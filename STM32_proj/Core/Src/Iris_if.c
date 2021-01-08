/*
 * Iris_if.c
 *
 *  Created on: Jan 8, 2021
 *      Author: Keshikan
 */


#include "Iris_if.h"

uint8_t vram[IRIS_SIZ_VRAM * 2];


void sendCmd(uint8_t dat)
{
	IRIS_CONFIG->BSRR = (uint32_t)IRIS_DCX_PIN << 16;

	IRIS_DATABUS->ODR = (uint32_t)dat;

	IRIS_CONFIG->BSRR = (uint32_t)IRIS_WRX_PIN << 16;

	//greater than 15ns (c.f. 18.3. AC Characteristics [twrl])
	asm("NOP");asm("NOP");asm("NOP");asm("NOP");

	IRIS_CONFIG->BSRR = IRIS_WRX_PIN;

}

void sendDat(uint8_t dat)
{
	IRIS_CONFIG->BSRR = IRIS_DCX_PIN;

	IRIS_DATABUS->ODR = (uint32_t)dat;

	IRIS_CONFIG->BSRR = (uint32_t)IRIS_WRX_PIN << 16;

	//greater than 15ns (c.f. 18.3. AC Characteristics [twrl])
	asm("NOP");asm("NOP");asm("NOP");asm("NOP");

	IRIS_CONFIG->BSRR = IRIS_WRX_PIN;
}

void clearScr()
{
	sendCmd(0x2C);
	for(uint32_t i=0; i<(IRIS_SIZ_X * IRIS_SIZ_Y); i++){
		sendDat(0x00);
		sendDat(0x00);
	}

}

void initIris()
{

	//Set initial GPIO state
	HAL_GPIO_WritePin(IRIS_CONFIG, IRIS_RDX_PIN, 1);
	HAL_GPIO_WritePin(IRIS_CONFIG, IRIS_WRX_PIN, 1);
	HAL_GPIO_WritePin(IRIS_CONFIG, IRIS_CSX_PIN, 1);
	HAL_GPIO_WritePin(IRIS_CONFIG, IRIS_DCX_PIN, 1);

	//Reset display
	HAL_GPIO_WritePin(IRIS_CONFIG, IRIS_RST_PIN, 0);
	HAL_Delay(100);
	HAL_GPIO_WritePin(IRIS_CONFIG, IRIS_RST_PIN, 1);
	HAL_Delay(100);

	HAL_GPIO_WritePin(IRIS_CONFIG, IRIS_CSX_PIN, 0);

	//Initialize code
	//(from https://github.com/kingyoPiyo/TFT_Test_48x640/blob/main/TFT_Test/TFT_Test.ino)
	//using ILI9342C TFT driver IC.

	//Set EXTC: turn on external command
	sendCmd(0xC8);
	sendDat(0xFF);
	sendDat(0x93);
	sendDat(0x42);

	//Column Address Set
	sendCmd(0x2A);
	sendDat(0x00);
	sendDat(0x00);
	sendDat(0x01);
	sendDat(0x3F);

	//Page Address Set
	sendCmd(0x2B);
	sendDat(0x00);
	sendDat(0x00);
	sendDat(0x00);
	sendDat(0x5F);

	//Memory Access Control: setting scanning direction.
	sendCmd(0x36);
	sendDat(0xC8);

	//Power Control 1
	sendCmd(0xC0);
	sendDat(0x0E);
	sendDat(0x0E);

	//Power Control 2
	sendCmd(0xC1);
	sendDat(0x10);

	//VCOM Control
	sendCmd(0xC5);
	sendDat(0xFA);

	//Pixel Format Set
	sendCmd(0x3A);
	sendDat(0x55);//RGB565 65K color

	//Frame Rate Control
	sendCmd(0xB1);
	sendDat(0x00);
	sendDat(0x18);

	//Positive Gamma Correction
	sendCmd(0xE0);
	sendDat(0x00);
	sendDat(0x1C);
	sendDat(0x21);
	sendDat(0x02);
	sendDat(0x11);
	sendDat(0x07);
	sendDat(0x3D);
	sendDat(0x79);
	sendDat(0x4B);
	sendDat(0x07);
	sendDat(0x0F);
	sendDat(0x0C);
	sendDat(0x1B);
	sendDat(0x1F);
	sendDat(0x0F);

	//Negative Gamma Correction
	sendCmd(0xE1);
	sendDat(0x00);
	sendDat(0x1C);
	sendDat(0x20);
	sendDat(0x04);
	sendDat(0x0F);
	sendDat(0x04);
	sendDat(0x33);
	sendDat(0x45);
	sendDat(0x42);
	sendDat(0x04);
	sendDat(0x0C);
	sendDat(0x0A);
	sendDat(0x22);
	sendDat(0x29);
	sendDat(0x0F);

	//Sleep Out
	sendCmd(0x11);
	HAL_Delay(130);//greater than 120ms

	sendCmd(0x29);
	HAL_Delay(10);

	clearScr();

}

uint16_t convRGB888toRGB565(uint8_t r, uint8_t g, uint8_t b)
{
	uint16_t col = ((r >> 3)<<11) + ((g >> 2)<<5) + (b >> 3);
	return col;
}

//x:0-639
//y:0-47
void irisDrawDot(uint16_t x, uint16_t y, uint16_t color)
{
	uint32_t pos = y * IRIS_SIZ_X + x;
	vram[pos*2] = (color & 0xFF00) >> 8;
	vram[pos*2+1] = (uint8_t)(color & 0x00FF);
}

void irisClearDisp()
{
	for(uint32_t i=0; i<IRIS_SIZ_VRAM * 2; i++){
		  vram[i] = 0x00;
	}
}

void irisUpdate()
{
	  //Column Addr set
	  sendCmd(0x2A);
	  sendDat(0x00);
	  sendDat(0x00);
	  sendDat(0x01);
	  sendDat(0x3F);

	  //Page Addr set
	  sendCmd(0x2B);
	  sendDat(0x00);
	  sendDat(0x00);
	  sendDat(0x5F);

	  //Write
	  sendCmd(0x2C);

		for(uint32_t i=0; i<IRIS_SIZ_VRAM * 2; i++){
			  sendDat(vram[i]);
		}
}
