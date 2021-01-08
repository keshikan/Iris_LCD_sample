/*
 * Iris_if_conf.h
 *
 *  Created on: Jan 8, 2021
 *      Author: Keshikan
 */

#ifndef INC_IRIS_IF_H_
#define INC_IRIS_IF_H_

#include <stdint.h>
#include "stm32f7xx_hal.h"
#include "Iris_if_conf.h"

#define IRIS_SIZ_X (640)
#define IRIS_SIZ_Y (48)
#define IRIS_SIZ_VRAM (IRIS_SIZ_X * IRIS_SIZ_Y)

extern void sendCmd(uint8_t dat);
extern void sendDat(uint8_t dat);

extern void initIris();
extern uint16_t convRGB888toRGB565(uint8_t r, uint8_t g, uint8_t b);
extern void irisDrawDot(uint16_t x, uint16_t y, uint16_t color);
extern void irisClearDisp();
extern void irisUpdate();
extern void irisMain();




#endif /* INC_IRIS_IF_H_ */
