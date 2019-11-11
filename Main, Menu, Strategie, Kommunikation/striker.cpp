#include "striker.h"

Striker::Striker(int radius) {
	this->kreis.setRadius(radius);
	this->kreis.setOrigin(radius,radius);
	this->kreis.setFillColor(Color::Blue);
	this->kreis.setPosition(19.5, 200);
}


Striker::~Striker() {

}

