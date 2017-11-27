#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <MeMegaPiPro.h>
#include "MeRGBLineFollower.h"

MeRGBLineFollower RGBLineFollower1(PORT_9,DEVICE2);
MeRGBLineFollower RGBLineFollower2(PORT_7,DEVICE3);


int16_t turnoffset1,turnoffset2;
uint8_t sensorstate1,sensorstate2;
bool study_state1,study_state2;
uint8_t address1,address2;
uint8_t ADCValueRGB1[4],ADCValueRGB2[4];


void setup()
{
  RGBLineFollower1.begin();
  RGBLineFollower2.begin();

  RGBLineFollower1.setKp(0.2);
  RGBLineFollower2.setKp(0.2);

  Serial.begin(115200);
}

void loop()
{
  RGBLineFollower1.loop();
  RGBLineFollower2.loop();

  study_state1 = RGBLineFollower1.getStudyFlag();
  turnoffset1 = RGBLineFollower1.getPositionOffset();
  sensorstate1 = RGBLineFollower1.getPositionState();
  address1 = RGBLineFollower1.getDevAddr();
  ADCValueRGB1[0] = RGBLineFollower1.getADCValueRGB1();
  ADCValueRGB1[1] = RGBLineFollower1.getADCValueRGB2();
  ADCValueRGB1[2] = RGBLineFollower1.getADCValueRGB3();
  ADCValueRGB1[3] = RGBLineFollower1.getADCValueRGB4();

  study_state2 = RGBLineFollower2.getStudyFlag();
  turnoffset2 = RGBLineFollower2.getPositionOffset();
  sensorstate2 = RGBLineFollower2.getPositionState();
  address2 = RGBLineFollower2.getDevAddr();
  ADCValueRGB2[0] = RGBLineFollower2.getADCValueRGB1();
  ADCValueRGB2[1] = RGBLineFollower2.getADCValueRGB2();
  ADCValueRGB2[2] = RGBLineFollower2.getADCValueRGB3();
  ADCValueRGB2[3] = RGBLineFollower2.getADCValueRGB4();

  if(Serial.available())
  {
    char a = Serial.read();
    switch(a)
    {
      case '1':
        Serial.println("studyBackground 1");
        RGBLineFollower1.studyBackground();
      break;
      case '2':
        Serial.println("studyTrack 1");
        RGBLineFollower1.studyTrack();
      break;
      case '3':
        Serial.println("studyBackground 2");
        RGBLineFollower2.studyBackground();
      break;
      case '4':
        Serial.println("studyTrack 2");
        RGBLineFollower2.studyTrack();
      break;
      default:
      break;
    }
  }

  Serial.print("address1: ");
  Serial.print(address1);
    Serial.print("  address2: ");
  Serial.print(address2);

  Serial.print("  turnoffset1:");
  Serial.print(turnoffset1);

   Serial.print("  turnoffset2:");
  Serial.print(turnoffset2);
  
  Serial.println("");

  delay(100);
}
