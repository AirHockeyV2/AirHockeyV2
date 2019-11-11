#include "strategieTest.h"
#include <math.h>
int position=0;
strategieTest::strategieTest()
{
	loop=0;
}

strategieTest::~strategieTest()
{
}


void strategieTest::reagiere(float xaktPuck, float yaktPuck, float vxPuck, float vyPuck, float frames){
	loop++;
	if(loop % 10) position++;
	if(position>=3) position=0;
	if(position==0){
		posxS = 10;
		posyS = 140;
	}
	if(position==1){
		posxS = 10;
		posyS = 220;
	}
	if(position==3){
		posxS = 100;
		posyS = 180;
	}
}


