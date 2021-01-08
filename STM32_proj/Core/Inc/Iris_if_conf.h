/*
 * Iris_if_conf.h
 *
 *  Created on: Jan 8, 2021
 *      Author: Keshikan
 */

#ifndef INC_IRIS_IF_CONF_H_
#define INC_IRIS_IF_CONF_H_


// [Iris long LCD porting]
#define IRIS_DATABUS	GPIOE
#define IRIS_CONFIG		GPIOF
#define IRIS_RST_PIN	GPIO_PIN_0
#define IRIS_RDX_PIN 	GPIO_PIN_1
#define IRIS_WRX_PIN 	GPIO_PIN_2
#define IRIS_CSX_PIN	GPIO_PIN_3
#define IRIS_DCX_PIN	GPIO_PIN_4

/* [connection example for Nucleo-144]
 * LCD-P1  to GND
 * LCD-P2  to Nucleo-PF0(RST)
 * LCD-P3  to GND
 * LCD-P4  to Nucleo-PE0(D0)
 * LCD-P5  to Nucleo-PE1(D1)
 * LCD-P6  to Nucleo-PE2(D2)
 * LCD-P7  to Nucleo-PE3(D3)
 * LCD-P8  to Nucleo-PE4(D4)
 * LCD-P9  to Nucleo-PE5(D5)
 * LCD-P10 to Nucleo-PE6(D6)
 * LCD-P11 to Nucleo-PE7(D7)
 * LCD-P12 to GND
 * LCD-P13 to Nucleo-PF1(RDX)
 * LCD-P14 to Nucleo-PF2(WRX)
 * LCD-P15 to Nucleo-PF3(CSX)
 * LCD-P16 to Nucleo-PF4(DCX)
 * LCD-P17 to GND
 * LCD-P18 to VDD(3.3V)
 * LCD-P19 to VDD(3.3V)
 * LCD-P20 to LED+(12V)
 * LCD-P21 to LED-(GND)
 * LCD-P21 to GND
 */


#endif /* INC_IRIS_IF_CONF_H_ */
