#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <MeMegaPiPro.h>
#include "MeRGBLineFollower.h"
#include "MeEnhanceEncoderOnBoard.h"

MeEnhanceEncoderOnBoard Encoder_1(SLOT1);
MeEnhanceEncoderOnBoard Encoder_2(SLOT2);
MeEnhanceEncoderOnBoard Encoder_3(SLOT3);
MeEnhanceEncoderOnBoard Encoder_4(SLOT4);
MeRGBLineFollower RGBLineFollower(PORT_9, 1);
Me4Button btn(PORT_8);

int16_t turnoffset = 0;
uint8_t sensorstate;
int16_t set_speed = 0;
bool run_flag = false;
bool study_flag = false;

void isr_process_encoder1(void)
{
    if(digitalRead(Encoder_1.getPortB()) == 0){
        Encoder_1.pulsePosMinus();
    }else{
        Encoder_1.pulsePosPlus();
    }
}
void isr_process_encoder2(void)
{
    if(digitalRead(Encoder_2.getPortB()) == 0){
        Encoder_2.pulsePosMinus();
    }else{
        Encoder_2.pulsePosPlus();
    }
}
void isr_process_encoder3(void)
{
    if(digitalRead(Encoder_3.getPortB()) == 0){
        Encoder_3.pulsePosMinus();
    }else{
        Encoder_3.pulsePosPlus();
    }
}
void isr_process_encoder4(void)
{
    if(digitalRead(Encoder_4.getPortB()) == 0){
        Encoder_4.pulsePosMinus();
    }else{
        Encoder_4.pulsePosPlus();
    }
}

void setup(){
    TCCR1A = _BV(WGM10);//PIN12
    TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);
    
    TCCR2A = _BV(WGM21) | _BV(WGM20);//PIN8
    TCCR2B = _BV(CS22);
    
    TCCR3A = _BV(WGM30);//PIN9
    TCCR3B = _BV(CS31) | _BV(CS30) | _BV(WGM32);
    
    TCCR4A = _BV(WGM40);//PIN5
    TCCR4B = _BV(CS41) | _BV(CS40) | _BV(WGM42);
    
    attachInterrupt(Encoder_3.getIntNum(), isr_process_encoder3, RISING);
    attachInterrupt(Encoder_4.getIntNum(), isr_process_encoder4, RISING);

		RGBLineFollower.begin();
		RGBLineFollower.setKp(0.4);
    Serial.begin(115200);

    Serial.println("init ok...");
    
}

void loop()
{
	Encoder_3.loop();
	Encoder_4.loop();
 	RGBLineFollower.loop();

	study_flag = RGBLineFollower.getStudyFlag();
	sensorstate = RGBLineFollower.getPositionState();
	turnoffset = RGBLineFollower.getPositionOffset();

  if (btn.pressed() == KEY_3)
  {
  	run_flag = true;
    Serial.println("KEY3 pressed");
  }

	if((run_flag == true) && (study_flag == false))
	{
	  if(set_speed < 80)
	  {
			set_speed++;
	  }
		Encoder_3.setTarPWM(set_speed + turnoffset);
  	Encoder_4.setTarPWM(-(set_speed - turnoffset));	
	}
  else
  {
  	turnoffset = 0;
  	set_speed = 0;
  	run_flag = false;
 		Encoder_3.setTarPWM(0);
    Encoder_4.setTarPWM	(-0);
  }
}

