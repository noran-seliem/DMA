#include "GPIO.h"
#include "stm32f401xc.h"
#include "stm32f401cc_interface.h"
#include "DMA.h"
unsigned int src[100];
unsigned int dst[100];

DMA_OBJ DMASTRUCT;
void DMA_INIT(){

		DMASTRUCT.LINE = DMA2_LINE;
		DMASTRUCT.STREAM =STREAM0;
		DMASTRUCT.CHANNAL=CHANNAL0;
		DMASTRUCT.DIR =MEMORY_MEMORY;
		DMASTRUCT.DMDIS=FIFO_MODE;
		DMASTRUCT.MSIZE=WORD;
		DMASTRUCT.PSIZE=WORD;
		DMASTRUCT.MINC=INCREMENT;
		DMASTRUCT.PINC=INCREMENT;
		DMASTRUCT.PL= VERY_HIGH;
		DMASTRUCT.FTH =FULL;
		DMASTRUCT.MBURST=SINGLE;
		DMASTRUCT.PBURST=SINGLE;
		DMASTRUCT. PreipheralAddress =src;
		DMASTRUCT.Memory0Address =dst;
		DMASTRUCT.PINCOS = INCREMENT;
		DMASTRUCT.numOfTransfare=sizeof(src)/sizeof(unsigned int);
		DMA_EnableClock(DMASTRUCT);
		DMA_Configuration(DMASTRUCT);
}
int main(void) {
	GPIO_EnableClock('A');
	GPIO_Init( 'A', 0, OUTPUT, PUSH_PULL);
	for(int i = 1; i <= 100; i++)
	  {
	    src[i-1] = i * 100;
	    dst[i-1] =0;
	  }

	DMA_INIT();
	DMA_BeginTransport(DMASTRUCT);
	while(1){
	if(dst[0] !=0){
		GPIO_WritePin('A',0, 1);
	}
	}
	return 0;
}
