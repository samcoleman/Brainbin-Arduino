#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int closedAngle = 5;   // Angle of the servo when door is closed (0-180)
int openAngle   = 175; // Angle of the servo when door is open   (0-180)
int sweepAngle  = abs(openAngle - closedAngle); 

int servoPin = 9; // PWM pin of arduino servo is connected to

int sweepSpeed = 85;                              // (Unit Deg/s)
int sweepDelay = 1000 / sweepSpeed;               // (Unit ms)
int sweepTime  = sweepAngle*sweepDelay;           // (Unit ms)

int pos = 0;           // variable to store the servo position

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object

  // Recover from reset state and close door
  myservo.write(closedAngle);   // Tell servo to go to position closed
  delay(sweepTime);             // Delay for worst case senario
  pinMode(servoPin, INPUT);     // TURN PWM MODE OFF 
}

int sweep(int a_start, int a_end){
  pinMode(servoPin, OUTPUT); // TURN PWM MODE BACK ON (Stops buzzing when the motor isnt moving)
  // Sweep forward
  if (a_end > a_start){
    for (pos = a_start; pos <= a_end; pos += 1) { 
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(sweepDelay);               // Wait for the servo to reach the position, sets the speed 
    }
  // Logic is different reversing the sweep
  } else {
    for (pos = a_start; pos >= a_end; pos -= 1) {
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(sweepDelay);               // Wait for the servo to reach the position, sets the speed 
    }
  }
  delay(sweepDelay);  
  pinMode(servoPin, INPUT); // TURN PWM MODE OFF
}

void door_open() {
  sweep(closedAngle, openAngle);
}

void door_close() {
  sweep(openAngle, closedAngle);
}

void loop() {
  delay(5000);
  door_open();
  delay(5000);
  door_close();
}
