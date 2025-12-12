#ifndef PLL_h
#define PLL_h


void Delay(void);
void Delay_ms(double delay_ms);
void PLL_Init(void);
void SysTick_Init(void);
void SysTick_Wait(unsigned long delay);
void SysTick_Wait_ms(unsigned long delay);
void SysTick_Wait_us(unsigned long delay);
void SysTick_Wait_25 (unsigned long delay);

#endif