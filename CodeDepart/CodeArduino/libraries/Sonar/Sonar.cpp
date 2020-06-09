/*
Projet S3 GRO
Class to use HC-SR04 sonar sensor
@author Jean-Samuel Lauzon
@version 1.0 30/04/2020
*/

#include "Sonar.h"

Sonar::Sonar(uint8_t trigPin, uint8_t echoPin){
    trigPin_ = trigPin;
    echoPin_ = echoPin;
    pinMode(trigPin_, OUTPUT);
    pinMode(echoPin_, INPUT);
}

float Sonar::getRange(){
      digitalWrite(trigPin_, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin_, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin_, LOW);
      long duration = pulseIn(echoPin_, HIGH);
      // Calculating the distance
      return duration*0.34/2.0;
}
