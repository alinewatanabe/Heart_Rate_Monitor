/*
 * File:   projeto_ins_mic.c
 * Author: 21.00309-2
 *
 * Created on 29 de Maio de 2024, 16:59
 */
// PIC16F628A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 4000000              // define o valor da constante de frequ�ncia do oscilador para a rotina de delay

/* Definindo os pinos ligados aos displays */
#define DISP3_A PORTAbits.RA7          // define que DISP1_A equivale ao endere�o da porta RA7
#define DISP3_B PORTAbits.RA0          // define que DISP1_B equivale ao endere�o da porta RA0
#define DISP3_C PORTAbits.RA1          // define que DISP1_C equivale ao endere�o da porta RA1
#define DISP3_D PORTAbits.RA2          // define que DISP1_D equivale ao endere�o da porta RA2
#define DISP2_A PORTAbits.RA3          // define que DISP2_A equivale ao endere�o da porta RA3
#define DISP2_B PORTAbits.RA6          // define que DISP2_B equivale ao endere�o da porta RA4
#define DISP2_C PORTBbits.RB2          // define que DISP2_C equivale ao endere�o da porta RB2
#define DISP2_D PORTBbits.RB3          // define que DISP2_D equivale ao endere�o da porta RB3
#define DISP1_A PORTBbits.RB4          // define que DISP3_A equivale ao endere�o da porta RB4
#define DISP1_B PORTBbits.RB5          // define que DISP3_B equivale ao endere�o da porta RB5
#define DISP1_C PORTBbits.RB6          // define que DISP3_C equivale ao endere�o da porta RB6
#define DISP1_D PORTBbits.RB7          // define que DISP3_D equivale ao endere�o da porta RB7

// Definindo os pinos de entrada
#define sinal PORTBbits.RB0            // Define que sinal equivale ao endere�o da porta RB0
#define botao PORTBbits.RB1            // Define que botao equivale ao endere�o da porta RB1

// Vari�veis globais
volatile unsigned int cont = 0;         // Conta o n�mero de vezes que o sinal foi de alto para baixo
volatile unsigned int estouro_timer0 = 0; // Conta o n�mero de estouros do Timer0
volatile unsigned int status_ant = 1; // Guarda o estado anterior do sinal

// Criando Prototipos
void config(void);                      // Prot�tipo da fun��o de configura��o
void atualiza_displays(unsigned int valor); // Prot�tipo da fun��o para atualizar os displays
void __interrupt() myi(void);           // Prot�tipo da fun��o de interrup��o

void main(void) {
    config();
    while(1) {
        if(!botao) {  // Se o botao for pressionado
            TMR0 = 131; // Timer0 inicia valor 131
            T0IE = 1; // Habilita a interrupcao do Timer0 
            T0IF = 0; // Limpa a flag do Timer0
            cont = 0; // Zera o contador
        }
        if(estouro_timer0 == 7500){ // Quando a interrupcao tiver estourado 7500 vezes
            atualiza_displays(cont); // Mostra nos displays o valor do contador
            T0IE = 0; // Desabilita a interrupcao do Timer0
            T0IF = 0; // Limpa a flag do Timer0
            TMR0 = 131; // Timer0 inicia no valor 131
        }
    }   
}

void config(void) {
    CMCON = 0x07;           // Define valor do registro CMCON, definindo todos os pinos RAx como digitais

    TRISA = 0b00000000;     // Configura todos os pinos RAx como saida
    TRISB = 0b00000011;     // Configura os pinos de RBx como saida (0) ou entrada (1)

    PORTA = 0b00000000;     // Define estado de todas as saidas RA como zero ou apagados
    PORTB = 0b00000011;     // Define estado inicial das saidas RB2 a RB7 e ativa o pull-up interno para RB0 e RB1

    // Configuracao do Timer0
    T0CS = 0;               // Seleciona o clock interno
    PSA = 0;                // Prescaler e atribuido ao Timer0
    PS2 = 1;                // A combinacao de PS2, PS1 e PS0 equivale a uma proporcao do Prescaler. Nesse caso (101) equivale 1:64
    PS1 = 0;
    PS0 = 1;
    TMR0 = 131;             // Valor inicial do Timer0

    // Interrupcao do Timer0
    T0IE = 0;               // Desabilita interrupcao do Timer0
    T0IF = 0;               // Limpa a flag de interrupcao do Timer0

    // Interrupcao Global e Perifericas
    PEIE = 1;               // Habilita interrupcao dos perifericos
    GIE = 1;                // Habilita interrupcao global
    atualiza_displays(000);
}

void atualiza_displays(unsigned int valor) {
    unsigned char unidades, dezenas, centenas;

    unidades = valor % 10;                      // Obt�m as unidades do valor
    dezenas = (valor / 10) % 10;                // Obt�m as dezenas do valor
    centenas = (valor / 100) % 10;              // Obt�m as centenas do valor

    // Atualiza os segmentos do display de unidades
    DISP1_A = (unidades % 2) == 1;              // Atualiza o segmento A
    DISP1_B = ((unidades / 2) % 2) == 1;        // Atualiza o segmento B
    DISP1_C = ((unidades / 4) % 2) == 1;        // Atualiza o segmento C
    DISP1_D = ((unidades / 8) % 2) == 1;        // Atualiza o segmento D

    // Atualiza os segmentos do display de dezenas
    DISP2_A = (dezenas % 2) == 1;               // Atualiza o segmento A
    DISP2_B = ((dezenas / 2) % 2) == 1;         // Atualiza o segmento B
    DISP2_C = ((dezenas / 4) % 2) == 1;         // Atualiza o segmento C
    DISP2_D = ((dezenas / 8) % 2) == 1;         // Atualiza o segmento D

    // Atualiza os segmentos do display de centenas
    DISP3_A = (centenas % 2) == 1;              // Atualiza o segmento A
    DISP3_B = ((centenas / 2) % 2) == 1;        // Atualiza o segmento B
    DISP3_C = ((centenas / 4) % 2) == 1;        // Atualiza o segmento C
    DISP3_D = ((centenas / 8) % 2) == 1;        // Atualiza o segmento D
}

void __interrupt() myi(void) {
    estouro_timer0++; // A cada interrupção incrementa o contador de estouros do Timer0
    TMR0 = 131; // TImer0 inicia no valor 131
    T0IF = 0; // Limpa a flag de interrupção do Timer0
    
    if(!sinal && status_ant){ // SE o sinal for baixo e o status anterior for alto
        cont++; // Incrementa o contador
    }
    status_ant = sinal; // Guarda o estado para verificação na próxima interrupção
}
