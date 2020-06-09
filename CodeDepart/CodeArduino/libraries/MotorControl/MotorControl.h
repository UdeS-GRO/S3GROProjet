/*
Projet S3 GRO
Class to control a motor via Sparkfun TB6612FNG
@author Jean-Samuel Lauzon
@version 1.0 30/04/2020
*/

#ifndef MotorControl_H_
#define MotorControl_H_

#include <Arduino.h>

class MotorControl
{
    public:
        /** Constructor
        @param pin values
        */
        MotorControl(uint8_t, uint8_t, uint8_t, uint8_t);

        /** Function to set PWM to motor
        @param PWM value in range [-1.0, 1.0]
        */
        void setPWM(float);
        
        /** Function to disable motor
        */
        void disable();

    
    private:
        uint8_t PWMPin_;
        uint8_t Input1Pin_;
        uint8_t Input2Pin_;
        uint8_t StandbyPin_;
};
#endif //MotorControl
