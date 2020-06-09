/*
Projet S3 GRO
Class to control a motor via Sparkfun TB6612FNG
@author Jean-Samuel Lauzon
@version 1.0 30/04/2020
*/

#include "MotorControl.h"

MotorControl::MotorControl(uint8_t PWMPin, uint8_t Input1Pin, uint8_t Input2Pin, uint8_t StandbyPin){
    PWMPin_ = PWMPin;
    Input1Pin_ = Input1Pin;
    Input2Pin_ = Input2Pin;
    StandbyPin_ = StandbyPin;
    pinMode(PWMPin_, OUTPUT);
    pinMode(Input1Pin_, OUTPUT);
    pinMode(Input2Pin_, OUTPUT);
    pinMode(StandbyPin_, OUTPUT);
}

void MotorControl::setPWM(float pwm){
      digitalWrite(StandbyPin_, HIGH);
      // Verify speed between [-1, 1]
      if(pwm>1){
        pwm = 1;
      }
      if(pwm<-1){
        pwm = -1;
      }
      // Motor direction
      if(pwm>0){
        digitalWrite(Input1Pin_, HIGH);
        digitalWrite(Input2Pin_, LOW);
      }else{
        digitalWrite(Input1Pin_, LOW);
        digitalWrite(Input2Pin_, HIGH);
      }
      // Set PWM
      pwm = fabs(pwm);
      analogWrite(PWMPin_, 255*pwm);
}
void MotorControl::disable(){
      analogWrite(PWMPin_, 0);
      digitalWrite(StandbyPin_, LOW);
    };
