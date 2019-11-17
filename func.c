#include "func.h"


void onda_senoidal_display(){
	 Nokia5110_ClearBuffer();
	 static uint32_t pos=0;

	 uint32_t cont, descendo=0,c1=0,c2,imp=0;
	 for(cont=pos;cont<84;cont++){
	     c1++;
	     if(c1==21){
	         c1=0;
	         if(descendo==0){
	             descendo=1;
	             Nokia5110_SetPxl(36,cont);
	             imp=0;
	         }
	         else{
	             descendo=0;
	             Nokia5110_SetPxl(10,cont);
	             imp=0;
	         }
	     }else if(descendo==0){
	         if(c1<=2){
	             Nokia5110_SetPxl(10+imp,cont);
	         }else if(c1<=5){
	             Nokia5110_SetPxl(10+imp,cont);
	             imp++;
	         }else if(c1<=15){
	             for(c2=0;c2<2;c2++){
	                 Nokia5110_SetPxl(10+imp+c2,cont);
	             }
                 imp+=2;
	         }else if(c1<=18){
	             Nokia5110_SetPxl(10+imp,cont);
	             imp++;
	         }else if(c1<=20){
	             Nokia5110_SetPxl(10+imp,cont);
	         }
	     }else if(descendo==1){
	         if(c1<=2){
                  Nokia5110_SetPxl(36-imp,cont);
              }else if(c1<=5){
                  Nokia5110_SetPxl(36-imp,cont);
                  imp++;
              }else if(c1<=15){
                  for(c2=0;c2<2;c2++){
                      Nokia5110_SetPxl(36-imp+c2,cont);
                  }
                  imp+=2;
              }else if(c1<=18){
                  Nokia5110_SetPxl(36-imp,cont);
                  imp++;
              }else if(c1<=20){
                  Nokia5110_SetPxl(36-imp,cont);
              }
	     }
	 }
	 for(cont=0;cont<pos;cont++){
	     c1++;
	              if(c1==21){
	                  c1=0;
	                  if(descendo==0){
	                      descendo=1;
	                      Nokia5110_SetPxl(36,cont);
	                      imp=0;
	                  }
	                  else{
	                      descendo=0;
	                      Nokia5110_SetPxl(10,cont);
	                      imp=0;
	                  }
	              }else if(descendo==0){
	                  if(c1<=2){
	                      Nokia5110_SetPxl(10+imp,cont);
	                  }else if(c1<=5){
	                      Nokia5110_SetPxl(10+imp,cont);
	                      imp++;
	                  }else if(c1<=15){
	                      for(c2=0;c2<2;c2++){
	                          Nokia5110_SetPxl(10+imp+c2,cont);
	                      }
	                      imp+=2;
	                  }else if(c1<=18){
	                      Nokia5110_SetPxl(10+imp,cont);
	                      imp++;
	                  }else if(c1<=20){
	                      Nokia5110_SetPxl(10+imp,cont);
	                  }
	              }else if(descendo==1){
	                  if(c1<=2){
	                       Nokia5110_SetPxl(36-imp,cont);
	                   }else if(c1<=5){
	                       Nokia5110_SetPxl(36-imp,cont);
	                       imp++;
	                   }else if(c1<=15){
	                       for(c2=0;c2<2;c2++){
	                           Nokia5110_SetPxl(36-imp+c2,cont);
	                       }
	                       imp+=2;
	                   }else if(c1<=18){
	                       Nokia5110_SetPxl(36-imp,cont);
	                       imp++;
	                   }else if(c1<=20){
	                       Nokia5110_SetPxl(36-imp,cont);
	                   }
	              }
	 }
	 if(pos==83)pos=0;
	 else pos++;
	 Nokia5110_DisplayBuffer();

}

