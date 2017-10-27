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
		LightSensorRGB.setKp(0.18);//4.����RGBѲ�ߴ�����ת��������Kp
    Serial.begin(115200);
}

void loop()
{
	study_flag = LightSensorRGB.getStudyFlag();//3.��ȡRGBѲ�ߴ������Ƿ���ѧϰ��
	turnoffset = LightSensorRGB.getPositionOffset();//1.��ȡRGBѲ�ߴ�����λ��ƫ����
	sensorstate = LightSensorRGB.getPositionState();//2.��ȡRGBѲ�ߴ�����״̬λ:bit0~bit3�ֱ��ʾ���鴫����״̬


	Serial.print(study_flag);
	Serial.print(", ");
	Serial.print(turnoffset);
	Serial.print(", ");
	Serial.println(sensorstate);
	}


