
#include "LCD.h"

static void  LCDEnable(void)
{
    LCDEnablePin = HIGH; 
    dlyus(25);
    LCDEnablePin = LOW; 
}

void LCDWriteCommand(LCDubyte LCDData)
{
    LCDRegisterSelectPin = LOW; 
    LCDWriteByte(LCDData);
}

void LCDWriteData(LCDubyte LCDData)
{
    LCDRegisterSelectPin = HIGH; 
    LCDWriteByte(LCDData);
}

 void LCDWriteString(const char *lcd_string)
{
    while(*lcd_string)
	LCDWriteData(*lcd_string++);

}

void lcdinit(void)
{
    LCD_DDR     &= 0x03;
    LCDDataPort &= 0x03;
    LCDReset();
    LCDWriteCommand(0x28);
    LCDWriteCommand(0x0C);
    LCDWriteCommand(0x06);
    LCDWriteCommand(0x01); 

}
static void LCDReset(void)
{
	LCDWriteCommand(0x33);
	LCDWriteCommand(0x33);
	LCDWriteCommand(0x32);
}
void LCDDisplayInitializing(void)
{
	
	LCDubyte i;
	LCDWriteString("INITIALIZING....");
	LCDRow2();
	for(i = 0 ; i < 16; i++)
	{
		LCDWriteData(46);			// ascii value of '.' in decimanl
		dlyms(100);
	}
	LCDClear();
}
static void  LCDWriteByte(LCDubyte  LCDData)
{
    LCDDataPort = (LCDDataPort & 0x0f)|(LCDData & 0xf0);
    LCDEnable();
    LCDDataPort = (LCDDataPort & 0x0f)|(LCDData << 4);
    LCDEnable();
    dlyms(2);
}
void LCDDisplayByte(LCDubyte LCDAdress, LCDubyte Value)
{
	LCDWriteCommand(LCDAdress);
	if(( Value / 100 ) == 0)
		LCDWriteData(0x20);			//put space
  	else
		LCDWriteData((Value / 100) | 0x30);
   
    if(((Value % 100) / 10) == 0)
		if(( Value / 100 ) == 0)
			LCDWriteData(0x20);	
		else
			LCDWriteData(((Value % 100) / 10) | 0x30);
  	else
		LCDWriteData(((Value % 100) / 10) | 0x30);

	LCDWriteData((Value % 10) | 0x30);
}	
