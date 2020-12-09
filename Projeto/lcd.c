#include "pic18f4520.h"
#include "lcd.h"
#include "delay.h"

void lcd_wr(unsigned char val) {
    PORTD = val;
}

void lcd_cmd(unsigned char val) {
    BitSet(PORTE,1); // Enable - PORTEbits.RE1
    lcd_wr(val);
    BitClr(PORTE,2); // Data - PORTEbits.RE2
    atraso_ms(3);
    BitClr(PORTE,1); 
    atraso_ms(3);
    BitSet(PORTE,1); 
}

void lcd_dat(unsigned char val) {
    BitSet(PORTE,1); 
    lcd_wr(val);
    BitSet(PORTE,2); 
    atraso_ms(3);
    BitClr(PORTE,1); 
    atraso_ms(3);
    BitSet(PORTE,1); 
}

void lcd_init(void) {
    BitClr(PORTE,1); 
    BitClr(PORTE,2); 
    atraso_ms(20);
    BitSet(PORTE,1); 

    lcd_cmd(L_CFG);
    atraso_ms(5);
    lcd_cmd(L_CFG);
    atraso_ms(1);
    lcd_cmd(L_CFG); //configura
    lcd_cmd(L_OFF); //desliga
    lcd_cmd(L_ON);  //liga
    lcd_cmd(L_CLR); //limpa
    lcd_cmd(L_CFG); //configura
    lcd_cmd(L_L1);
}

void lcd_str(const char* str) {
    unsigned char i = 0;

    while (str[i] != 0) {
        lcd_dat(str[i]);
        i++;
    }
}







