#ifndef STRATEGIE_H
#define STRATEGIE_H

class Strategie
{
public:
	Strategie();
	~Strategie();
	float posxS;
	float posyS;
	float xalt;
	float yalt;
	float vxS;
	float vyS;
	int breite;
	int laenge;
	float steigung; //Steigung der Puckbahn	
	float Xschnittpunkt = 200; //Schnittpunkt an Aktionslinie
	float Yschnittpunkt;
	float b = 200; //Schnittpunt mit der y Achse
	float xlinie;
	float ylinie;
	float xlinie2;
	float ylinie2;
	
	void reagiere(float xaktPuck, float yaktPuck, float vxPuck, float vyPuck, float frames);

};

#endif // STRATEGIE_H
