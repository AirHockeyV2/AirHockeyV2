#include "puck.h"

Puck::Puck(int radius) {
	this->kreis.setRadius(radius);
	this->kreis.setOrigin(radius, radius);
	this->kreis.setFillColor(Color::White);
	this->kreis.setPosition(posx, posy);
	breite = 361;
	laenge = 761;
	posx = laenge;
	posy = breite/2;
	vx = 0;
	vy = 0;
	rad = 19.5;
	faktorBandenkontakt = 0.8;
	
}

Puck::~Puck() {

}

void Puck::move(float xs, float ys) {
	if (posx +vx >= laenge) { //abprallen rechts
		posx = 2 * laenge - posx - vx;
		vx = -vx * faktorBandenkontakt;
		vy *= faktorBandenkontakt;
	}
	else {
		if (posx + vx <= 0 ) { //abprallen links
			posx = - posx - vx;
			vx = -vx * faktorBandenkontakt;
			vy *= faktorBandenkontakt;
		}
		else posx += vx;
	}

	if (posy + vy >= breite) { // abprallen unten
		posy = 2 * breite - posy - vy;
		vy = -vy * faktorBandenkontakt;
		vx *= faktorBandenkontakt;
	}
	else {
		if (posy + vy <= 0) { //abprallen oben
			posy = - posy - vy;
			vy = -vy * faktorBandenkontakt;
			vx *= faktorBandenkontakt;
		}
		else posy += vy;
	}
	strikerCollision(xs, ys);

	this->kreis.setPosition(posx, posy);
}

void Puck::strikerCollision(float xs, float ys)
{
	float dx = posx - xs;
	float dy = posy - ys;
	float dges = sqrt(dx * dx + dy * dy);

	if (dges <= 39) {

		this->kreis.setFillColor(Color::Green);

		bool collision = true;

		while (collision == true) {
			posx -= 0.001*vx;
			posy -= 0.001*vy;
			dx = posx - xs;
			dy = posy - ys;
			dges = sqrt(dx * dx + dy * dy);
			
			if (dges > 40) collision = false;
		}

		float a = atan((posx - xs) / (posy - ys));

		//Drehung um a
		float vxa = vx * cos(a) - vy * sin(a);
		float vya = vx * sin(a) + vy * cos(a);

		//an Neuer Koordinate reflektieren
		float vxx = vxa;
		float vyy = -vya;

		//um a zurzück drehen
		vx = vxx * cos(a) + vyy * sin(a);
		vy = -vxx * sin(a) + vyy * cos(a);

	}

	else this->kreis.setFillColor(Color::White);

}