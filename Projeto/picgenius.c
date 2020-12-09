#include "picgenius.h"



void win7seg() {
    int v7seg2[4] = {0x09, 0x40};
    int x7 = -1;
    for (;;) {
        x7++;
        if (x7 == 2)x7 = 0;
        PORTD = v7seg2[x7 % 2];
        BitSet(PORTA, 5); //liga o 1o display 
        BitClr(PORTA, 2); //desliga o 4o display 
        atraso_ms(100);
        PORTD = v7seg2[x7 % 2];
        BitClr(PORTA, 5); //desliga o 1o display 
        BitSet(PORTA, 4); //liga o 2o display 
        atraso_ms(100);
        PORTD = v7seg2[x7 % 2];
        BitClr(PORTA, 4); //desliga o 2o display 
        BitSet(PORTA, 3); //liga o 3o display  
        atraso_ms(100);
        PORTD = v7seg2[x7 % 2];
        BitClr(PORTA, 3); //desliga o 3o display 
        BitSet(PORTA, 2); //liga o 4o display 
        atraso_ms(100);
    }
}

void beep() {
    PORTC = 0b00000000;
    atraso_ms(500);
    PORTC = 0b00000010;
}

void led1() {
    PORTB = 0x02;
    PORTC = 0b00000000;
    atraso_ms(600);
    PORTC = 0b00000010;
}

void led2() {
    PORTB = 0x04;
    PORTC = 0b00000000;
    atraso_ms(600);
    PORTC = 0b00000010;

}

void led3() {
    PORTB = 0x08;
    PORTC = 0b00000000;
    atraso_ms(600);
    PORTC = 0b00000010;
}

void led4() {
    PORTB = 0x10;
    PORTC = 0b00000000;
    atraso_ms(600);
    PORTC = 0b00000010;
}

void sorteia() {
    srand(srandx * 7919); //A Seed depende do tempo q demora para startar o game
    for (int i = 0; i < 10; i++) {
        sequencia[i] = ((rand() % 4 + 1)*2 + '0');
    }
}

void ganhou() {
    lcd_cmd(L_CLR);
    lcd_str("Voce Conseguiu");
    lcd_cmd(L_L2);
    lcd_str("Vamos De novo?");
    lcd_cmd(L_L4);
    lcd_str("Novo Jogo -> RST");
    lcd_cmd(L_L3);

    atraso_ms(2000);
    lcd_str("       =D   ");

    win7seg();

}

void atencao() {
    lcd_cmd(L_CLR);
    lcd_str("     ATENCAO  ");
    lcd_cmd(L_L2);
    lcd_str("    Sequencia   ");
    lcd_cmd(L_L3);
    atraso_ms(2000);
    lcd_cmd(L_CLR);
}

void prox_fase() {
    PORTB = 0x00;
    PORTD = 0x00;

    lcd_cmd(L_CLR);
    for (int i = 0; i < 16; i++) {
        lcd_dat(255);
        atraso_ms(50);
    }
    lcd_cmd(L_L2);
    lcd_str("   Muito bem!");
    PORTB = 0xFF;
    PORTD = 0xFF;
    PORTC = 0b00000000;

    atraso_ms(200);

    PORTC = 0b00000010;
    PORTB = 0x00;
    PORTD = 0x00;

    atraso_ms(100);

    PORTC = 0b00000000;
    PORTB = 0xFF;
    PORTD = 0xFF;

    atraso_ms(200);

    PORTC = 0b00000010;
    PORTB = 0x00;
    PORTD = 0x00;
    atraso_ms(1000);
    fase++;
}

