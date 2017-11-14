#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <MeMegaPiPro.h>
#include "MeLightSensorRGB.h"



MeLightSensorRGB LightSensorRGB1(PORT_6,0);
MeLightSensorRGB LightSensorRGB2(PORT_7,1);
MeLightSensorRGB LightSensorRGB3(PORT_8,2);
MeLightSensorRGB LightSensorRGB4(PORT_9,3);

int16_t turnoffset1,turnoffset2,turnoffset3,turnoffset4;
uint8_t sensorstate1,sensorstate2,sensorstate3,sensorstate4;
bool study_flag1,study_flag2,study_flag3,study_flag4;
uint8_t address1,address2,address3,address4;

void setup()
{
		LightSensorRGB1.begin();
		LightSensorRGB2.begin();
		LightSensorRGB3.begin();
		LightSensorRGB4.begin();
		
		LightSensorRGB1.setKp(0.1);//4.设置RGB巡线传感器转向灵敏度Kp
		LightSensorRGB2.setKp(0.1);
		LightSensorRGB3.setKp(0.1);
		LightSensorRGB4.setKp(0.1);
		
    Serial.begin(115200);
}

void loop()
{
	LightSensorRGB1.loop();
	LightSensorRGB2.loop();
	LightSensorRGB3.loop();
	LightSensorRGB4.loop();
	
	study_flag1 = LightSensorRGB1.getStudyFlag();//3.获取RGB巡线传感器是否在学习中
	study_flag2 = LightSensorRGB2.getStudyFlag();
	study_flag3 = LightSensorRGB3.getStudyFlag();
	study_flag4 = LightSensorRGB4.getStudyFlag();
	
	turnoffset1 = LightSensorRGB1.getPositionOffset();//1.获取RGB巡线传感器位置偏移量
	turnoffset2 = LightSensorRGB2.getPositionOffset();
	turnoffset3 = LightSensorRGB3.getPositionOffset();
	turnoffset4 = LightSensorRGB4.getPositionOffset();
	
	sensorstate1 = LightSensorRGB1.getPositionState();//2.获取RGB巡线传感器状态位:bit0~bit3分别表示四组传感器状态
	sensorstate2 = LightSensorRGB2.getPositionState();
	sensorstate3 = LightSensorRGB3.getPositionState();
	sensorstate4 = LightSensorRGB4.getPositionState();

	address1 = LightSensorRGB1.getDevAddr();
	address2 = LightSensorRGB2.getDevAddr();
	address3 = LightSensorRGB3.getDevAddr();
	address4 = LightSensorRGB4.getDevAddr();

	Serial.print(address1);
	Serial.print(", ");
	Serial.print(address2);
	Serial.print(", ");
	Serial.print(address3);
	Serial.print(", ");
	Serial.print(address4);
	Serial.print(",,, ");

	Serial.print(study_flag1);
	Serial.print(", ");
	Serial.print(study_flag2);
	Serial.print(", ");
	Serial.print(study_flag3);
	Serial.print(", ");
	Serial.print(study_flag4);
	Serial.print(",,, ");
	
	Serial.print(turnoffset1);
	Serial.print(", ");
	Serial.print(turnoffset2);
	Serial.print(", ");
	Serial.print(turnoffset3);
	Serial.print(", ");
	Serial.print(turnoffset4);
	Serial.print(",,, ");

	Serial.print(sensorstate1);
	Serial.print(", ");
	Serial.print(sensorstate2);
	Serial.print(", ");
	Serial.print(sensorstate3);
	Serial.print(", ");
	Serial.println(sensorstate4);

}


