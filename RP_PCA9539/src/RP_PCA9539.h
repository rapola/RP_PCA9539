/*
 * classPCA9539.h
 *
 * Created on: 09.06.2021
 * Author: Ralf
 * https://www.ti.com/product/PCA9539
 * https://42project.net/c-basic-bitmanipulation-set-clear-change-bit-in-c/
 *
 */

#ifndef RP_PCA9539_H_
#define RP_PCA9539_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


/*
 *	PCA9539 defines
 *  invert register is not supported
 */
#define PCA9539_INPUT      0								//register 0 and 1
#define PCA9539_OUTPUT     2								//register 2 and 3
#define PCA9539_CONFIG     6								//register 6 and 7

/*
 * macros for simple bit handling
*/
#define CLEAR_BIT(byte,bit) ((byte) &= ~(1UL << (bit)))
#define SET_BIT(byte, bit) ((byte) |= (1UL << (bit)))
#define IS_SET(byte,bit) (((byte) & (1UL << (bit))) >> (bit))


class PCA9539 {
public:
  PCA9539();                            					        //constructor
  uint8_t init(uint8_t i2caddr);							            //intialize, returns 1 if success otherwise 0
	uint8_t pinModeBuf(uint8_t pin, uint8_t Mode);			    //call this to set several pins in a buffer, transmit to PCA9539 by calling "PinModeUpdate" (faster, only write once)
	uint8_t pinModeUpdate(void);							              //call to update pin mode registers in PCA9539
	uint8_t pinMode(uint8_t pin, uint8_t Mode);				      //call to set the desired pin direction immediately
	uint8_t digitalWriteBuf(uint8_t pin, uint8_t level);	  //call to set the desired pin level in a buffer, transmit to PCA9539 by calling "WriteBufUpdate" (faster, only write once)
	uint8_t writeBufUpdate(void);							              //call to update pin level registers in PCA9539
	uint8_t digitalWrite(uint8_t pin, uint8_t level);		    //call to set the desired pin level immediately
	uint8_t readBufUpdate(void);							              //call to update the input read buffer
	uint8_t digitalReadBuf(uint8_t pin);					          //call to read the specified pin, call "ReadBufUpdate" first to ensure an actual level (faster, only read once)
	uint8_t digitalRead(uint8_t pin);						            //call to read the desired pin level immediately
	uint8_t readPortA(void);								                //returns the actual PortA level
	uint8_t readPortB(void);								                //returns the actual PortB level


private:
  uint8_t _i2caddr;										                    //holds the i2c address of PCA9539
	uint8_t _cfgPort0Direction;								
	uint8_t _cfgPort1Direction;
	uint8_t _cfgPort0Level;
	uint8_t _cfgPort1Level;
	uint8_t _inPort0Level;
	uint8_t _inPort1Level;

};

 /* RP_PCA9539_H_ */
#endif