#ifndef STRIKER_H
#define STRIKER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;
using namespace std;

class Striker
{
public:
	CircleShape kreis;


	Striker();
	Striker(int radius);
	~Striker();

};


#endif 

