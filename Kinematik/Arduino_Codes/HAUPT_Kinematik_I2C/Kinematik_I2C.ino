#include <stdlib.h>
#include <stdio.h>
#include <AccelStepper.h>
#include <Wire.h>

// -------------------------DEFINITIONEN-------------------------------------------
// I2C Adresse festlegen
#define adresse 0x07

// Pins an Treiber 1 (Stepper 1)
#define power_pin_1 26 // Power (5V) pin of driver 1
#define pulse_pin_1 27 // Pulse pin of driver 1
#define direction_pin_1 28 // Direction pin of driver 1
#define enable_pin_1 29 // Enable pin of driver 1

// Pins an Treiber 2 (Stepper 2)
#define power_pin_2 22 // Power (5V) pin of driver 2
#define pulse_pin_2 23 // Pulse pin of driver 2
#define direction_pin_2 24 // Direction pin of driver 2
#define enable_pin_2 25 // Enable pin of driver 2

// Zwei Objekte des Typs Stepper erstellen mit Einstellung DRIVER, da Motoren nicht direkt am Arduino sind sondern Treiber dazwischenhängt
AccelStepper stepper1(AccelStepper::DRIVER, pulse_pin_1, direction_pin_1);
AccelStepper stepper2(AccelStepper::DRIVER, pulse_pin_2, direction_pin_2);

/*
Maximal Geschwindigkeit und Beschleunigung definieren. 
WICHTIG: Maximalwerte müssen mit Strombegrezungsschraube auf TB6600 Treiber getestet werden. Große Auswirkung auf Dynamik. 
Zu viel Strom: Schritte übersprungen, Motoren zu heiß und sehr laut. 
Zu wenig Strom: Motoren bleiben zwischendurch komplett stehen und pfeifen, nicht genug Drehmoment für die Schritte.

ACHTUNG: Folgende Werte haben sich im Vergleich zur Doku nochmal verändert, da die Bewegungslänge noch
mit Wurzel(2) vergrößert werden musste, damit wir uns auf "rechteckigem" Koordinatensystem bewegen, und 
nicht auf einem Kreis mit normierter Länge. Deshalb hat sich auch die Orts-Trafo dementsprechend verändert.

Ergebnisse Dynamiktests:
speed | accel | sgu  | Kommentar
 120  |  120  | 1,25 | laut, Erwärmung gerade noch ok. Zeit 2,98 Umdr. ~0,27s. 
 100  |  100  | 1,5  | laut, Erwärmung ok, Zeit 2,98 Umdr. ~0,31s. ab und zu Ruckler
 80   |  80   | 2,4  | etwas leiser, Erärmung gut. Zeit 2,98 Umdr. ~0,37s. Genauigkeit mittel, selten Aussetzer <- läuft am Glattesten!
 40   |  40   | 3,5  | leise, Erwärmung sehr gut. Zeit 2,98 Umdr. ~0,58s. Genauigkeit besser

Legende:
striche-gegen-uhrzeigersinn-von-12-Uhr =: sgu
2,98 Umdr. ist eine Bewegung von "Torposition" zu "rechts-außen-auf-Verteidigungslinie(y=100)"

*/
float max_speed_rev_sec = 80; // Max. Geschwindigkeit in Umdr./s (motor max 35 rev/s)
float acceleration_rev_sec_square = 80; // Max. Beschleunigung in Umdr./s*s

// Variablen definieren
int16_t kontrollvariable = 0; // Signalisiert R.Pi, ob Motoren angekommen (1) oder unterwegs (0)
int16_t x_ziel = 0;
int16_t y_ziel = 0;
float stepper1_ziel_umdrehungen = 0.0;
float stepper2_ziel_umdrehungen = 0.0;
float umfang_scheibe = 94.248; // Aus Geometrie

// Grenzen der Spielfläche, damit Roboter nicht gegen die Banden fährt
int obere_grenze_x = 361;
int untere_grenze_x = 0;
int obere_grenze_y = 200;
int untere_grenze_y = 0;

