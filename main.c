#define MAIN_FILE
#include "global.h"
#include "func.h"
#include "Nokia5110.h"
#include "conversorDA.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"

/*
Perguntas para o monitor:

2- Nao entendi o que sao os parametros de amplitude e frequencia, nao entendi a mudanca no display.
Bancos verticas para amplitude

3- As ondas geradas tem que se mover ou podem ser estáticas? Se movem, a frequência que interfere na velocidade de movimento?
tem q andar

4- As mudanças periódicas são geradas por interrupt de timers?
blz

PINOS CONFLITANTES: A2 e A7

*/

/*
 *  Perguntas:
 *
 *  a)  1- ~SYNC (PB4)
 *      2- SCLK  (PA2)
 *      3- Din   (PA7)
 *
 *  b) Maximo de 50 MHz
 *
 *  Presets:
 *  20000  ==20k
 *  ate
 *  100000 == 100k
 *
 *  talvez ate 80k ou menos para usar os 2 juntos
 *
 *
 */


const char opcoes[]={"Wave options: s, q, r, t\n\rFrequency options: f1, f2, f3, f4\n\rAmplitude options: a1, a2, a3\n\r"};
const char read[]={"Read: "};
const char incorrect[]={" (Incorrect)"};

void printOpcoes(){
    uint32_t cont;
    for(cont=0; cont<92; cont++) UARTCharPut(UART0_BASE, opcoes[cont]);
}

void trataUART0(void){
    UARTIntClear(UART0_BASE, UART_INT_RX);
    uint32_t c1,c2,lido=0;
    c1 = UARTCharGet(UART0_BASE);
    if(c1 == 's'){G_forma=senoidal;lido=2;}
    if(c1 == 't'){G_forma=triangular;lido=2;}
    if(c1 == 'r'){G_forma=rampa;lido=2;}
    if(c1 == 'q'){G_forma=quadrada;lido=2;}
    if(lido!=2)
        c2 = UARTCharGet(UART0_BASE);
    if(c1 == 'f'){
        if(c2== '1') {G_freq=20000;lido++;}
        if(c2== '2') {G_freq=40000;lido++;}
        if(c2== '3') {G_freq=60000;lido++;}
        if(c2== '4') {G_freq=80000;lido++;}
        if(c2== '5') {G_freq=100000;lido++;}
        SysTickDisable();
        SysTickIntDisable();
        SysTickPeriodSet(SysCtlClockGet()/G_freq);
        SysTickIntEnable();
        SysTickEnable();
    }
    if(c1 == 'a'){
        if(c2 == '1') {G_amp=8000;lido++;}
        if(c2 == '2') {G_amp=10000;lido++;}
        if(c2 == '3') {G_amp=12000;lido++;}
        if(c2 == '4') {G_amp=14000;lido++;}
        if(c2 == '5') {G_amp=16000;lido++;}
    }
    uint32_t cont;
    for(cont=0;cont<6;cont++) UARTCharPut(UART0_BASE, read[cont]);
    UARTCharPut(UART0_BASE, c1);
    if(lido!=2)
        UARTCharPut(UART0_BASE, c2);
    if(lido == 0)
        for(cont=0;cont<12;cont++) UARTCharPut(UART0_BASE, incorrect[cont]);
    UARTCharPut(UART0_BASE, '\n');
    UARTCharPut(UART0_BASE, '\n');
    UARTCharPut(UART0_BASE, '\r');
    printOpcoes();
}

void trata_period_display(){
	static cont=0, mode=0;
	cont++;
	if(cont==10){
		cont=0;
		if(mode==0)mode=1;
		else mode=0;
	}
	if(mode==1){
		inf_display();
		return;
	}
    switch(G_forma){
        case rampa:
            onda_rampa_display();
            break;
        case senoidal:
            onda_senoidal_display();
            break;
        case triangular:
            onda_triangular_display();
            break;
        case quadrada:
            onda_quadrada_display();
            break;
    }
}


void trata_period(){
    switch(G_forma){
        case rampa:
            onda_rampa();
            break;
        case senoidal:
            onda_senoidal();
            break;
        case triangular:
            onda_triangular();
            break;
        case quadrada:
            onda_quadrada();
            break;
    }
}

int main(void)
{
	// Habilita clock de 80 MHz
	//SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_SYSDIV_2_5);

	//Inicializa display

	Nokia5110_Init();
    Nokia5110_Clear();
    SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_SYSDIV_12);

    SysTickIntDisable();
    SysTickPeriodSet(SysCtlClockGet());
    SysTickIntRegister(trata_period_display);
    SysTickIntEnable();
    SysTickEnable();

	//Habilita periféricos
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);


    // Inicializa as variáveis globais
    G_amp=10000;
    G_freq=100000;
    G_forma=senoidal;

    // Configura pinos UART
    GPIOPinConfigure(GPIO_PA0_U0RX);	
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	UARTEnable(UART0_BASE);

	// Habilita interrupts
	IntMasterEnable();
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    UARTIntRegister(UART0_BASE, trataUART0);

    // Configura SSI
    /*GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);

    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4);

    GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);

    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_5);

    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_2, SSI_MODE_MASTER, 3000000, 16); // 16 bits transferidos

    SSIEnable(SSI0_BASE);

    SysTickIntDisable();
    SysTickPeriodSet(SysCtlClockGet()/G_freq);
    SysTickIntRegister(trata_period);
    SysTickIntEnable();
    SysTickEnable();*/

    printOpcoes();
	while(1);
	return 0;
}


