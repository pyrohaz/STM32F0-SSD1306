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
volatile uint8_t Hour = 0, Min = 0, Sec = 0;

void SysTick_Handler(void){
	MSec++;
	if((MSec%1000)==999){
		Sec++;
		if(Sec==60){
			Sec = 0;
			Min++;
			if(Min==60){
				Hour++;
				if(Hour == 24){
					Hour = 0;
				}
			}
		}
	}
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

	while(1)
	{

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
