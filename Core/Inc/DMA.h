#ifndef DMA_H
#define DMA_H
#include"stm32f401xc.h"
#undef SETBIT
#undef SETBITS
#undef CLEARBIT
#undef CLEARBITS
#define GET_REG(REG, OFFSET) ((unsigned int *)(REG + OFFSET))
#define SETBIT(R,B) (*(R) |= (1<<(B)))
#define SETBITS(R,B,Data) (*(R) |= ((unsigned int)Data<<(B)))
#define CLEARBIT(R,B) (*(R) &=~ (1<<(B)))
#define CLEARBITS(R,B,Data) (*(R) &=~ (Data<<(B)))

#undef DMA1
#undef DMA2

#define DMA1 ((unsigned int *)(0x40026000))
#define DMA2 ((unsigned int *)(0x40026400))

#define DMAn_LISR(LINE) 		GET_REG(LINE, 0x00)
#define DMAn_HISR(LINE) 		GET_REG(LINE, 0x04)
#define DMAn_LIFCR(LINE) 		GET_REG(LINE, 0x08)
#define DMAn_HIFCR(LINE) 		GET_REG(LINE, 0x0C)
#define DMAn_SxCR(LINE, x) 		GET_REG(LINE, ((0x10)+(0x18 * x)))
#define DMAn_SxNDTR(LINE, x) 	GET_REG(LINE, ((0x14)+(0x18 * x)))
#define DMAn_SxPAR(LINE, x) 	GET_REG(LINE, ((0x18)+(0x18 * x)))
#define DMAn_SxM0AR(LINE, x) 	GET_REG(LINE, ((0x1C)+(0x18 * x)))
#define DMAn_SxM1AR(LINE, x) 	GET_REG(LINE, ((0x20)+(0x18 * x)))
#define DMAn_SxFCR(LINE, x) 	GET_REG(LINE, ((0x24)+(0x24 * x)))


typedef enum{
	DMA1_LINE = 1,DMA2_LINE = 2
}DMA_LINE;

typedef enum{
	STREAM0,STREAM1,STREAM2,STREAM3,STREAM4,STREAM5,STREAM6,STREAM7,
}STREAMX;
typedef enum{
	CHANNAL0,CHANNAL1,CHANNAL2,CHANNAL3,CHANNAL4,CHANNAL5,CHANNAL6,CHANNAL7
}CHANNALX;

typedef enum{
	PERIPHERAL_MEMORY,MEMORY_PERIPHERAL,MEMORY_MEMORY
}DIRECTION;
typedef enum{
	LOW,MEDIUM,HIGH,VERY_HIGH
}PRIORITY;
typedef enum {
	DIRECT_MODE,FIFO_MODE
}MODE;
typedef enum {
	FIXED,INCREMENT
}INC_MODE;
typedef enum {
	DMA_FLOW_CTR,PERIPHERAL_FLOW_CTR,
}FLOW_CTRL;
typedef enum {
	SINGLE,INCR4,INCR8,INCR16,
}BURST_MODE;
typedef enum {
	BYTE,HALF_WORD,WORD,
}DATA_SIZE;
typedef enum {
	ONE_FOURTH,HALF,THREE_FOURTHS,FULL,
}FIFO_THRESHOLD;
typedef enum {
	DISABLED , ENABLED
}INTERUPT_CTRL;
typedef enum{
	NO_BUFFER,BUFFER_SWITCHING
}DOUBLE_BUFFER;
typedef enum{
	MEMORY0,MEMORY1
}CURRENT_TARGET;
typedef enum {
	DISABLE,ENABLE
}CIRCULAR_MODE;


typedef struct {
	DMA_LINE LINE;
	STREAMX STREAM;
	CHANNALX CHANNAL;
	DATA_SIZE MSIZE;
	DATA_SIZE PSIZE;
	DIRECTION DIR;
	PRIORITY PL;
	CURRENT_TARGET CT;
	FLOW_CTRL PFCTRL;
	BURST_MODE MBURST;
	BURST_MODE PBURST;
	INTERUPT_CTRL DMEIE;
	INTERUPT_CTRL TEIE;
	INTERUPT_CTRL HTIE;
	INTERUPT_CTRL TCIE;
	INTERUPT_CTRL FEIE;
	DOUBLE_BUFFER DoubleBufferMode;
	MODE DMDIS;
	FIFO_THRESHOLD FTH;
	INC_MODE PINC;
	INC_MODE PINCOS;
	INC_MODE MINC;
	CIRCULAR_MODE CIRC;

	unsigned short numOfTransfare;
	unsigned int* Memory0Address;
	unsigned int* Memory1Address;
	unsigned int* PreipheralAddress;
}DMA_OBJ;

void DMA_EnableClock(DMA_OBJ DMA_struct);
void DMA_Configuration(DMA_OBJ DMA_struct);
void DMA_BeginTransport(DMA_OBJ DMA_struct);
void DMA_TransfareComplete(DMA_OBJ DMA_struct);
#endif
