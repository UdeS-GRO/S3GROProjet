/*
Projet S3 GRO
Class to use HC-SR04 sonar sensor
@author Jean-Samuel Lauzon
@version 1.0 30/04/2020
*/

#ifndef Sonar_H_
#define Sonar_H_

#include <Arduino.h>

class Sonar
{
    public:
        Sonar(uint8_t, uint8_t);

        /** Function to get range in mm
        @return distance in mm
        */
        float getRange();

    
    private:
        uint8_t trigPin_;
        uint8_t echoPin_;
};
#endif //Sonar
