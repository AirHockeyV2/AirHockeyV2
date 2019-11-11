#ifndef STRATEGIETEST_H
#define STRATEGIETEST_H

class strategieTest
{
public:
	strategieTest();
	~strategieTest();
	float posxS;
	float posyS;
	int loop;
	
	void reagiere(float xaktPuck, float yaktPuck, float vxPuck, float vyPuck, float frames);

};

#endif // STRATEGIETEST_H
