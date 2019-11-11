#include <Wire.h>
 
void setup()
{
Wire.begin(8);
Wire.onRequest(schreiben);
Wire.onReceive(empfangen);
}

int16_t x_empfangen = 0;
int16_t y_empfangen = 0;

void schreiben()
{
  byte datenarray[2];

  if (x_empfangen != -1){
    datenarray[0] = (x_empfangen >> 8) & 0xFF;
    datenarray[1] = x_empfangen & 0xFF;
    x_empfangen = -1;
    Wire.write(datenarray, 2);
  }
  
  else if (y_empfangen != -1){
    datenarray[0] = (y_empfangen >> 8) & 0xFF;
    datenarray[1] = y_empfangen & 0xFF;
    x_empfangen = -1;
    Wire.write(datenarray, 2);
  }
  
}

void empfangen(int anzahl_bytes){
  byte a,b,c,d;
  a = Wire.read();
  b = Wire.read();
  c = Wire.read();
  d = Wire.read();
  x_empfangen = a;
  x_empfangen = (x_empfangen << 8) | b;
  y_empfangen = c;
  y_empfangen = (y_empfangen << 8) | d;
}

void loop()
{

}
