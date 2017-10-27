#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <MeMegaPiPro.h>


MeLightSensorRGB LightSensorRGB;

int16_t turnoffset;
uint8_t sensorstate;
bool study_flag;


void setup(){
		LightSensorRGB.begin();
		LightSensorRGB.setKp(0.18);//4.设置RGB巡线传感器转向灵敏度Kp
    Serial.begin(115200);
}

void loop()
{
	study_flag = LightSensorRGB.getStudyFlag();//3.获取RGB巡线传感器是否在学习中
	turnoffset = LightSensorRGB.getPositionOffset();//1.获取RGB巡线传感器位置偏移量
	sensorstate = LightSensorRGB.getPositionState();//2.获取RGB巡线传感器状态位:bit0~bit3分别表示四组传感器状态


	Serial.print(study_flag);
	Serial.print(", ");
	Serial.print(turnoffset);
	Serial.print(", ");
	Serial.println(sensorstate);
	}


