#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <MeMegaPiPro.h>


MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);
MeEncoderOnBoard Encoder_3(SLOT3);
MeEncoderOnBoard Encoder_4(SLOT4);
Me4Button btn(PORT_8);
MeLightSensorRGB LightSensorRGB(PORT_9, 3);

uint8_t keyPressed = KEY_NULL;
uint8_t keyPressedPrevious = KEY_NULL;
int16_t turnoffset = 0;
uint8_t sensorstate;
int16_t set_speed = 0;
uint8_t run_flag = 0;
uint8_t study_flag1 = 0;
unsigned long motor_ctrl_time = 0;
unsigned long printf_time = 0;

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

		LightSensorRGB.begin();
		LightSensorRGB.setKp(0.15);
    Serial.begin(115200);

    Serial.println("init ok...");
    
}

void loop()
{
		
	Encoder_3.loop();
	Encoder_4.loop();
 	LightSensorRGB.loop();
	
  keyPressedPrevious = keyPressed;
  keyPressed = btn.pressed();
  if (keyPressedPrevious != keyPressed)
  {
    if (keyPressed == KEY_3)
    {
    	run_flag = 1;
      Serial.println("KEY3 pressed");
    }
    if (keyPressed == KEY_4)
    {
    	run_flag = 0;
      Serial.println("KEY4 pressed");
    }
    if (keyPressed == KEY_NULL)
    {
      Serial.println("KEY NULL");
    }
  }
	
  if(millis() - motor_ctrl_time > 10)  
  { 
		study_flag1 = LightSensorRGB.getStudyFlag();
		sensorstate = LightSensorRGB.getPositionState();
		turnoffset = LightSensorRGB.getPositionOffset();
  		
  	if((run_flag == 1) && (study_flag1 == 0))
		{
		  motor_ctrl_time = millis(); 
		  if(set_speed < 100)
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
	  	run_flag = 0;
	 		Encoder_3.setTarPWM(0);
	    Encoder_4.setTarPWM(-0);
	  }
  }

  if(millis() - printf_time > 500)  
  {    
	  printf_time = millis();  
	  Serial.print(study_flag1);
	  Serial.print(", ");
	  Serial.print(run_flag);
	  Serial.print(", ");
	  Serial.print(sensorstate);
	  Serial.print(", ");
 		Serial.println(turnoffset);

 		Serial.println(LightSensorRGB.getDevAddr());
  }

}

