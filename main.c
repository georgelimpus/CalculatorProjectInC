// 1. Pre-processor Directives Section
// #include "TExaS.h"
// #include "PLL.h"
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
	
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
	

#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_PUR_R        (*((volatile unsigned long *)0x40007510))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *)0x40007524))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))


#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PDR_R        (*((volatile unsigned long *)0x40024514))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
	
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))

	
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))

// bit specific addressing for RS, EN and DB pins
#define RS     (*((volatile unsigned long *)0x40004020))
#define EN     (*((volatile unsigned long *)0x40004010))



	



// 2. Declarations Section
//   Global Variables

//   Function Prototypes
void PortF_Init(void);
void PortE_Init(void);
void PortD_Init(void);
void PortB_Init(void);
void PortA_Init(void);
void Delay(void);
void Delay_ms(double delay_ms);
void PLL_Init(void);
void SysTick_Init(void);
void SysTick_Wait(unsigned long delay);
void SysTick_Wait_ms(unsigned long delay);
void SysTick_Wait_us(unsigned long delay);
void SysTick_Wait_25 (unsigned long delay);

void lcdInit(void);
void lcdENPulse(void);

void lcdSendInst(unsigned char inst);
void lcdSendData(unsigned char data);



//void EnableInterrupts(void);


// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable
int main(void){    

  PortF_Init();
	PortD_Init(); 
	PortE_Init();
	PortA_Init();
	PortB_Init();
	PLL_Init();
	SysTick_Init();
	lcdInit();
	Delay();
	
	lcdSendData(0x04);
	SysTick_Wait_ms(5000);
	lcdSendInst(0x01);
	
  while(1) {
		unsigned long i;
			for (i=0;i<4; i++) {
				GPIO_PORTD_DATA_R =(0x01<<i);// sends 1 to each column one by 1
				SysTick_Wait_ms(1);
				
				GPIO_PORTF_DATA_R = GPIO_PORTE_DATA_R;
			}
			SysTick_Wait_ms(1);
			
			}
}
    
	/** CHANGE the delay function to use SysTick **/ 
	/*if (i == 0) {
	SysTick_Wait(5000000);                    // wait 0.1 sec - 5000000 * 20 ns = 0.1 second?
	i = 1;
	}
	else {
		SysTick_Wait(10000000); // 0.2 sec
		i = 0;
	}
    GPIO_PORTF_DATA_R = 0x04;    // LED is blue
    SysTick_Wait(5000000);                     // wait 0.1 sec
  }
}*/

// Subroutine to initialize port F pins for input and output
// PF4 and PF0 are input SW1 and SW2 respectively
// PF3,PF2,PF1 are outputs to the LED
// Inputs: None
// Outputs: None
// Notes: These five pins are connected to hardware on the LaunchPad
void PortF_Init(void){ volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x20;
		GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTF_CR_R = 0x0E;
		GPIO_PORTF_AFSEL_R = 0x00;
		GPIO_PORTF_PUR_R |= 0x11;
		GPIO_PORTF_AMSEL_R |= 0x00;
		GPIO_PORTF_PCTL_R = 0x00000000;
		GPIO_PORTF_DIR_R |= 0x0E;
		GPIO_PORTF_DEN_R |= 0x1F;
}

void PortD_Init(void){ volatile unsigned long delay; //columns, output
  SYSCTL_RCGC2_R |= 0x00000008;     // D clock
  delay = SYSCTL_RCGC2_R;               
  GPIO_PORTD_CR_R = 0x0F;           
  GPIO_PORTD_AMSEL_R = 0x00;        
  GPIO_PORTD_DIR_R = 0x0F;          
  GPIO_PORTD_AFSEL_R = 0x00;        
  GPIO_PORTD_DEN_R = 0x0F;    
	//GPIO_PORTD_DATA_R = 0x0F;
}

void PortE_Init(void){ volatile unsigned long delay; // rows, input
  SYSCTL_RCGC2_R |= 0x00000010;     // E clock 
  delay = SYSCTL_RCGC2_R;           
  GPIO_PORTE_CR_R = 0x0F;           
  GPIO_PORTE_AMSEL_R = 0x00;       
  GPIO_PORTE_DIR_R = 0x00;          
  GPIO_PORTE_AFSEL_R = 0x00;        
	GPIO_PORTE_PDR_R = 0x0F;
  GPIO_PORTE_DEN_R = 0x0F;          
}