// -------------------------SETUP-------------------------------------------
void setup()
{ 
  // I2C - Verbindung mit Adresse aktivieren
  Wire.begin(adresse);
  Wire.onReceive(empfangen);
  Wire.onRequest(senden);
  
  // Pins als Ausgang definieren
  pinMode(power_pin_1, OUTPUT);
  pinMode(pulse_pin_1, OUTPUT);
  pinMode(direction_pin_1, OUTPUT);
  pinMode(enable_pin_1, OUTPUT);
  pinMode(power_pin_2, OUTPUT);
  pinMode(pulse_pin_2, OUTPUT);
  pinMode(direction_pin_2, OUTPUT);
  pinMode(enable_pin_2, OUTPUT);

  // Treiber mit Spannung versorgen, damit Kommunikation möglich.
  digitalWrite(power_pin_1, HIGH);
  digitalWrite(power_pin_2, HIGH);

  // Minimale Pulsweite mit welcher Treiber angesteuert wird. 
  // 20 Mikrosekunden von Bibliothek empfohlen, Treiber kann lt. Datenblatt bis 2,2 Mikrosekunden.
  stepper1.setMinPulseWidth(20);
  stepper2.setMinPulseWidth(20);

  // Pins invertieren falls nötig, false ist default. (direction, step, enable)
  stepper1.setPinsInverted (true, false, false);
  stepper2.setPinsInverted (true, false, false);
}

// -------------------------FUNKTIONEN-------------------------------------------
// Funktion zum Deaktivieren der Motoren / Treiber, damit die Motoren nicht überhitzen.
void motoren_deaktivieren(){
  digitalWrite(enable_pin_1, LOW);
  digitalWrite(enable_pin_2, LOW);
}

// Funktion zum Aktivieren der Motoren / Treiber, damit Bewegung überhaupt möglich. Motoren werden heiß mit der Zeit!
void motoren_aktivieren(){
  digitalWrite(enable_pin_1, HIGH);
  digitalWrite(enable_pin_2, HIGH);
}

// Sendefunktion I2C
void senden(){ 
  byte datenarray[2];
  datenarray[0] = (kontrollvariable >> 8) & 0xFF;
  datenarray[1] = kontrollvariable & 0xFF;
  Wire.write(datenarray, 2);
}


// Empfangsfunktion I2C
void empfangen(int anzahl_bytes){
  byte a,b,c,d;
  a = Wire.read();
  b = Wire.read();
  c = Wire.read();
  d = Wire.read();
  x_ziel = a;
  x_ziel = (x_ziel << 8) | b;
  y_ziel = c;
  y_ziel = (y_ziel << 8) | d;
  // Checken, ob Eingabe in den Grenzen liegt
  if (x_ziel > obere_grenze_x || x_ziel < untere_grenze_x) x_ziel = 0;
  if (y_ziel > obere_grenze_y || y_ziel < untere_grenze_y) y_ziel = 0;
}

// Funktion, um neue anzufahrende Koordinaten abfragen und in (Umdr1,Umdr2)-Koordinaten by reference abzuspeichern. Dabei wird geprüft, ob die (x,y)-Eingabe innerhalb der Spielfläche liegt.
void neue_koordinaten_abfragen(float* stepper1_ziel_umdrehungen, float* stepper2_ziel_umdrehungen, float* umfang_scheibe, int obere_grenze_x, int untere_grenze_x, int obere_grenze_y, int untere_grenze_y){
  // Abspeichern der (Umdr1,Umdr2)-Koordinaten
  *stepper1_ziel_umdrehungen = ortstransformation(1, (float)x_ziel, (float)y_ziel, *umfang_scheibe);
  *stepper2_ziel_umdrehungen = ortstransformation(2, (float)x_ziel, (float)y_ziel, *umfang_scheibe);
}

// Funktion zur Koordinatentransformation von (x,y)-Koordinaten der Aktionsfläche auf dem Spieltisch zu (Umdr1,Umdr2)-Koordinaten
// der jeweiligen Motorpositionen. Steppernummer gibt an, welche Formel verwendet werden soll - Je nach Motor (Formel aus kinematischer
// Beziehung durch den Aufbau).
// Achtung: Die Wurzel(2) im Nenner hat sich wieder gekürzt, da wir uns nicht auf einem Radius r=1 bewegen wollen, 
// sondern auf einem Kartesichen Koord.Sys., welches "rechteckig" ist und kein Kreis. 
float ortstransformation(int steppernummer, float x_ziel, float y_ziel, float umfang_scheibe){
  float ziel_umdrehung;
  if (steppernummer == 1) ziel_umdrehung = (-x_ziel + y_ziel) / (umfang_scheibe); 
  if (steppernummer == 2) ziel_umdrehung = (-x_ziel - y_ziel) / (umfang_scheibe); 
  return ziel_umdrehung;
}

