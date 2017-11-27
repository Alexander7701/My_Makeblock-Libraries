#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <MeMegaPiPro.h>
#include "MeEnhanceEncoderOnBoard.h"

MeEnhanceEncoderOnBoard Encoder_1(SLOT1);
MeEnhanceEncoderOnBoard Encoder_2(SLOT2);

void isr_process_encoder1(void)
{
  if(digitalRead(Encoder_1.getPortB()) == 0)
  {
    Encoder_1.pulsePosMinus();
  }
  else
  {
    Encoder_1.pulsePosPlus();;
  }
}

void isr_process_encoder2(void)
{
  if(digitalRead(Encoder_2.getPortB()) == 0)
  {
    Encoder_2.pulsePosMinus();
  }
  else
  {
    Encoder_2.pulsePosPlus();
  }
}

void setup()
{
  attachInterrupt(Encoder_1.getIntNum(), isr_process_encoder1, RISING);
  attachInterrupt(Encoder_2.getIntNum(), isr_process_encoder2, RISING);
  Serial.begin(115200);
  
  TCCR1A = _BV(WGM10);//PIN12
  TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);

  TCCR2A = _BV(WGM21) | _BV(WGM20);//PIN8
  TCCR2B = _BV(CS22);

  TCCR3A = _BV(WGM30);//PIN9
  TCCR3B = _BV(CS31) | _BV(CS30) | _BV(WGM32);

  TCCR4A = _BV(WGM40);//PIN5
  TCCR4B = _BV(CS41) | _BV(CS40) | _BV(WGM42);
}

void loop()
{
  if(Serial.available())
  {
    char a = Serial.read();
    switch(a)
    {
      case '0':
      Encoder_1.setTarPWM(0);
      Encoder_2.setTarPWM(0);
      break;
      case '1':
      Encoder_1.setTarPWM(100);
      Encoder_2.setTarPWM(-100);
      break;
      case '2':
      Encoder_1.setTarPWM(200);
      Encoder_2.setTarPWM(-200);
      break;
      case '3':
      Encoder_1.setTarPWM(255);
      Encoder_2.setTarPWM(-255);
      break;
      case '4':
      Encoder_1.setTarPWM(-100);
      Encoder_2.setTarPWM(100);
      break;
      case '5':
      Encoder_1.setTarPWM(-200);
      Encoder_2.setTarPWM(200);
      break;
      case '6':
      Encoder_1.setTarPWM(-255);
      Encoder_2.setTarPWM(255);
      break;
      default:
      break;
    }
  }
  Encoder_1.loop();
  Encoder_2.loop();
  Serial.print("Spped 1:");
  Serial.print(Encoder_1.getCurrentSpeed());
  Serial.print(" ,Spped 2:");
  Serial.println(Encoder_2.getCurrentSpeed());
}

