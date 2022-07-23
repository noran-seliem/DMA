#include "DMA.h"
#include "stm32f401xc.h"
#include "stm32f401cc_interface.h"

void DMA_EnableClock(DMA_OBJ DMA_struct) {
	unsigned char line = DMA_struct.LINE;
  switch (line) {
    case 1:
      RCC_AHB1ENR |= (1 << 21);
      break;
    case 2:
      RCC_AHB1ENR |= (1 << 22);
      break;
    default:
      break;
  }
}


void DMA_Configuration(DMA_OBJ DMA_struct){
	unsigned int interrubtBitTC;
	//half transfer
	unsigned int HTIFbit;
	//transfer error
	unsigned int TEIFbit;
	//direct mode error
	unsigned int DMEIFbit;
	//fifo error
	unsigned int FEIFbit;
	switch(DMA_struct.STREAM){
		case 0:
		case 4:
			interrubtBitTC = 5;
			HTIFbit = 4;
			TEIFbit = 3;
			DMEIFbit = 2;
			FEIFbit =0;
			break;
		case 1:
		case 5:
			interrubtBitTC = 11;
			HTIFbit = 10;
			TEIFbit = 9;
			DMEIFbit = 8;
			FEIFbit =6;

			break;
		case 2:
		case 6:
			interrubtBitTC = 21;
			HTIFbit = 20;
			TEIFbit = 19;
			DMEIFbit = 18;
			FEIFbit =16;

			break;
		case 3:
		case 7:
			interrubtBitTC = 27;
			HTIFbit = 26;
			TEIFbit = 25;
			DMEIFbit = 24;
			FEIFbit =22;
			break;
	}
	//switch to DMA LINE
	switch(DMA_struct.LINE){
		case DMA1_LINE:

			// first must disable stream
			CLEARBIT(DMAn_SxCR(DMA1, DMA_struct.STREAM),0);
			//clear interrupt
			if(DMA_struct.STREAM <=3){
				CLEARBITS(DMAn_LISR(DMA1),0,0x00000000);
			}else{
				CLEARBITS(DMAn_HISR(DMA1),0,0x00000000);
			}
			//choose the channal
			SETBITS(DMAn_SxCR(DMA1, DMA_struct.STREAM),25,DMA_struct.CHANNAL);
			//number of data transfers
			SETBITS(DMAn_SxNDTR(DMA1, DMA_struct.STREAM),0,DMA_struct.numOfTransfare);
			//set src address
			SETBITS(DMAn_SxPAR(DMA1, DMA_struct.STREAM),0,DMA_struct. PreipheralAddress);
			//set dst address
			SETBITS(DMAn_SxM0AR(DMA1, DMA_struct.STREAM),0,DMA_struct.Memory0Address);
			//set priority
			SETBITS(DMAn_SxCR(DMA1, DMA_struct.STREAM),16,DMA_struct.PL);
			//set direct/fifo and direction of data
			if((DMA_struct.DIR != MEMORY_MEMORY) &&(DMA_struct.DMDIS == FIFO_MODE)){
				//error not allowed
				return;
			}
			else{
				SETBITS(DMAn_SxFCR(DMA1, DMA_struct.STREAM),2,DMA_struct.DMDIS);
				SETBITS(DMAn_SxCR(DMA1, DMA_struct.STREAM),6,DMA_struct.DIR);
			}
			//set flow control
			SETBITS(DMAn_SxCR(DMA1, DMA_struct.STREAM),5,DMA_struct.PFCTRL);
			//set MSIZE and PSIZE
			if(DMA_struct.DMDIS == DIRECT_MODE){
				//it is DIRECT MODE SO MSIZE and PSIZE must be equal
				if(DMA_struct.MSIZE == DMA_struct.PSIZE){
					SETBITS(DMAn_SxCR(DMA1, DMA_struct.STREAM),13,DMA_struct.MSIZE);
					SETBITS(DMAn_SxCR(DMA1, DMA_struct.STREAM),11,DMA_struct.PSIZE);
				}
				else{
					return;
				}
			}
			else{
				//it is FIFO mode so set MSIZE,PSIZE and Threshold
				SETBITS(DMAn_SxCR(DMA1, DMA_struct.STREAM),13,DMA_struct.MSIZE);
				SETBITS(DMAn_SxCR(DMA1, DMA_struct.STREAM),11,DMA_struct.PSIZE);
				SETBITS(DMAn_SxFCR(DMA1, DMA_struct.STREAM),0,DMA_struct.FTH);
			}
			//set MINC , PINC and PINCOS
			SETBITS(DMAn_SxCR(DMA1, DMA_struct.STREAM),10,DMA_struct.MINC);
			SETBITS(DMAn_SxCR(DMA1, DMA_struct.STREAM),9,DMA_struct.PINC);
			SETBITS(DMAn_SxCR(DMA1, DMA_struct.STREAM),15,DMA_struct.PINCOS);
			//set MBURST and PBURST
			SETBITS(DMAn_SxCR(DMA1, DMA_struct.STREAM),23,DMA_struct.MBURST);
			SETBITS(DMAn_SxCR(DMA1, DMA_struct.STREAM),21,DMA_struct.PBURST);
			//enable interrupt
			if(DMA_struct.STREAM == (0|1|2|3)){
				SETBIT(DMAn_LISR(DMA1) , interrubtBitTC);

			}else{
				SETBIT(DMAn_HISR(DMA1) , interrubtBitTC);

			}

			break;
		case DMA2_LINE:
			// first must disable stream
			CLEARBIT(DMAn_SxCR(DMA1, DMA_struct.STREAM),0);
			//clear interrupt
			if (DMA_struct.STREAM <=3){
				CLEARBITS(DMAn_LISR(DMA2),0,0x00000000);
			}
			else{
				CLEARBITS(DMAn_HISR(DMA2),0,0x00000000);
			}
			//choose the channal
			SETBITS(DMAn_SxCR(DMA2, DMA_struct.STREAM),25,DMA_struct.CHANNAL);
			//number of data transfers
			SETBITS(DMAn_SxNDTR(DMA2, DMA_struct.STREAM),0,DMA_struct.numOfTransfare);
			//set src address
			SETBITS(DMAn_SxPAR(DMA2, DMA_struct.STREAM),0,DMA_struct. PreipheralAddress);
			//set dst address
			SETBITS(DMAn_SxM0AR(DMA2, DMA_struct.STREAM),0,DMA_struct.Memory0Address);
			//set priority
			SETBITS(DMAn_SxCR(DMA2, DMA_struct.STREAM),16,DMA_struct.PL);
			//set direct/fifo and direction of data
			if((DMA_struct.DIR != MEMORY_MEMORY) &&(DMA_struct.DMDIS == FIFO_MODE)){
				//error not allowed
				return;
			}
			else{
				SETBITS(DMAn_SxFCR(DMA2, DMA_struct.STREAM),2,DMA_struct.DMDIS);
				SETBITS(DMAn_SxCR(DMA2, DMA_struct.STREAM),6,DMA_struct.DIR);
			}
			//set flow control
			SETBITS(DMAn_SxCR(DMA2, DMA_struct.STREAM),5,DMA_struct.PFCTRL);
			//set MSIZE and PSIZE
			if(DMA_struct.DMDIS == DIRECT_MODE){
				//it is DIRECT MODE SO MSIZE and PSIZE must be equal
				if(DMA_struct.MSIZE == DMA_struct.PSIZE){
					SETBITS(DMAn_SxCR(DMA2, DMA_struct.STREAM),13,DMA_struct.MSIZE);
					SETBITS(DMAn_SxCR(DMA2, DMA_struct.STREAM),11,DMA_struct.PSIZE);
				}
				else{
					return;
				}
			}
			else{
				//it is FIFO mode so set MSIZE,PSIZE and Threshold
				SETBITS(DMAn_SxCR(DMA2, DMA_struct.STREAM),13,DMA_struct.MSIZE);
				SETBITS(DMAn_SxCR(DMA2, DMA_struct.STREAM),11,DMA_struct.PSIZE);
				SETBITS(DMAn_SxFCR(DMA2, DMA_struct.STREAM),0,DMA_struct.FTH);
			}
			//set MINC , PINC and PINCOS
			SETBITS(DMAn_SxCR(DMA2, DMA_struct.STREAM),10,DMA_struct.MINC);
			SETBITS(DMAn_SxCR(DMA2, DMA_struct.STREAM),9,DMA_struct.PINC);
			SETBITS(DMAn_SxCR(DMA2, DMA_struct.STREAM),15,DMA_struct.PINCOS);
			//set MBURST and PBURST
			SETBITS(DMAn_SxCR(DMA2, DMA_struct.STREAM),23,DMA_struct.MBURST);
			SETBITS(DMAn_SxCR(DMA2, DMA_struct.STREAM),21,DMA_struct.PBURST);
			//enable interrupt
			if(DMA_struct.STREAM == (0|1|2|3)){
				SETBIT(DMAn_LISR(DMA2) , interrubtBitTC);
				//SETBIT(DMAn_LISR(DMA2) , HTIFbit);
				//SETBIT(DMAn_LISR(DMA2) , TEIFbit);
				//SETBIT(DMAn_LISR(DMA2) , DMEIFbit);
				//SETBIT(DMAn_LISR(DMA2) , FEIFbit);
			}else{
				SETBIT(DMAn_HISR(DMA2) , interrubtBitTC);
				//SETBIT(DMAn_HISR(DMA2) , HTIFbit);
				//SETBIT(DMAn_HISR(DMA2) , TEIFbit);
				//SETBIT(DMAn_HISR(DMA2) , DMEIFbit);
				//SETBIT(DMAn_HISR(DMA2) , FEIFbit);
			}
			break;
		default:
			break;

	}

}

void DMA_BeginTransport(DMA_OBJ DMA_struct){
	switch(DMA_struct.LINE){
		case DMA1_LINE:
			SETBIT(DMAn_SxCR(DMA1, DMA_struct.STREAM),0);
			break;
		case DMA2_LINE:
			SETBIT(DMAn_SxCR(DMA2, DMA_struct.STREAM),0);
			break;
		default:
			break;
	}
}