void PortB_Init(void) {volatile unsigned long delay; // (PB0->DB4), (PB1->DB5), (PB2->DB6), (PB3->DB7) 
	
	SYSCTL_RCGC2_R |= 0x00000002;     // B clock
  delay = SYSCTL_RCGC2_R;                     			
  GPIO_PORTB_AMSEL_R = 0x00;        
  GPIO_PORTB_DIR_R = 0x0F;          // PB0 - PB3 set as outputs
  GPIO_PORTB_AFSEL_R = 0x00;        
  GPIO_PORTB_DEN_R = 0x0F; 					// Digital Enable on PB0 - PB3
	GPIO_PORTB_PUR_R = 0x00;					// Disable pull-up resistos
	GPIO_PORTB_PCTL_R = 0x00000000;
	
	//GPIO_PORTB_DATA_R = 0x00;
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
	
	//GPIO_PORTA_CR_R = 0x06;   				// RS on bit 3 EN on bit 2 
	//GPIO_PORTA_DATA_R = 0x0C;					// PA2 and PA3 set to 1
}


void lcdENPulse(void) {
	
	EN = 0x04;												// EN set to ON
	SysTick_Wait_25(25); 							// 18*25ns = 450ns delay
	EN = 0x00;	
	
}


void lcdSendInst(unsigned char inst) {			// Function to send lcd instruction
	
	RS = 0x00;												 				// RS set to 0
	SysTick_Wait_us (40);
	
	GPIO_PORTB_DATA_R = (inst & 0xF0);				// Mask for bits 1-4				
	lcdENPulse();															// Pulse high nibble
	SysTick_Wait_ms(1);
	
	GPIO_PORTB_DATA_R = ((inst<<4) & 0xF0); 	// Shift left by 4 and mask
	lcdENPulse();															// Pulse low nibble
	SysTick_Wait_ms(1);
	
}

void lcdSendData(unsigned char data) { 			// Function to send lcd data
	
	RS = 0x08;																// RS set to 1
	SysTick_Wait_us (40);
	
	GPIO_PORTB_DATA_R = (data & 0xF0);	      // Mask for bits 1-4		
	lcdENPulse();															// Pulse high nibble
	SysTick_Wait_ms(1);
	
	GPIO_PORTB_DATA_R = ((data<<4) & 0xF0);		// Shift left by 4 and mask
	lcdENPulse();															// Pulse low nibble
	SysTick_Wait_ms(1);
	
}

void lcdInit(void) {
	
	PortB_Init();									// Initialise Port A, Port B
	PortA_Init();
	
	RS = 0x00;												// Set RS, EN to 0
	EN = 0x00;
	
	SysTick_Wait_ms(15);					// Wait 15ms
	SysTick_Wait_ms(15);					// Wait 15ms

	GPIO_PORTB_DATA_R = 0x03; 		// Set DB5, DB4 to 1
	lcdENPulse();									// Pulse in
	
	SysTick_Wait_ms(5);						// Wait 5ms (5ms >= 4.1ms)
	SysTick_Wait_ms(5);						// Wait 5ms (5ms >= 4.1ms)
	
	GPIO_PORTB_DATA_R = 0x03; 		// Set DB5, DB4 to 1
	lcdENPulse();									// Pulse in
	
	SysTick_Wait_us(150);					// Wait 150us (150us >= 100us)
	SysTick_Wait_us(150);					// Wait 150us (150us >= 100us)
	
	GPIO_PORTB_DATA_R = 0x03; 		// Set DB5, DB4 to 1
	lcdENPulse();									// Pulse in
	
	SysTick_Wait_us(40);					// Wait 40us
	//SysTick_Wait_us(150);					// Wait 150us
	
	
	GPIO_PORTB_DATA_R = 0x02; 		// Set DB5 to 1
	lcdENPulse();									// Pulse in
	
	SysTick_Wait_us(150);
	//SysTick_Wait_us(150);
	
	
	lcdSendInst(0x28);						// Set DB5 to 1, then set N to 1 for 2 display lines, F does not need to be set
	lcdSendInst(0x0F);						// Set DB7 to 1, Display to 1, Curser to 1, Blink to 1
	lcdSendInst(0x01);						// Set DB4 to 1 on second pulse -> display clear
	lcdSendInst(0x06);						// Set DB6 to 1, I/D to 1 (increment), S to 0 (no shift)
	
	
	
}



void Delay(void){unsigned long volatile time;
	//time = 727240*200/91;  // 0.1sec
	time = 727240*20/91;  // 0.01sec
  while(time){
                time--;
  }
}

void Delay_ms(double delay_ms) {double volatile time;
	time = 727240*2*delay_ms/91;  // 0.001sec 1 milisecond
	while(time){
                time--;
  }
}

void SysTick_Wait_25(unsigned long delay) {
	SysTick_Wait (delay * 2); // 25ns delay
}



void SysTick_Wait_us(unsigned long delay) {
	
	unsigned long i;
	for(i = 0; i < delay; i ++) {
		
		SysTick_Wait (80); // 80 cycles per us
	}
}

void SysTick_Wait_ms(unsigned long delay) {
	
	unsigned long i;
	for(i = 0; i < delay; i ++) {
		
		SysTick_Wait (80000); // 80,000 cycles per ms
	}
}





