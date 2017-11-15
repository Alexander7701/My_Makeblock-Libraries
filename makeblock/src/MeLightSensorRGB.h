/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class   MeLightSensorRGB
 * \brief   Driver for LingSensorRGB module.
 * @file    MeLightSensorRGB.h
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2017/09/26
 * @brief   Header for MeLightSensorRGB.cpp module.
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
 *  Payton            2017/09/26          1.0.0         rebuild the old lib.
 * </pre>
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MeLightSensorRGB_H
#define MeLightSensorRGB_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "MeConfig.h"
#ifdef ME_PORT_DEFINED
#include "MePort.h"
#endif // ME_PORT_DEFINED

/* Exported macro ------------------------------------------------------------*/
#define I2C_ERROR                  						(-1)
#define I2C_OK                    						(0)
#define LIGHTSENSORRGB_DEFAULT_ADDRESS       (0x20)

//Me LightSensorRGB Register Address
#define LIGHTSENSOR_RGB_DATA_S1        (0x00)
#define LIGHTSENSOR_RGB_DATA_S2        (0x01)
#define LIGHTSENSOR_RGB_DATA_S3        (0x02)
#define LIGHTSENSOR_RGB_DATA_S4        (0x03)
#define LIGHTSENSOR_RGB_STATE       	 (0x04)
#define LIGHTSENSOR_RGB_TURNOFFSET_L   (0x05)
#define LIGHTSENSOR_RGB_TURNOFFSET_H   (0x06)

//LightSensorRGB number
#define LIGHTSENSOR_RGB_NUM		         (0x04)


/**
 * Class: MeLightSensorRGB
 * \par Description
 * Declaration of Class MeLightSensorRGB
 */
#ifndef ME_PORT_DEFINED
class MeLightSensorRGB
#else // !ME_PORT_DEFINED
class MeLightSensorRGB : public MePort
#endif // !ME_PORT_DEFINED
{
public:
#ifdef ME_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the MeCompass to arduino port,
 * no pins are used or initialized here
 */
  MeLightSensorRGB(void);

/**
 * Alternate Constructor which can call your own function to map the MeCompass to arduino port,
 * no pins are used or initialized here, but PWM frequency set to 976 Hz
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  MeLightSensorRGB(uint8_t port);

/**
 * Alternate Constructor which can call your own function to map the MeCompass to arduino port
 * and change the i2c device address
 * no pins are used or initialized here, but PWM frequency set to 976 Hz
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \param[in]
 *   address - the i2c address you want to set
 */
  MeLightSensorRGB(uint8_t port, uint8_t address);
#else
/**
 * Alternate Constructor which can call your own function to map the _AD0 and _INT to arduino port,
 * no pins are used or initialized here
 * \param[in]
 *   _AD0 - arduino gpio number
 * \param[in]
 *   _INT - arduino gpio number
 */
  MeLightSensorRGB(uint8_t AD0, uint8_t INT);

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
  MeLightSensorRGB(uint8_t AD0, uint8_t INT, uint8_t address);
#endif  //  ME_PORT_DEFINED
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
  void setpin(uint8_t AD0, uint8_t INT);

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
 *   You can check the MPU6050 datasheet for the registor address.
 */
  void begin();

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
  uint8_t getDevAddr(void);

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
	uint8_t getADCValueS1(void);

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
	uint8_t getADCValueS2(void);

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
	uint8_t getADCValueS3(void);

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
	uint8_t getADCValueS4(void);

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
	void getAllADCValue(uint8_t *adcbuff, uint8_t size);

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
	void setKp(float value);

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
 *   turn offset Value
 * \par Others
 *   |--------------------------|
     |     |      |      |      |
     |  S1 |  S2  |  S3  |  S4  |
     |     |      |      |      |
     |--------------------------|
 */
	int16_t getPositionOffset(void);


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
 *   turn offset Value
 * \par Others
 *   |--------------------------|
     |     |      |      |      |
     |  S1 |  S2  |  S3  |  S4  |
     |     |      |      |      |
     |--------------------------|
 */
	uint8_t getPositionState(void);
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
  uint8_t getIicErrorCnt(void);
	
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
	uint8_t getStudyFlag(void);

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
	void updataAllSensorValue(void);

	void loop(void);

private:
  volatile uint8_t  _AD0;
  volatile uint8_t  _INT;
  uint8_t i2cData[15];
  uint8_t adcOutput[LIGHTSENSOR_RGB_NUM];
  uint8_t Device_Address;
  float Kp;
  int16_t positionOffset;
  uint8_t positionState;
  uint8_t study_flag;
  uint32_t iic_error_count;
  
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
  int8_t writeReg(int16_t reg, uint8_t data);

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
  int8_t readData(uint8_t start, uint8_t *buffer, uint8_t size);

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
  int8_t writeData(uint8_t start, const uint8_t *pData, uint8_t size);
};
#endif //  MeLightSensorRGB_H
