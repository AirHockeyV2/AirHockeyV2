#include <AccelStepper.h>

//define Arduino pin assignments

// pins of driver 1 (stepper 1)
#define power_pin_1 4 // Power (5V) pin of driver 1
#define pulse_pin_1 5 // Pulse pin of driver 1
#define direction_pin_1 6 // Direction pin of driver 1
#define enable_pin_1 7 // Enable pin of driver 1

// pins of driver 2 (stepper 2)
#define power_pin_2 8 // Power (5V) pin of driver 2
#define pulse_pin_2 9 // Pulse pin of driver 2
#define direction_pin_2 10 // Direction pin of driver 2
#define enable_pin_2 11 // Enable pin of driver 2

// Define two steppers of type driver 
AccelStepper stepper1(AccelStepper::DRIVER, pulse_pin_1, direction_pin_1);
AccelStepper stepper2(AccelStepper::DRIVER, pulse_pin_2, direction_pin_2);

// define steppers max speed and acceleration (max 20 rev/s for Arduino UNO)
float max_speed_rev_sec = 20; // Maximum speed in revolution/second
float max_speed_steps_second = max_speed_rev_sec*200; // Maximum speed in revolution/second, due to 200 steps per revolution by motor
float acceleration_rev_sec_square = 15; // Acceleration in revolution/squaresecond
float acceleration_steps_second_square = acceleration_rev_sec_square*200; // Acceleration in steps/squaresecond due to 200 steps per revolution by motor


int pos1 = 10000;
int pos2 = 10000;
unsigned long last_millis = 0;
unsigned int interval = 2000;


void setup()
{ 
  // Define pins as output
  pinMode(power_pin_1, OUTPUT);
  pinMode(pulse_pin_1, OUTPUT);
  pinMode(direction_pin_1, OUTPUT);
  pinMode(enable_pin_1, OUTPUT);
  pinMode(power_pin_2, OUTPUT);
  pinMode(pulse_pin_2, OUTPUT);
  pinMode(direction_pin_2, OUTPUT);
  pinMode(enable_pin_2, OUTPUT);

  // Activate drivers 
  digitalWrite(power_pin_1, HIGH);
  digitalWrite(power_pin_2, HIGH);
  digitalWrite(enable_pin_1, HIGH);
  digitalWrite(enable_pin_2, HIGH);

  stepper1.setMaxSpeed(max_speed_steps_second);
  stepper1.setAcceleration(acceleration_steps_second_square);
  stepper2.setMaxSpeed(max_speed_steps_second);
  stepper2.setAcceleration(acceleration_steps_second_square);
}

void loop()
{
  unsigned long current_millis = millis();
  
  if (stepper2.distanceToGo() == 0){
    pos2 = -pos2;
    stepper2.moveTo(pos2);
  }
  
  if(current_millis - last_millis >= 2*interval){
    last_millis = current_millis;
    digitalWrite(enable_pin_1, HIGH);
    digitalWrite(enable_pin_2, HIGH);
  }
  if(current_millis - last_millis < interval){
    stepper2.run();
  }
  else {
  digitalWrite(enable_pin_1, LOW);
  digitalWrite(enable_pin_2, LOW);
  }
}
