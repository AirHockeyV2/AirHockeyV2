#include <Wire.h>
 
void setup()
{
Wire.begin(7);
Wire.onRequest(requestEvent);
}
 
void loop()
{
delay(100);
}
 
void requestEvent()
{
int16_t bigNum = 11;
byte myArray[2];
 
myArray[0] = (bigNum >> 8) & 0xFF;
myArray[1] = bigNum & 0xFF;
Wire.write(myArray, 2);
}
