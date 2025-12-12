#ifndef LCD_h
#define LCD_h


void PortA_Init(void);
void PortB_Init(void);

void lcdInit(void);

void lcdENPulse(void);
void lcdSendInst(unsigned char inst);
void lcdSendData(unsigned char data);

#endif