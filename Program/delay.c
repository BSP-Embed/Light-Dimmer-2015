#include "delay.h"

void dlyms(unsigned int time)
{
    unsigned int pause;
    while (time--) {
	pause = 250;
	while (pause--);
    }
}
void dlyus(unsigned int time)
{
    unsigned char pause;
    while (time--) {
	pause = 5;
	while (pause--);
    }
}