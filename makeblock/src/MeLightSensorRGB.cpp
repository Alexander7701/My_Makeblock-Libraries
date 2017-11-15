/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class   MeLightSensorRGB
 * \brief   Driver for MeLightSensorRGB module.
 * @file    MeLightSensorRGB.cpp
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2017/09/26
 * @brief   Driver for MeLightSensorRGB module.
 *
 * \par Copyright
 * This software is Copyright (C), 2012-2016, MakeBlock. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * \par Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * \par Description
 * This file is a drive for MeLightSensorRGB module, It supports MeLightSensorRGB V1.0 device provided
 * by MakeBlock.
 *
 * \par Method List:
 *
 *    1. void MeLightSensorRGB::setpin(uint8_t AD0, uint8_t INT)
 *    2. void MeLightSensorRGB::begin(void)
 *    3. void MeLightSensorRGB::update(void)
 *    4. void MeLightSensorRGB::fast_update(void)
 *    5. uint8_t MeLightSensorRGB::getDevAddr(void)
 *    6. double MeLightSensorRGB::getAngleX(void)
 *    7. double MeLightSensorRGB::getAngleY(void)
 *    8. double MeLightSensorRGB::getAngleZ(void)
 *    9. double MeLightSensorRGB::getGyroX(void)
 *    10. double MeLightSensorRGB::getGyroY(void)
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 *  Payton            2017/09/26        1.0.0         rebuild the old lib.
 * </pre>
 *
 * @example MeLightSensorRGBTest.ino
 */

/* Includes ------------------------------------------------------------------*/
#include "MeLightSensorRGB.h"

  
//????????
#define LIMIT_DEATH(x, a)	if( (((x) > 0) && ((x) < (a))) ) (x) = 0;\
            							else if((x) >= (a)) (x) = (x) - (a);\
            							else if( (((x) <= 0) && ((x) >= -(a))) ) (x) = 0;	\
            							else (x) = (x) + (a);


/* Private functions ---------------------------------------------------------*/
#ifdef ME_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the MeLightSensorRGB to arduino port,
 * no pins are used or initialized here
 */
MeLightSensorRGB::MeLightSensorRGB(void) : MePort(0)
{
  Device_Address = LIGHTSENSORRGB_DEFAULT_ADDRESS;
}

/**
 * Alternate Constructor which can call your own function to map the MeLightSensorRGB to arduino port,
 * no pins are used or initialized here, but PWM frequency set to 976 Hz
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
MeLightSensorRGB::MeLightSensorRGB(uint8_t port) : MePort(port)
{
  Device_Address = LIGHTSENSORRGB_DEFAULT_ADDRESS;
}

/**
 * Alternate Constructor which can call your own function to map the MeLightSensorRGB to arduino port
 * and change the i2c device address
 * no pins are used or initialized here, but PWM frequency set to 976 Hz
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \param[in]
 *   address - the i2c address you want to set
 */
MeLightSensorRGB::MeLightSensorRGB(uint8_t port, uint8_t address) : MePort(port)
{
	Device_Address = LIGHTSENSORRGB_DEFAULT_ADDRESS + address;

  //address0-11, address1-10, address2-01, address3-00
	pinMode(s1, OUTPUT);
	pinMode(s2, OUTPUT);
  if(address == 0)
  {
  	digitalWrite(s1,HIGH);
  	digitalWrite(s2,HIGH);
	}
	else if(address == 1)
  {
  	digitalWrite(s1,LOW);
  	digitalWrite(s2,HIGH);
	}
	else if(address == 2)
  {
  	digitalWrite(s1,HIGH);
  	digitalWrite(s2,LOW);
	}
	else if(address == 3)
  {
  	digitalWrite(s1,LOW);
  	digitalWrite(s2,LOW);
	}
	else
	{ 
    digitalWrite(s1,HIGH);
  	digitalWrite(s2,HIGH);
	}
}
#else  // ME_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the _AD0 and _INT to arduino port,
 * no pins are used or initialized here
 * \param[in]
 *   _AD0 - arduino gpio number
 * \param[in]
 *   _INT - arduino gpio number
 */
