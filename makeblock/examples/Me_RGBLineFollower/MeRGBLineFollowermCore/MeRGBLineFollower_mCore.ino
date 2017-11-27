#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

//#include <MeMegaPiPro.h>
#include "MeMCore.h"
#include "MeRGBLineFollower.h"

MeRGBLineFollower RGBLineFollower1(PORT_1,0);
MeRGBLineFollower RGBLineFollower2(PORT_2,1);
MeRGBLineFollower RGBLineFollower3(PORT_3,2);
MeRGBLineFollower RGBLineFollower4(PORT_4,3);

MeDCMotor motor1(M1);
MeDCMotor motor2(M2);

int16_t turnoffset1,turnoffset2,turnoffset3,turnoffset4;
uint8_t sensorstate1,sensorstate2,sensorstate3,sensorstate4;
bool study_state1,study_state2,study_state3,study_state4;
uint8_t address1,address2,address3,address4;

uint8_t motorSpeed = 100;

uint8_t valueS1;
uint8_t valueS2;
uint8_t valueS3;
uint8_t valueS4;


void setup()
{
	RGBLineFollower1.begin();
	RGBLineFollower2.begin();
	RGBLineFollower3.begin();
	RGBLineFollower4.begin();

	RGBLineFollower1.setKp(0.2);
	RGBLineFollower2.setKp(0.2);
	RGBLineFollower3.setKp(0.2);
	RGBLineFollower4.setKp(0.2);

	Serial.begin(115200);
  delay(1000);
}

void loop()
{
	RGBLineFollower1.loop();
	RGBLineFollower2.loop();
	RGBLineFollower3.loop();
	RGBLineFollower4.loop();

  
   motor1.run(-motorSpeed); /* value: between -255 and 255. */
  motor2.run(motorSpeed); /* value: between -255 and 255. */
	study_state1 = RGBLineFollower1.getStudyFlag();
	study_state2 = RGBLineFollower2.getStudyFlag();
	study_state3 = RGBLineFollower3.getStudyFlag();
	study_state4 = RGBLineFollower4.getStudyFlag();
	
	turnoffset1 = RGBLineFollower1.getPositionOffset();
	turnoffset2 = RGBLineFollower2.getPositionOffset();
	turnoffset3 = RGBLineFollower3.getPositionOffset();
	turnoffset4 = RGBLineFollower4.getPositionOffset();
	
	sensorstate1 = RGBLineFollower1.getPositionState();
	sensorstate2 = RGBLineFollower2.getPositionState();
	sensorstate3 = RGBLineFollower3.getPositionState();
	sensorstate4 = RGBLineFollower4.getPositionState();

	address1 = RGBLineFollower1.getDevAddr();
	address2 = RGBLineFollower2.getDevAddr();
	address3 = RGBLineFollower3.getDevAddr();
	address4 = RGBLineFollower4.getDevAddr();

  valueS1 = RGBLineFollower1.getADCValueRGB1();
  //valueS2 = RGBLineFollower2.getADCValueS2();
  //valueS3 = RGBLineFollower3.getADCValueS3();
  //valueS4 = RGBLineFollower4.getADCValueS4();

    Serial.print(valueS1);
  Serial.print(", ");
  Serial.print(valueS2);
  Serial.print(", ");
  Serial.print(valueS3);
  Serial.print(", ");
  Serial.print(valueS4);
  Serial.println(",,, ");

  if(valueS1 < 68)
  {
    Serial.print(valueS1);
    while(1)
    {
      motor1.stop();
      motor2.stop();

      valueS1 = RGBLineFollower1.getADCValueRGB1();
      //Serial.print(valueS1);


    }
  }

}

