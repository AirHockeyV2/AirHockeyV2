#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <chrono>
#include <ctime>
#include <raspicam/raspicam_cv.h>
#include <thread>
#include "grafik.h"
#include <SFML/Graphics.hpp>
#include <ncurses.h>


using namespace std;
using namespace cv;

float Geschw(float tdelta, float posalt, float posneu)
{
	float v;
	v = abs(posneu - posalt) / (tdelta);
	std::cout << "In Funktion Geschw: v ist " << v << endl;
	return(v);
}

//Eingangsgrößen aus Foto
float xpix;
float ypix;
long long tneu;

//Vorgegebene Größen
const float rpuck = 19.5; //Festlegen je nach Größe des Pucks 

//Positionsvariablen
float xalt;
float yalt;
float xneu;
float yneu;


//Zeitangaben
long long talt;
int tdelta;

//Für Picamera
raspicam::RaspiCam_Cv Camera; //Definiert, wie Kamera genannt
cv::Mat CapturedImage;  //Bild mit Opencv

//fuer Simulation
Grafik sim;

int main()
{
	initscr();
	curs_set(0);
	
	//Parameter: BEFORE open camera)
	Camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
	//CV_8UC1 is greyscale image or CV_8UC3 is RGB image

	if (!Camera.open())
	{
		cerr << "Error opening the camera" << endl; //cerr: standard error stream für char
		return -1;
	}

	//Parameter: AFTER Camera is opened, Eigenschaften aus raspicam_cv.h
	Camera.set(CV_CAP_PROP_FRAME_WIDTH, 1200);
	Camera.set(CV_CAP_PROP_FRAME_HEIGHT, 640);
	Camera.set(CV_CAP_PROP_FPS, 30); //Funktioniert bisher nur mit 30
	
	//z.B. wenn Bild zu dunkel:
	//Camera.set(CV_CAP_PROP_GAIN, 50); //50
	//Camera.set(CV_CAP_PROP_EXPOSURE, -1); //50
	//Camera.set(CV_CAP_PROP_WHITE_BALANCE_RED_V, -1); //50
	//Camera.set(CV_CAP_PROP_WHITE_BALANCE_BLUE_U, -1); //50

	//Alle Eigenschaften aus raspicam_cv.h, SET wenn nötig 
	//CV_CAP_PROP_FRAME_WIDTH
	//CV_CAP_PROP_FRAME_HEIGHT
	//CV_CAP_PROP_FPS
	//CV_CAP_PROP_FORMAT: CV_8UC1 or CV_8UC3 
	//CV_CAP_PROP_BRIGHTNESS : [0, 100]
	//CV_CAP_PROP_CONTRAST : [0, 100]
	//CV_CAP_PROP_SATURATION : [0, 100]
	//CV_CAP_PROP_GAIN : (iso) : [0, 100]
	//CV_CAP_PROP_EXPOSURE : -1 auto.[1, 100] shutter speed from 0 to 33ms
	//CV_CAP_PROP_WHITE_BALANCE_RED_V : [1, 100] - 1 auto whitebalance
	//CV_CAP_PROP_WHITE_BALANCE_BLUE_U : [1, 100] - 1 auto whitebalance

//Schleife, sodass dauerhaft Bilder gemacht werden 
for (int status=1; status<500;status++) //Bisher nur 3x //Ändern in a > 0 oder while schleife

{
	clear();
	printw("Loop Nr. %d \n",status);

	//Startet Bild
		Camera.grab();
		Camera.retrieve(CapturedImage);

	//Konvertierung des Bildes
	Mat hsvImg;    // HSV Image
	Mat threshImg;   // Thresh Image
	cvtColor(CapturedImage, hsvImg, cv::COLOR_BGR2HSV); // Convert Original Image to HSV Image

	//HSV - Farbspezifisch anpassen.
	//Diese Werte müssen bei anderen Lichtverhältnissen angepasst werden
	int lowH = 0;       // Set Hue (Gelb) 				//15	0
	int highH = 5;										//45	5
	int lowS = 150;       // Set Saturation (Gelb)		//80	150
	int highS = 255;									//255	255
	int lowV = 150;       // Set Value (Gelb)			//80	150
	int highV = 255;									//255	255

	inRange(hsvImg, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), threshImg);
	dilate(threshImg, threshImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(threshImg, threshImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//KOORDINATENBERECHNUNG
	Moments oMoments = moments(threshImg);
	double dM01 = oMoments.m01;
	double dM10 = oMoments.m10;
	double dArea = oMoments.m00;

	xpix = dM10 / dArea;
	ypix = dM01 / dArea;

	//AB HIER IST KOORDINATENVERWERTUNG	

	//1. Schritt: Pixelkoordinate in x/y-Koordinate umrechnen 
	//Umrechnen auf 800x400, Anpassen an Koordinatensystem
	float xneu = (xpix) / 680 * 400;
	float yneu = (ypix) / 1200 * 800;
	xneu -= 57;
	yneu -= 34;
	xneu = xneu * 744/620;
	if (xpix > 680 || ypix > 1200)
	{
		std::cout << "Fehler, Puck in Pixeln falsch erkannt" << endl;
		//return -1; //Hier das programm beenden
	}
	printw("x: %f \n",xneu);
	printw("y: %f \n",yneu);
	
	//Für nächstes Bild: 
	talt = tneu;
	xalt = xneu;
	yalt = yneu;
	vxalt = vxneu;
	vyalt = vyneu;
	
	//Weitergabe der Daten (xweiter, yweiter, vxweiter, vyweiter) an den zweiten Pi (angepasst an das Koordinatensystem) 
	//--> Noch zu realisieren über I2
	
	sim.zeichne(xneu, yneu,0,0,0,0);
	refresh();
} //Ende des Loops insgesamt

printw("stopping camera");
Camera.release();

return 0;
}