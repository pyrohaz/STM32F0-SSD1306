#include <SSD1306.h>
#include <GFX.h>

/*
 * main.c
 * Author: Harris Shallcross
 * Year: 2014-ish
 *
 * SSD1306 driver example using the STM32F0 discovery board
 * STM32F0 communicates with OLED display through SPI, pinouts described below.
 * My GFX library is used to create the functions below
 *
 * This code is provided AS IS and no warranty is included!
 */

GPIO_InitTypeDef G;

volatile uint32_t MSec = 0;

void SysTick_Handler(void){
	MSec++;
}

int main(void)
{
	SystemInit();

	SysTick_Config(SystemCoreClock/1000); //1ms timebase

	SSD1306_InitSetup();
	LCDSleepMode(LCDWake);

	int Cnt;
	int Dly = 50, WDly = 1500;

	uint8_t XPos = 0;

	int n, a, MSO, Sec = 1, Min = 2, Hour = 3;

	while(1)
	{
		Sec = (MSec/1000)%60;
		Min = (Sec/60)%60;
		Hour = (Min/60)%60;

		XPos = PStr("Time: ", 0, 0, 0, 0);
		XPos = PNum(Hour, XPos, 0, 1, 0, 0);
		XPos = PChar(':', XPos, 0, 0, 0);
		XPos = PNum(Min, XPos, 0, 1, 0, 0);
		XPos = PChar(':', XPos, 0, 0, 0);
		XPos = PNum(Sec, XPos, 0, 1, 0, 0);

		XPos = PStr("Date: ", 0, 16, 0, 0);
		XPos = PNum(10, XPos, 16, 1, 0, 0);
		XPos = PChar('/', XPos, 16, 0, 0);
		XPos = PNum(11, XPos, 16, 1, 0, 0);
		XPos = PChar('/', XPos, 16, 0, 0);
		XPos = PNum(12, XPos, 16, 1, 0, 0);
		PScrn();
		ClrBuf();
	}
}
