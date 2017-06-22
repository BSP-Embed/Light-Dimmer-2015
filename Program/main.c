#include "main.h"

/* main.c: Application program for MPPT implimentation*/

bit ZCFlag = 0;
bit StartFlag = 0;

void main(void)
{
    int8u SwStat = 0;
    int8u Speed = 5;

    init();
    
    while (TRUE) {
        
        if (StartFlag == 1 && ZCFlag == 1) {
            dlyms(Speed);
            LoadOn();
            dlyus(250);
            LoadOff();
            ZCFlag = 0;
        }
        if (START_SW == PRESSED) {
           StartFlag = ~StartFlag;
           LCDWriteCommand(0xc4);
           if (StartFlag == 1)
               LCDWriteString("ON ");
            else
               LCDWriteString("OFF");
           
           while (START_SW == PRESSED);
        }
        if (SPEED_SW == PRESSED) {
            if(++SwStat >= 3)
                SwStat = 0;
            LCDWriteCommand(0xcc);
            switch(SwStat) {
                case 0: Speed = 5; LCDWriteString("30% "); break;
                case 1: Speed = 4; LCDWriteString("50% "); break;
                case 2: Speed = 1; LCDWriteString("100%"); break;
            }
            while (SPEED_SW == PRESSED);
        }
    
    }
}
/* initialize pheripherals*/
void init(void)
{
    initGPIO();
    lcdinit();
    disp_title();
}

/* overflows at every 100msecs*/
void interrupt ISR(void)
{
    if (INTF){          //INTF flag raised, so external interrupt occured
        ZCFlag = 1;
        INTF = 0;
     }
}
/* initialize GPIO's*/
void initGPIO(void)
{
    T1CON &= ~(0x01 << 3);  /* Timer 1 osc disable*/
    TRISC &= ~(0x3f);       /*RC5:RC0 as output*/
    TRISB &= ~(1 << 1);
    LoadOff();
    
    TRISD |= 0x03;
    PORTD |= 0x03;

    TRISB = 0x01;         //RB0 input for interrupt
    INTEDG = 0;          //interrupt on falling edge
    INTF = 0;           //clear interrupt flag
    INTE = 1;           //enable external interrupt
    GIE = 1;            //enable global interrupt
}
void disp_title(void)
{
    LCDClear();
    LCDWriteString("Vari Freq Drive");
    LCDRow2();
    LCDWriteString("Mot:OFF RPM:30%");
}