MeLightSensorRGB::MeLightSensorRGB(uint8_t AD0, uint8_t INT)
{
  Device_Address = LIGHTSENSORRGB_DEFAULT_ADDRESS;
  _AD0 = AD0;
  _INT = INT;
}

/**
 * Alternate Constructor which can call your own function to map the _AD0 and _INT to arduino port
 * and change the i2c device address, no pins are used or initialized here
 * \param[in]
 *   _AD0 - arduino gpio number
 * \param[in]
 *   _INT - arduino gpio number
 * \param[in]
 *   address - the i2c address you want to set
 */
MeLightSensorRGB::MeLightSensorRGB(uint8_t AD0, uint8_t INT, uint8_t address)
{
  Device_Address = address;
  _AD0 = AD0;
  _INT = INT;
}
#endif // ME_PORT_DEFINED

/**
 * \par Function
 *   setpin
 * \par Description
 *   Set the PIN of the button module.
 * \param[in]
 *   AD0 - pin mapping for arduino
 * \param[in]
 *   INT - pin mapping for arduino
 * \par Output
 *   None
 * \return
 *   None.
 * \par Others
 *   Set global variable _AD0, _INT, s1 and s2
 */
void MeLightSensorRGB::setpin(uint8_t AD0, uint8_t INT)
{
  _AD0 = AD0;
  _INT = INT;
#ifdef ME_PORT_DEFINED
  s1 = AD0;
  s2 = INT;
#endif // ME_PORT_DEFINED
}

/**
 * \par Function
 *   begin
 * \par Description
 *   Initialize the MeLightSensorRGB.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   
 */
void MeLightSensorRGB::begin(void)
{
  uint8_t i;
  
  for(i=0; i<LIGHTSENSOR_RGB_NUM; i++)
  {

  }
  Kp = 0.1;
  study_flag = false;
  iic_error_count = 0;
  
  Wire.begin();
  delay(10);
}

/**
 * \par Function
 *   getDevAddr
 * \par Description
 *   Get the device address of Gyro.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   The device address of Gyro
 * \par Others
 *   None
 */
uint8_t MeLightSensorRGB::getDevAddr(void)
{
  return Device_Address;
}

/**
 * \par Function
 *   getADCValueS1
 * \par Description
 *   Get the S1 sensor ADC value.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   The ADC value of S1
 * \par Others
 *   
 */
uint8_t MeLightSensorRGB::getADCValueS1(void)
{
  int8_t return_value;
  /* read data */
  return_value = readData(LIGHTSENSOR_RGB_DATA_S1, &i2cData[0], 1);
  if(return_value == I2C_OK)
  {
    adcOutput[0] = i2cData[0];
  }

  return adcOutput[0];
}

/**
 * \par Function
 *   getADCValueS2
 * \par Description
 *   Get the S2 sensor ADC value.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   The ADC value of S2
 * \par Others
 *   
 */
uint8_t MeLightSensorRGB::getADCValueS2(void)
{
  int8_t return_value;
  /* read data */
  return_value = readData(LIGHTSENSOR_RGB_DATA_S2, &i2cData[1], 1);
  if(return_value == I2C_OK)
  {
    adcOutput[1] = i2cData[1];
  }

  return adcOutput[1];

}

/**
 * \par Function
 *   getADCValueS3
 * \par Description
 *   Get the S3 sensor ADC value.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   The ADC value of S3
 * \par Others
 *   
 */
uint8_t MeLightSensorRGB::getADCValueS3(void)
{
  int8_t return_value;
  /* read data */
  return_value = readData(LIGHTSENSOR_RGB_DATA_S3, &i2cData[2], 1);
  if(return_value == I2C_OK)
  {
    adcOutput[2] = i2cData[2];
  }

  return adcOutput[2];

}

