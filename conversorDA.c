#include "conversorDA.h"

const uint32_t seno[100]={50,53,56,59,62,65,68,71,74,76,79,81,84,86,88,90,92,93,95,96,97,98,99,99,99,99,99,99,99,98,97,96,95,93,92,90,88,86,84,81,79,76,74,71,68,65,62,59,56,53,50,46,43,40,37,34,31,28,25,23,20,18,15,13,11,9,7,6,4,3,2,1,0,0,0,0,0,0,0,1,2,3,4,6,7,9,11,13,15,18,20,23,25,28,31,34,37,40,43,46};

uint32_t rampa_cont=0;
uint32_t triang_cont=0;


void onda_senoidal(){
    static uint32_t vet_pos=0;
    uint32_t valor=seno[vet_pos]*G_amp/100;
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0x00);
    SSIDataPut(SSI0_BASE, valor);
    while(SSIBusy(SSI0_BASE));
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0xFF);
    if(vet_pos==99)vet_pos=0;
    else vet_pos++;
}

void onda_rampa()
{
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0x00);
    SSIDataPut(SSI0_BASE, rampa_cont);   // 0x3FFF == 16383
    while(SSIBusy(SSI0_BASE));
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0xFF);

    if( rampa_cont  <= G_amp ) rampa_cont+=10;
    else rampa_cont = 0;
}

void onda_quadrada()
{
    static uint32_t quadrada_cont=0;
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0x00);
    SSIDataPut(SSI0_BASE, quadrada_cont);
    while(SSIBusy(SSI0_BASE));
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0xFF);

    static int maximo=0, aux=0;
    if( aux  >= G_amp ){
        maximo = 1;
        quadrada_cont = G_amp;
    }
    if( aux  <= 0 ){
        aux = 0;
        maximo = 0;
        quadrada_cont = 0;
    }

    if(maximo==0)
    {
        aux += 10;
    }else{
        aux-=10;
    }
}

void onda_triangular()
{
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0x00);
    SSIDataPut(SSI0_BASE, triang_cont);
    while(SSIBusy(SSI0_BASE));
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0xFF);

    static int descendo=0;
    if( triang_cont  >= G_amp  && descendo==0){
        descendo=1;
    }
    else if( triang_cont  <= 0 && descendo==1) descendo=0;
    else if(descendo==0) triang_cont+=10;
    else if(descendo==1) triang_cont-=10;
}
