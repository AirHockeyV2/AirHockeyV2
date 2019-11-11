#include <AccelStepper.h>

//define Arduino pin assignments

// pins of driver 1 (stepper 1)
#define power_pin_1 22 // Power (5V) pin of driver 1
#define pulse_pin_1 23 // Pulse pin of driver 1
#define direction_pin_1 24 // Direction pin of driver 1
#define enable_pin_1 25 // Enable pin of driver 1

// pins of driver 2 (stepper 2)
#define power_pin_2 26 // Power (5V) pin of driver 2
#define pulse_pin_2 27 // Pulse pin of driver 2
#define direction_pin_2 28 // Direction pin of driver 2
#define enable_pin_2 29 // Enable pin of driver 2

// Define two steppers of type driver 
AccelStepper stepper1(AccelStepper::DRIVER, pulse_pin_1, direction_pin_1);
AccelStepper stepper2(AccelStepper::DRIVER, pulse_pin_2, direction_pin_2);

// define steppers max speed and acceleration (max 20 rev/s for Arduino UNO)
float max_speed_rev_sec = 80; // Maximum speed in revolution/second
float max_speed_steps_second = max_speed_rev_sec*200; // Maximum speed in revolution/second, due to 200 steps per revolution by motor
float acceleration_rev_sec_square = 80; // Acceleration in revolution/squaresecond
float acceleration_steps_second_square = acceleration_rev_sec_square*200; // Acceleration in steps/squaresecond due to 200 steps per revolution by motor


float pos_rev_1 = 1.8; // Aimed position in revolutions clockwise for stepper 1
float pos_steps_1 = pos_rev_1*200; // in steps
float pos_rev_2 = 1.8; // Aimed position in revolutions clockwise for stepper 2
float pos_steps_2 = pos_rev_2*200; // in steps


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

  stepper1.moveTo(pos_steps_1);
}

void loop()
{ 
  if (stepper1.distanceToGo() == 0){
    pos_steps_1 = -pos_steps_1;
    stepper1.moveTo(pos_steps_1);
  }
  stepper1.run();
  
  if (stepper2.distanceToGo() == 0){
    pos_steps_2 = -pos_steps_2;
    stepper2.moveTo(pos_steps_2);
  }
  stepper2.run();
}