void start_game() {
    lcd_cmd(L_CLR);
    lcd_str(" Loading Genius");
    for (i = 0; i < 15; i++) {
        atraso_ms(200);
        lcd_cmd(0x10);
    }
    for (i = 0; i < 16; i++) {
        atraso_ms(200);
        lcd_cmd(0x14);
    }
    lcd_cmd(L_CLR);
    lcd_cmd(L_L2);
    lcd_str("RB3 -> INICIAR");
    lcd_cmd(L_L3);
    lcd_str("RB4 -> TUTORIAL");

    while (BitTst(PORTB, 3) && BitTst(PORTB, 4)) {
        srandx++;
    }

    if (BitTst(PORTB, 4) == 0) {
        lcd_cmd(L_CLR);
        lcd_str("    Tutorial");
        for (i = 0; i < 9; i++) {
            atraso_ms(200);
            lcd_cmd(0x10);
        }
        for (i = 0; i < 10; i++) {
            atraso_ms(200);
            lcd_cmd(0x14);
        }
        lcd_cmd(L_CLR);
        lcd_str("   Controles");
        atraso_ms(2000);
        lcd_cmd(L_CLR);
        lcd_str("    TECLAS");
        lcd_cmd(L_L2);
        lcd_str("     (2)R");
        lcd_cmd(L_L3);
        lcd_str("(4)G        B(8)");
        lcd_cmd(L_L4);
        lcd_str("     Y(6)");
        lcd_cmd(L_L1 + 0x0A);
        atraso_ms(5000);
        lcd_cmd(L_CLR);
        lcd_str("(2) -> LED B1 R");
        lcd_cmd(L_L2);
        lcd_str("(4) -> LED B2 G");
        lcd_cmd(L_L3);
        lcd_str("(6) -> LED B3 B");
        lcd_cmd(L_L4);
        lcd_str("(8) -> LED B4 Y");
        atraso_ms(5000);
        lcd_cmd(L_CLR);
        lcd_str("Reproduza a");
        lcd_cmd(L_L2);
        lcd_str("Sequencia do LEDS");
        lcd_cmd(L_L3);
        lcd_str("Bom Jogo =D");
        lcd_cmd(L_L4);
        lcd_str("RB3 -> INICIAR");
        while (BitTst(PORTB, 3)) {
            srandx++;
        }
    }
    sorteia();
}

void game_over() {
    lcd_cmd(L_CLR);
    lcd_str("   Nao Deu =(");
    lcd_cmd(L_L2);
    lcd_str("  Nao desista!  ");
    lcd_cmd(L_L4);
    lcd_str("Novo Jogo -> RST");


    PORTB = 0x00;
    PORTD = 0x00;


    PORTC = 0b00000000;

    PORTB = 0xFF;
    PORTD = 0xFF;

    atraso_ms(300);

    PORTC = 0b00000010;
    PORTB = 0x00;
    PORTD = 0x00;

    atraso_ms(300);

    PORTC = 0b00000000;
    PORTB = 0xFF;
    PORTD = 0xFF;

    atraso_ms(600);

    PORTC = 0b00000010;
    PORTB = 0x00;
    PORTD = 0x00;

    atraso_ms(300);
    PORTC = 0b00000000;
    PORTB = 0xFF;
    PORTD = 0xFF;

    atraso_ms(2000);
    PORTC = 0b00000010;
    PORTB = 0x00;
    PORTD = 0x00;
    for (;;);
}

void d7seg() {
    int values7seg[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
    int aux7 = fase + 1;
    PORTD = values7seg[aux7];
    BitSet(PORTA, 5);
    if (fase + 1 > 9) {
        for (i = 0; i < 20; i++) {
            PORTD = values7seg[aux7 - 10];
            BitSet(PORTA, 5);
            BitClr(PORTA, 4);
            BitClr(PORTA, 3);
            BitClr(PORTA, 2);
            atraso_ms(20);
            PORTD = values7seg[1];
            BitClr(PORTA, 5);
            BitSet(PORTA, 4);
            BitClr(PORTA, 3);
            BitClr(PORTA, 2);
            atraso_ms(20);
        }
        BitClr(PORTA, 5);
        BitClr(PORTA, 4);
    }
}

void show_seq() {
    for (int i = 0; i <= fase; i++) {
        PORTB = 0x00;
        atraso_ms(atrasoMed);
        if (sequencia[i] == '2') {
            led1();
        }
        if (sequencia[i] == '4') {
            led2();
        }
        if (sequencia[i] == '6') {
            led3();
        }
        if (sequencia[i] == '8') {
            led4();
        }
    }
}

void verifica(int aux) {
    if (resposta[aux] == '2') {
        led1();
    }
    if (resposta[aux] == '4') {
        led2();
    }
    if (resposta[aux] == '6') {
        led3();
    }
    if (resposta[aux] == '8') {
        led4();
    }

    PORTB = 0x00;

    if (resposta[aux] != sequencia[aux]) {
        game_over();
    }
}

void leitura() {
    unsigned char tmp;
    aux = 0;
    while (aux <= fase) {
        TRISD = 0x0F;
        tmp = tc_tecla(0) + 0x30;
        if (tmp == '2' || tmp == '4' || tmp == '6' || tmp == '8') {
            TRISB = 0x00;
            TRISD = 0x00;
            resposta[aux] = tmp;
            verifica(aux);
            aux++;
        }
    }
}

