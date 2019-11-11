#include <AccelStepper.h>

#define power_pin_1 22 // Power (5V) pin of driver 11
#define enable_pin_1 25 // Enable pin of driver 1
#define power_pin_2 26 // Power (5V) pin of driver 2
#define enable_pin_2 29 // Enable pin of driver 2


void setup() {
  // Define pins as output
  pinMode(power_pin_1, OUTPUT);
  pinMode(enable_pin_1, OUTPUT);
  pinMode(power_pin_2, OUTPUT);
  pinMode(enable_pin_2, OUTPUT);

  // Activate drivers 
  digitalWrite(power_pin_1, HIGH);
  digitalWrite(power_pin_2, HIGH);
  digitalWrite(enable_pin_1, LOW);
  digitalWrite(enable_pin_2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
