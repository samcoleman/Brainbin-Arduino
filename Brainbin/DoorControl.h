#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H
#include <Arduino.h>
#include <Servo.h>

class DoorControl
{
  public:
    DoorControl(int pwmPin, int sweepSpeed,int closedAngle, int openAngle);
    void reset();
    void door_open();
    void door_close();
    int  get_sweep_time();
  private:
    void sweep(int a_start, int a_end);
    Servo _servo;
    int _closedAngle;  // Angle of the servo when door is closed (0-180)
    int _openAngle;    // Angle of the servo when door is open (0-180)
    int _sweepAngle;   // Angle inbetween
    int _pwmPin;       // PWM pin of arduino servo is connected to
    int _sweepSpeed;   // (Unit Deg/s)
    int _sweepDelay;   // Delay per angle step (Unit ms);
    int _sweepTime;    // Calcuated time for sweep (Unit ms);

    int  _pos;         // Variable to store the servo position
    bool _state;       // False Closed , True Open
};

#endif