// Funktion um Geschwindigkeit und Beschleunigung des Motors mit dem kürzeren zu fahrenden Weg herunter zu skalieren,
// damit beide Motoren zeitgleich ihr Ziel erreichen und der Roboter insgesamt eine (annähernd) geradlinige Bewegung ausführt.
void geschwindigkeit_und_beschleunigung_zuweisen(float max_speed_rev_sec, float acceleration_rev_sec_square){
  
  // Variablen für den zu fahrenden Weg und Eliminieren der Vorzeichen. 
  // Nötig, damit betragsmäßiges Vergleichen von floats in der darauffolgenden If-Anweisung möglich ist
  float stepper1_distance = stepper1.distanceToGo()/200.0;
  if (stepper1_distance < 0) stepper1_distance = -stepper1_distance; // Negative float in positive, damit Vergleich möglich in if-Schleife
  float stepper2_distance = stepper2.distanceToGo()/200.0;
  if (stepper2_distance < 0) stepper2_distance = -stepper2_distance; // Negative float in positive, damit Vergleich möglich in if-Schleife

  // Fall: Stepper 1 hat den längeren Weg
  if (stepper1_distance > stepper2_distance) {
    stepper1.setMaxSpeed(max_speed_rev_sec*200.0); // Stepper 1 max Geschwindigkeit zuweisen
    stepper1.setAcceleration(acceleration_rev_sec_square*200); // Stepper 1 max Beschleunigung zuweisen
    stepper2.setMaxSpeed((wert_skalieren(stepper2.distanceToGo(), stepper1.distanceToGo(), max_speed_rev_sec))*200.0); // Stepper 2 skalierte Geschwindigkeit zuweisen
    stepper2.setAcceleration((wert_skalieren(stepper2.distanceToGo(), stepper1.distanceToGo(), acceleration_rev_sec_square))*200.0); // Stepper 2 skalierte Beschleunigung zuweisen
  }
  // Fall: Stepper 2 hat den längeren Weg oder beide Wege gleichgroß
  else {
    stepper1.setMaxSpeed((wert_skalieren(stepper1.distanceToGo(), stepper2.distanceToGo(), max_speed_rev_sec))*200.0); // Stepper 1 skalierte Geschwindigkeit zuweisen
    stepper1.setAcceleration((wert_skalieren(stepper1.distanceToGo(), stepper2.distanceToGo(), acceleration_rev_sec_square))*200.0); // Stepper 1 skalierte Beschleunigung zuweisen
    stepper2.setMaxSpeed(max_speed_rev_sec*200.0); // Stepper 2 max Geschwindigkeit zuweisen
    stepper2.setAcceleration(acceleration_rev_sec_square*200); // Stepper 2 max Beschleunigung zuweisen
  }
}

// Funktion zum Skalieren der Geschwindigkeit oder der Beschleunigung
float wert_skalieren(float kleinerer_weg, float groesserer_weg, float skalier_massstab){
    float skalierter_wert = (kleinerer_weg / groesserer_weg) * skalier_massstab;
    return skalierter_wert;
}

// -------------------------LOOP-------------------------------------------
void loop(){ 
  // Abfragen neuer Zielkoordinaten, wenn vorheriges Ziel erreicht ist. 
  if (stepper1.distanceToGo() == 0 && stepper2.distanceToGo() == 0){
    motoren_deaktivieren();
    kontrollvariable = 1;
    neue_koordinaten_abfragen(&stepper1_ziel_umdrehungen, &stepper2_ziel_umdrehungen, &umfang_scheibe, obere_grenze_x, untere_grenze_x, obere_grenze_y, untere_grenze_y);
    stepper1.moveTo((int)(stepper1_ziel_umdrehungen*200));
    stepper2.moveTo((int)(stepper2_ziel_umdrehungen*200));
    geschwindigkeit_und_beschleunigung_zuweisen(max_speed_rev_sec, acceleration_rev_sec_square);
    motoren_aktivieren();
    kontrollvariable = 0;
  }
  stepper1.run();
  stepper2.run();
}
