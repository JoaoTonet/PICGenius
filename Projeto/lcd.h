#ifndef LCD_H
#define	LCD_H

#define L_ON	0x0F
#define L_OFF	0x08
#define L_CLR	0x01
#define L_L1	0x80
#define L_L2	0xC0
#define L_L3    0x90
#define L_L4    0xD0		
#define L_CR	0x0F		
#define L_NCR	0x0C	

#define L_CFG   0x38

void lcd_init(void);
void lcd_cmd(unsigned char val); 
void lcd_dat(unsigned char val);
void lcd_str(const char* str);

#endif	