void onda_quadrada_display(){
	 Nokia5110_ClearBuffer();
	 static uint32_t pos=0;

	 uint32_t cont, estado=0, c1=0, c2;
	 for(cont=pos;cont<84;cont++){
	 	c1++;
	 	if(c1==21){
	 		for(c2=0;c2<36;c2++) Nokia5110_SetPxl(6+c2,cont);
	 		c1=0;
	 		if(estado==0)estado=1;
	 		else estado=0;
  		}else if (estado==0){
	 		Nokia5110_SetPxl(6,cont);
	 	}else if(estado==1){
	 		Nokia5110_SetPxl(41,cont);
	 	}
	 }
	 for(cont=0;cont<pos;cont++){
	 	c1++;
	 	if(c1==21){
	 		for(c2=0;c2<36;c2++) Nokia5110_SetPxl(6+c2,cont);
	 		c1=0;
	 		if(estado==0)estado=1;
	 		else estado=0;
  		}else if (estado==0){
	 		Nokia5110_SetPxl(6,cont);
	 	}else if(estado==1){
	 		Nokia5110_SetPxl(41,cont);
	 	}
	 }
	 if(pos==83)pos=0;
	 else pos++;
	 Nokia5110_DisplayBuffer();

}

void onda_triangular_display(){
	 Nokia5110_ClearBuffer();
	 static uint32_t pos=0;

	 uint32_t cont, descendo=0, c1=0;
	 for(cont=pos;cont<84;cont++){
	 	c1++;
	 	if(c1==21){
	 		c1=0;
	 		if(descendo==0){
	 			Nokia5110_SetPxl(34,cont);
	 			descendo=1;
	 		}else{
	 			descendo=0;
	 			Nokia5110_SetPxl(13,cont);
	 		}
  		}else if (descendo==0){
	 		Nokia5110_SetPxl(13+c1,cont);
	 	}else if(descendo==1){
	 		Nokia5110_SetPxl(34-c1,cont);
	 	}
	 }
	 for(cont=0;cont<pos;cont++){
	 	c1++;
	 	if(c1==21){
	 		c1=0;
	 		if(descendo==0){
	 			Nokia5110_SetPxl(34,cont);
	 			descendo=1;
	 		}else{
	 			descendo=0;
	 			Nokia5110_SetPxl(13,cont);
	 		}
  		}else if (descendo==0){
	 		Nokia5110_SetPxl(13+c1,cont);
	 	}else if(descendo==1){
	 		Nokia5110_SetPxl(34-c1,cont);
	 	}
	 }
	 if(pos==83)pos=0;
	 else pos++;
	 Nokia5110_DisplayBuffer();
}

void onda_rampa_display(){
	Nokia5110_ClearBuffer();
	static uint32_t pos=0;

	uint32_t cont, c1=0, c2;
	for(cont=pos;cont<84;cont++){
		c1++;
		if(c1==21){
			c1=0;
			for(c2=0;c2<21;c2++)Nokia5110_SetPxl(13+c2,cont);
 		}else{
 			Nokia5110_SetPxl(33-c1,cont);
 		}
	}
	for(cont=0;cont<pos;cont++){
		c1++;
		if(c1==21){
			c1=0;
			for(c2=0;c2<21;c2++)Nokia5110_SetPxl(13+c2,cont);
 		}else{
 			Nokia5110_SetPxl(33-c1,cont);
 		}
	}
	if(pos==83)pos=0;
	else pos++;
	Nokia5110_DisplayBuffer();

}

void inf_display(){
	Nokia5110_Clear();
	Nokia5110_Cursor(0,0);
	Nokia5110_OutString("    ONDA");
	Nokia5110_Cursor(0,1);
	switch(G_forma){
		case senoidal:
			Nokia5110_OutString("  SENOIDAL");
			break;
		case rampa:
			Nokia5110_OutString("   RAMPA");
			break;
		case triangular:
			Nokia5110_OutString(" TRIANGULAR");
			break;
		case quadrada:
			Nokia5110_OutString(" QUADRADA");
			break;
	}
	Nokia5110_Cursor(0,3);
	Nokia5110_OutString(" F: ");
	Nokia5110_Cursor(4,3);
	Nokia5110_OutUDec(G_freq);
	Nokia5110_Cursor(0,4);
	Nokia5110_OutString(" A: ");
	Nokia5110_Cursor(4,4);
	Nokia5110_OutUDec(G_amp);
}
