#ifndef CONVERSORDA_H
#define CONVERSORDA_H

#include "global.h"
#include <stdint.h>
#include <stdbool.h>
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
#include <math.h>

#define AMP_MAX     10000
#define FREQ_MAX    2000


//uint32_t seno[100]={50,53,56,59,62,65,68,71,74,76,79,81,84,86,88,90,92,93,95,96,97,98,99,99,99,99,99,99,99,98,97,96,95,93,92,90,88,86,84,81,79,76,74,71,68,65,62,59,56,53,50,46,43,40,37,34,31,28,25,23,20,18,15,13,11,9,7,6,4,3,2,1,0,0,0,0,0,0,0,1,2,3,4,6,7,9,11,13,15,18,20,23,25,28,31,34,37,40,43,46};

void onda_senoidal();

void onda_quadrada();

void onda_rampa();

void onda_triangular();





#endif
