#include "PLL.h"

#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108)) 

#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC)) // Port B
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))

	
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC)) // Port A
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))


#define RS     									(*((volatile unsigned long *)0x40004020))	// Bit specific addresses for RS and EN
#define EN     									(*((volatile unsigned long *)0x40004010))
	

void PortB_Init(void) {volatile unsigned long delay; // (PB0->DB4), (PB1->DB5), (PB2->DB6), (PB3->DB7) 
	
	SYSCTL_RCGC2_R |= 0x00000002;     								 // B clock
  delay = SYSCTL_RCGC2_R;               
  GPIO_PORTB_CR_R = 0x0F;      			
  GPIO_PORTB_AMSEL_R = 0x00;        
  GPIO_PORTB_DIR_R = 0x0F;          								 // PB0 - PB3 set as outputs
  GPIO_PORTB_AFSEL_R = 0x00;        
  GPIO_PORTB_DEN_R = 0x0F; 													 // Digital Enable on PB0 - PB3
	GPIO_PORTB_PUR_R = 0x00;													 // Disable pull-up resistos
	GPIO_PORTB_PCTL_R = 0x00000000;
	
}


void PortA_Init(void) {volatile unsigned long delay;
	
	SYSCTL_RCGC2_R |= 0x00000001;     // A clock
  delay = SYSCTL_RCGC2_R;                      
  GPIO_PORTA_AMSEL_R = 0x00;        
  GPIO_PORTA_DIR_R = 0x0C;         	// PA2, PA3 set as outputs
  GPIO_PORTA_AFSEL_R = 0x00;        
  GPIO_PORTA_DEN_R = 0x0C;  				// Digital Enable on PA2,PA3
	GPIO_PORTA_PCTL_R = 0x00000000;
	GPIO_PORTA_PUR_R = 0x00;					// Disable pull-up resistos
	
}


void lcdENPulse(void) {
	
	EN = 0x04;												// EN set to ON
	SysTick_Wait_25(18); 							// 18*25ns = 450ns delay
	EN = 0x00;	
	
}


void lcdSendInst(unsigned char inst) {			// Function to send lcd instruction
	
	GPIO_PORTB_DATA_R = ((inst>>4) & 0x0F);		// Shift right by 4 and mask 				
	RS = 0x00;												 				// RS set to 0
	lcdENPulse();															// Pulse high nibble
	GPIO_PORTB_DATA_R = (inst & 0x0F); 	      // Mask for bits 1-4
	lcdENPulse();															// Pulse low nibble
	
}


void lcdSendData(unsigned char data) { 			// Function to send lcd data
	
	GPIO_PORTB_DATA_R = ((data>>4) & 0x0F);		// Shift right by 4 and mask 
	RS = 0x08;																// RS set to 1
	lcdENPulse();															// Pulse high nibble															
	GPIO_PORTB_DATA_R = (data & 0x0F);				// Mask for bits 1-4
	lcdENPulse();															// Pulse low nibble
	
}


void lcdInit(void) {
	
	PortB_Init();									// Initialise Port A, Port B
	PortA_Init();
	
	RS = 0;												// Set RS, EN to 0
	EN = 0x00;
	
	SysTick_Wait_ms(15);					// Wait 15ms											
	
	GPIO_PORTB_DATA_R = 0x03; 		// Set DB5, DB4 to 1
	lcdENPulse();									// Pulse in
	
	SysTick_Wait_ms(5);						// Wait 5ms (5ms >= 4.1ms)
	
	GPIO_PORTB_DATA_R = 0x03; 		// Set DB5, DB4 to 1
	lcdENPulse();									// Pulse in
	
	SysTick_Wait_us(150);					// Wait 150us (150us >= 100us)
	
	GPIO_PORTB_DATA_R = 0x03; 		// Set DB5, DB4 to 1
	lcdENPulse();									// Pulse in
	
	SysTick_Wait_us(150);					// Wait 150us
	
	GPIO_PORTB_DATA_R = 0x02; 		// Set DB5 to 1
	lcdENPulse();									// Pulse in
	
	SysTick_Wait_us(150);
	
	lcdSendInst(0x28);						// Set DB5 to 1, then set N to 1 for 2 display lines, F does not need to be set
	lcdSendInst(0x0F);						// Set DB7 to 1, Display to 1, Curser to 1, Blink to 1
	lcdSendInst(0x01);						// Set DB4 to 1 on second pulse -> display clear
	lcdSendInst(0x06);						// Set DB6 to 1, I/D to 1 (increment), S to 0 (no shift)
	
}
