#ifndef PUCK_H
#define PUCK_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;
using namespace std;

class Puck
{
public:
	CircleShape kreis;
	float posx;
	float posy;
	float vx;
	float vy;
	float rad;
	float faktorBandenkontakt;
	float breite;
	float laenge;

	void move(float xs, float ys);
	void strikerCollision(float xs, float ys);

	Puck(int radius);
	~Puck();
	
};


#endif 

