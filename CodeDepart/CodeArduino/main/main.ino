/* 
 * GRO 302 - Conception d'un robot mobile
 * Code de démarrage
 * Auteurs: Jean-Samuel Lauzon     
 * date: 15 mai 2020
*/

/*------------------------------ Librairies ---------------------------------*/
#include <ArduinoJson.h>
#include <Capteur_MPU6050.h>
#include <MPU6050.h>
#include <Sonar.h>
#include <MotorControl.h>

#include <SoftTimer.h>
#include <ArduinoJson.h>
#include <PID.h>
/*------------------------------ Constantes ---------------------------------*/

#define BAUD            115200      // Frequence de transmission serielle
#define UPDATE_PERIODE  100         // Periode (ms) d'envoie d'etat general

/*---------------------------- variables globales ---------------------------*/
Capteur_MPU6050 imu_;                 // Objet IMU
double angleX;                        // Variable pour angle X
double angleY;                        // Variable pour angle Y

MotorControl motor_(13, 12, 11, 10);  // Objet moteur
Sonar rangeSensor_(9,8);              // Objet sonar

volatile bool shouldSend_ = false;    // drapeau prêt à envoyer un message
volatile bool shouldRead_ = false;    // drapeau prêt à lire un message
volatile bool shouldPulse_ = false;   // drapeau pour effectuer un pulse
volatile bool isInPulse_ = false;     // drapeau pour effectuer un pulse
uint16_t pulseTime_ = 0;              // temps dun pulse en ms
float pulsePWM_ = 0;                  // amplitude de la tension au moteur [-1,1]

String error_;                        // message d'erreur pour le deverminage
SoftTimer timerSendMsg_;              // chronometre d'envoie de messages
SoftTimer timerPulse_;                // chronometre pour la duree d'un pulse
/*------------------------- Prototypes de fonctions -------------------------*/

void serialEvent();
void sendSerial();
void readSerial();
void endPulse();
void startPulse();


/*---------------------------- fonctions "Main" -----------------------------*/
void setup() {
  Serial.begin(BAUD);
  
  // Initialisation imu
  imu_.init();
  
  // Power Sonar
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  // Chronometre envoie message
  timerSendMsg_.setDelay(UPDATE_PERIODE);
  timerSendMsg_.setCallback(sendSerial);
  timerSendMsg_.enable();

  // Chronometre duration pulse
  timerPulse_.setCallback(endPulse);
}

void loop() {
  if(shouldRead_){
    readSerial();
  }
  if(shouldPulse_){
    startPulse();
  }
  timerSendMsg_.update();
  timerPulse_.update();
}

/*---------------------------Definition de fonctions ------------------------*/
void serialEvent(){
  shouldRead_=true;
}

//Lire message du RPI
void readSerial(){
    StaticJsonDocument<512> doc;
    DeserializationError err = deserializeJson(doc, Serial);
    if (err) {
      error_ = "erreur deserialisation.";
      return;
    }else{
      error_ = "";
    }
    // Analyse du message
    bool pulse = doc["pulse"];
    if (pulse) {
      shouldPulse_ = true;
    }

    uint16_t pulseTime = doc["pulseTime"];
    if (pulseTime) {
      pulseTime_ = pulseTime;
    }
    
    float pulsePWM = doc["pulsePWM"];
    if (pulsePWM) {
      pulsePWM_ = pulsePWM;
    }
    
  
    shouldRead_=false;
}

//Envoi d'un message au RPI
void sendSerial(){
  StaticJsonDocument<512> doc;
  // Construction du message a envoyer
  imu_.getAngles(&angleX,&angleY, 1);
  doc["time"] = millis();
  doc["angleX"] = angleX;
  doc["angleY"] = angleY;
  doc["sonar"] = rangeSensor_.getRange();
  doc["error"] = error_;
  doc["inPulse"] = isInPulse_;
  // Serialisation
  serializeJson(doc, Serial);
  // Envoit
  Serial.println();
}

void endPulse(){
  /* Rappel du chronometre */
  motor_.setPWM(0);
  timerPulse_.disable();
  isInPulse_ = false;
}

void startPulse(){
  /* Demarrage d'un pulse */
  timerPulse_.setDelay(pulseTime_);
  timerPulse_.enable();
  timerPulse_.setRepetition(1);
  motor_.setPWM(pulsePWM_);
  shouldPulse_ = false;
  isInPulse_ = true;
}
