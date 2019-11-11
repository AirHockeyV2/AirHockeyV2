#include "grafik.h"
#include <SFML/Graphics.hpp>
#include "puck.h"
#include "striker.h"
#include <ncurses.h>

using namespace std;
using namespace sf;
RenderWindow window({ 761 , 361 }, "Air-Hockey-Tisch");
Puck P1(17);
Striker S1(19.5); // nicht der tatsaechliche Striker, nur ein Kreisobjekt, das gezeichnet werden kann
#define RADIUS_S 19.5
#define breite 361;
#define laenge 761;

	
Grafik::Grafik()
{	
	faktor = 0.2;
	frames = 30;
	
	window.setFramerateLimit(frames);
	
	this->kreis.setRadius(RADIUS_S);
	this->kreis.setOrigin(RADIUS_S,RADIUS_S);
	this->kreis.setFillColor(Color::Blue);
	this->kreis.setPosition(19.5, 200);
}

Grafik::~Grafik()
{
}

//wird jeden Main-Loop einmal ausgefuehrt
void Grafik::bildverarbeitung(float posxS, float posyS){

	
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (Mouse::isButtonPressed(Mouse::Left))
		{

			P1.vx = ((Mouse::getPosition(window).x - P1.kreis.getPosition().x)*faktor);
			P1.vy = ((Mouse::getPosition(window).y - P1.kreis.getPosition().y)*faktor);
		}

	}

	xalt = P1.posx;
	yalt = P1.posy;

	P1.move(posxS, posyS); //Puckbewegung, ggf. Kollision mit Striker
	
	posx = P1.posx;
	posy = P1.posy;
	vx = P1.vx;
	vy = P1.vy;
	
	
}

//wird jeden Main-Loop einmal ausgefuehrt, nach Strategie
void Grafik::zeichne(float posxS, float posyS, int xl, int yl, int xl2, int yl2){
	
	window.clear();
	
	//Strikerposition dem Kreisobjekt mitteilen
	this->kreis.setPosition(posxS, posyS);
	
	if (P1.vx < 0) {
		//Bahn vor Bandenkontakt zeichnen
		sf::Vertex linie[]
		{
			sf::Vertex(sf::Vector2f(xalt, yalt)),
			sf::Vertex(sf::Vector2f(xl, yl))
		};

		window.draw(linie, 2, sf::Lines);

		//Bahn nach Bandenkontakt zeichenen
		sf::Vertex linieBande[]
		{
			sf::Vertex(sf::Vector2f(xl, yl)),
			sf::Vertex(sf::Vector2f(xl2, yl2))
		};

		window.draw(linieBande, 2, sf::Lines);
	}
	
	//Aktionslinie zeichnen
	sf::Vertex aktionslinie[]
	{
		sf::Vertex(sf::Vector2f(200, 0)),
		sf::Vertex(sf::Vector2f(200, 400))
	};
	window.draw(aktionslinie, 2, sf::Lines);
	
	window.draw(P1.kreis);
	window.draw(this->kreis);
	
	window.display();
}

