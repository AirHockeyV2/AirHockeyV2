#ifndef GRAFIK_H
#define GRAFIK_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;
using namespace std;

class Grafik
{
public:
	CircleShape kreis;
	void bildverarbeitung(float posxs, float posys);
	void zeichne(float posxS, float posyS, int xl, int yl, int xl2, int yl2);
	float faktor;
	float frames;
	float posx;
	float posy;
	float xalt;
	float yalt;
	float vx;
	float vy;
	

	Grafik();
	~Grafik();

};

#endif // GRAFIK_H
