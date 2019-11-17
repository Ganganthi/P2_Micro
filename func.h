#ifndef FUNC_H
#define FUNC_H

#include "global.h"
#include "Nokia5110.h"

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/uart.h"
#include "driverlib/rom.h"
#include "driverlib/lcd.h"
#include "driverlib/ssi.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h" 
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_ssi.h"

#define rampa 0
#define quadrada 1
#define senoidal 2
#define triangular 3

void onda_senoidal_display();
void onda_triangular_display();
void onda_quadrada_display();
void onda_rampa_display();

void inf_display();

#endif
