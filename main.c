#include "Nokia5110.h"

/*
Perguntas para o monitor:

1- Usar o UART significa que tem q digitar no terminal? Melhor usar UART ou botoes, que sao mais faceis?

2- Nao entendi o que sao os parametros de amplitude e frequencia, nao entendi a mudanca no display.

3- As ondas geradas tem que se mover ou podem ser estáticas? Se movem, a frequência que interfere na velocidade de movimento?

4- As mudanças periódicas são geradas por interrupt de timers?

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
 *  c)
 *
 *
 */

int main(void)
{
	// Habilita clock de 80 MHz
	SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_SYSDIV_2_5);

	//Habilita periféricos


	// Habilita interrupts


	// Configura timers


	//Inicializa display
	Nokia5110_Init();
    Nokia5110_Clear();
    
	while(1);
	return 0;
}
