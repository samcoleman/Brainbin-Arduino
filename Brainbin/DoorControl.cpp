#include "DoorControl.h"

DoorControl::DoorControl(int pwmPin, int sweepSpeed, int closedAngle, int openAngle){
    _closedAngle = closedAngle;
    _openAngle = openAngle;
    _pwmPin = pwmPin;
    _sweepSpeed = sweepSpeed;                    // (Unit Deg/s)
    
    _sweepAngle = abs(_openAngle - _closedAngle);  
    _sweepDelay = 1000 / _sweepSpeed;             // (Unit ms);
    _sweepTime  = _sweepAngle*_sweepDelay;         // (Unit ms);

    _pos = 0;
}

// Recover from off state and close door
void DoorControl::reset() {
  _servo.attach(_pwmPin); 
  _servo.write(_closedAngle);   // Tell servo to go to position closed
  delay(_sweepTime);            // Delay for worst case senario
  pinMode(_pwmPin, INPUT);      // TURN PWM MODE OFF 
  _state = false;               // Set state as closed
}

void DoorControl::sweep(int a_start, int a_end){
  pinMode(_pwmPin, OUTPUT); // TURN PWM MODE BACK ON (Stops buzzing when the motor isnt moving)
  // Sweep forward
  if (a_end > a_start){
    for (_pos = a_start; _pos <= a_end; _pos += 1) { 
      // in steps of 1 degree
      _servo.write(_pos);              // tell servo to go to position in variable 'pos'
      delay(_sweepDelay);               // Wait for the servo to reach the position, sets the speed 
    }
  // Logic is different reversing the sweep
  } else {
    for (_pos = a_start; _pos >= a_end; _pos -= 1) {
      // in steps of 1 degree
      _servo.write(_pos);              // tell servo to go to position in variable 'pos'
      delay(_sweepDelay);             // Wait for the servo to reach the position, sets the speed 
    }
  }
  delay(_sweepDelay);  
  pinMode(_pwmPin, INPUT); // TURN PWM MODE OFF
}

void DoorControl::door_open() {
   if (_state == true) {
    return; // If door is already open, return early
  }
  sweep(_closedAngle, _openAngle);
  _state = true;
}

void DoorControl::door_close() {
  if (_state == false) {
    return; // If door is already closed, return early
  }
  
  sweep(_openAngle, _closedAngle);
  _state = false;
}


int DoorControl::get_sweep_time() {
  return _sweepTime;
}