/**
 * \par Function
 *   getADCValueS4
 * \par Description
 *   Get the S4 sensor ADC value.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   The ADC value of S4
 * \par Others
 *   
 */
uint8_t MeLightSensorRGB::getADCValueS4(void)
{
  int8_t return_value;
  /* read data */
  return_value = readData(LIGHTSENSOR_RGB_DATA_S4, &i2cData[3], 1);
  if(return_value == I2C_OK)
  {
    adcOutput[3] = i2cData[3];
  }

  return adcOutput[3];
}

/**
 * \par Function
 *   getAllADCValue
 * \par Description
 *   Get the S1??S2??S3??S4 sensor ADC value.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *  
 */
void MeLightSensorRGB::getAllADCValue(uint8_t *adcbuff, uint8_t size)
{
  int8_t return_value;
      
  /* read data */
  return_value = readData(LIGHTSENSOR_RGB_DATA_S1, i2cData, size);
  if(return_value == I2C_OK)
  {
    memcpy(adcOutput, i2cData, size);
  }

  memcpy(adcbuff, adcOutput, size);
}

/**
 * \par Function
 *   setKp
 * \par Description
 *   set Kp.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *  
 */
void MeLightSensorRGB::setKp(float value)
{
  if((value >= 0) && (value <= 1))
  {
    Kp = value;
  }
}

/**
 * \par Function
 *   getPositionOffset
 * \par Description
 *   get turn Value.
 * \param[in]
 *   Speed:set forward speed
 * \par Output
 *   None
 * \return
 *   Position offset Value,-512 ~ 512
      <0,in right
      >0,in left
 * \par Others
 *   |--------------------------|
     |     |      |      |      |
     |  S1 |  S2  |  S3  |  S4  |
     |     |      |      |      |
     |--------------------------|
 */
int16_t MeLightSensorRGB::getPositionOffset(void)
{
  return positionOffset;
}

/**
 * \par Function
 *   getPositionState
 * \par Description
 *   get turn Value.
 * \param[in]
 *   Speed:set forward speed
 * \par Output
 *   None
 * \return
 *   Position offset Value,-255 ~ 255
      <0,in right
      >0,in left
 * \par Others
 *   |--------------------------|
     |     |      |      |      |
     |  S1 |  S2  |  S3  |  S4  |
     |     |      |      |      |
     |--------------------------|
 */
uint8_t MeLightSensorRGB::getPositionState(void)
{
  return positionState;
}

/**
 * \par Function
 *   getPositionState
 * \par Description
 *   get turn Value.
 * \param[in]
 *   Speed:set forward speed
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 */
uint8_t MeLightSensorRGB::getIicErrorCnt(void)
{
  return iic_error_count;
}

/**
 * \par Function
 *   getStudyFlag
 * \par Description
 *   get turn Value.
 * \param[in]
 *   Speed:set forward speed
 * \par Output
 *   None
 * \return
 *   
 * \par Others
 */
uint8_t MeLightSensorRGB::getStudyFlag(void)
{
  return study_flag;
}

/**
 * \par Function
 *   updataAllSensorValue
 * \par Description
 *   updata All Sensor Value.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   
 * \par Others
 */
void MeLightSensorRGB::updataAllSensorValue(void)
{
  int8_t return_value;
  int16_t temp_positionOffset;
  
  /* read data */
  return_value = readData(LIGHTSENSOR_RGB_STATE, &i2cData[4], 3);
  if(return_value == I2C_OK)
  {
    if(i2cData[4] <= 0x1F)
    {
      positionState = i2cData[4] & 0x0F;
      study_flag = (i2cData[4]>>4) & 0x01;
      temp_positionOffset = (int16_t)(i2cData[5] | ((uint16_t)i2cData[6]<<8));
      temp_positionOffset = (int16_t)(Kp * temp_positionOffset);
      positionOffset= constrain(temp_positionOffset, -512, 512);
    }
    else
    {
      iic_error_count++;  
    }
  }
}

