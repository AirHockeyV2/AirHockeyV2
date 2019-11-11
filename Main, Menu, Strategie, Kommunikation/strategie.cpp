#include <iostream>
#include <math.h>
#include "strategie.h"

using namespace std;

Strategie::Strategie()
{
	xalt = 0;
	yalt = 0;
	breite = 361;
	laenge = 761;
	posxS = 0;
	posyS = breite/2;
	xlinie = 0;
	ylinie = 0;
	xlinie2 = 0;
	ylinie2 = 0;
}

Strategie::~Strategie()
{
}

void Strategie::reagiere(float xaktPuck, float yaktPuck, float vxPuck, float vyPuck, float frames) {

	if (vxPuck < 0) {

		steigung = vyPuck/vxPuck;

		//Schnittpunt mit der y Achse
		b = yaktPuck - xaktPuck * steigung;

		Yschnittpunkt = steigung * Xschnittpunkt + b;
		//cout << "Schnittpunkt = " << Yschnittpunkt << endl;

		//Bandenkontakt & Anzahl der Bandenkontakte
		int AnzahlBanden = 0;
		if ((Yschnittpunkt <= breite && Yschnittpunkt >= 0) || vxPuck > 0) {
			//cout << "kein Bandenkontakt" << endl;
			AnzahlBanden = 0;
		}
		else {

			if (Yschnittpunkt < 0) {
				AnzahlBanden = ceil(-Yschnittpunkt / breite);
			}
			else {
				AnzahlBanden = ceil((Yschnittpunkt - breite) / breite);
			}
			//cout << "Bandenkontakte = " << ceil(AnzahlBanden) << endl;
		}

		//Schnittpunkt mit Aktionslinie berechnen
		float SchnittmitAktionslinie;

		if (AnzahlBanden == 1) {
			if (Yschnittpunkt < 0) SchnittmitAktionslinie = -Yschnittpunkt;
			else SchnittmitAktionslinie = breite - (Yschnittpunkt - breite);
		}
		else {
			//erster Bandenkontakt oben
			if (Yschnittpunkt<0) {
				if (AnzahlBanden % 2 == 0) SchnittmitAktionslinie = Yschnittpunkt + AnzahlBanden * breite;//Schnittpunkt bei gerader Anzahl an noch Ausstehenden Bandenkontakten und nächstem Bandenkontakt oben am Spielfeld
				else SchnittmitAktionslinie = breite - (Yschnittpunkt + AnzahlBanden * breite); //oben & ungerade
			}
			//erster Bandenkontakt unten
			else {
				if (AnzahlBanden % 2 == 0) SchnittmitAktionslinie = Yschnittpunkt - AnzahlBanden * breite;//unten & gerade
				else SchnittmitAktionslinie = breite - (Yschnittpunkt - AnzahlBanden * breite); //unten & ungerade
			}
		}
		//cout << "SchnittpunktmitAKtionslinie: " << SchnittmitAktionslinie << endl;


		/*//Berechne Strecke
		float strecke = sqrt((Xschnittpunkt - xaktPuck)*(Xschnittpunkt - xaktPuck) + (Yschnittpunkt - yaktPuck)*(Yschnittpunkt - yaktPuck));
		//cout << "Weg zum Schnittpunkt: " << strecke << endl;

		float Xstrecke = posxS - Xschnittpunkt;
		float Ystrecke = posyS - Yschnittpunkt;

		//Puckgeschwindeigkeit
		float puckGeschw;
		puckGeschw = sqrt(vxPuck*vxPuck + vyPuck * vyPuck)*frames;
		//cout << " PuckGeschwindigkeit: " << puckGeschw << endl;

		//Zeit bis zum eintreffen 
		float zeit;
		zeit = strecke / puckGeschw;
		//cout << "Zeit bis zum Eintreffen = " << zeit << endl;
		 */
		// Abwehren vorläufig
			vxS = (Xschnittpunkt - posxS)*0.3;
			vyS = (SchnittmitAktionslinie - posyS)*0.3;

			posxS += vxS;
			posyS += vyS;
	}
	else {
		vxS = (0 - posxS)*0.3;
		vyS = (breite / 2 - posyS)*0.3;

		posxS += vxS;
		posyS += vyS;
	}
	
	//Linie der Bahn zeichnen
	if (vxPuck > 0) {

		if (steigung < 0) {
			xlinie = -b / steigung;
			ylinie = 0;

			xlinie2 = -(breite + b ) / steigung;
			ylinie2 = breite;
		}
		else {
			xlinie = (breite - b) / steigung;
			ylinie = breite;

			xlinie2 = (2 * breite - b) / steigung;
			ylinie2 = 0;
		}
	}
	else {

		if (steigung > 0) {
			xlinie = - b / steigung;
			ylinie = 0;

			xlinie2 = -(breite + b ) / steigung;
			ylinie2 = breite;
		}
		else {
			xlinie = (breite - b) / steigung;
			ylinie = breite;

			xlinie2 = (2*breite - b) / steigung;
			ylinie2 = 0;
		}
	}
}