/**
 * \par Function
 *   writeReg
 * \par Description
 *   Write the registor of i2c device.
 * \param[in]
 *   reg - the address of registor.
 * \param[in]
 *   data - the data that will be written to the registor.
 * \par Output
 *   None
 * \return
 *   Return the error code.
 *   the definition of the value of variable return_value:
 *   0:success
 *   1:BUFFER_LENGTH is shorter than size
 *   2:address send, nack received
 *   3:data send, nack received
 *   4:other twi error
 *   refer to the arduino official library twi.c
 * \par Others
 *   To set the registor for initializing.
 */
int8_t MeLightSensorRGB::writeReg(int16_t reg, uint8_t data)
{
  int8_t return_value = 0;
  return_value = writeData(reg, &data, 1);
  return(return_value);
}

/**
 * \par Function
 *   readData
 * \par Description
 *   Write the data to i2c device.
 * \param[in]
 *   start - the address which will write the data to.
 * \param[in]
 *   pData - the head address of data array.
 * \param[in]
 *   size - set the number of data will be written to the devide.
 * \par Output
 *   None
 * \return
 *   Return the error code.
 *   the definition of the value of variable return_value:
 *   0:success
 *   1:BUFFER_LENGTH is shorter than size
 *   2:address send, nack received
 *   3:data send, nack received
 *   4:other twi error
 *   refer to the arduino official library twi.c
 * \par Others
 *   Calling the official i2c library to read data.
 */
int8_t MeLightSensorRGB::readData(uint8_t start, uint8_t *buffer, uint8_t size)
{
  int16_t i = 0;
  int8_t return_value = 0;

  Wire.beginTransmission(Device_Address);
  return_value = Wire.write(start);
  if(return_value != 1)
  {
    return(I2C_ERROR);
  }
  return_value = Wire.endTransmission(false);
  if(return_value != 0)
  {
    return(I2C_ERROR);
    //return(return_value);
  }
  delayMicroseconds(1);
  /* Third parameter is true: relase I2C-bus after data is read. */
  Wire.requestFrom(Device_Address, size, (uint8_t)true);
  while(Wire.available() && i < size)
  {
    buffer[i++] = Wire.read();
  }
  delayMicroseconds(1);
  if(i != size)
  {
    return(I2C_ERROR);
  }
  return(0); //return: no error 
}

/**
 * \par Function
 *   writeData
 * \par Description
 *   Write the data to i2c device.
 * \param[in]
 *   start - the address which will write the data to.
 * \param[in]
 *   pData - the head address of data array.
 * \param[in]
 *   size - set the number of data will be written to the devide.
 * \par Output
 *   None
 * \return
 *   Return the error code.
 *   the definition of the value of variable return_value:
 *   0:success
 *   1:BUFFER_LENGTH is shorter than size
 *   2:address send, nack received
 *   3:data send, nack received
 *   4:other twi error
 *   refer to the arduino official library twi.c
 * \par Others
 *   Calling the official i2c library to write data.
 */
int8_t MeLightSensorRGB::writeData(uint8_t start, const uint8_t *pData, uint8_t size)
{
  int8_t return_value = 0;
  Wire.beginTransmission(Device_Address);
  return_value = Wire.write(start); 
  if(return_value != 1)
  {
    return(I2C_ERROR);
  }
  Wire.write(pData, size);  
  return_value = Wire.endTransmission(true); 
  return(return_value); //return: no error                     
}

void MeLightSensorRGB::loop(void)
{
  static unsigned long updata_time = 0;
  if(millis() - updata_time > 8)  
  {    
	  updata_time = millis();  
    updataAllSensorValue();
  }
	delay(1);
}
