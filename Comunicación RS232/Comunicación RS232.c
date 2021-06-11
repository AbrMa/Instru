//librerias
#include <16F877A.h>
#include <stdio.h>

//configuración
#use delay (CLOCK=4M)
#use RS232(baud=9600, parity=N, xmit=pin_c6, rcv=pin_c7, bits=8)
#fuses xt, noprotect, nowdt

//configuración entrada
#byte PORTA=5
#define BTN PORTA,0

//configuración salida
#byte PORTD=8
#define LED PORTD, 2

char accion; // 'E' -> encender, 'A' -> apagar

//interrupción pa leer la accion
#INT_RDA
void rda_isr(){
   accion = getc();
   if (accion == 'E') // si es 'E'
       bit_set(LED); // enciende el LED
   else
      bit_clear(LED); //de lo contrario lo apaga
}

void main(){
   SET_TRIS_A(0X0F); // config entrada
   SET_TRIS_D(0xF0); // config salida 
   PORTD=0x00;
   //interrupciones pa leer la acción 
   enable_interrupts(int_rda);
   enable_interrupts(global);
   //enviar acción dependieno de si oprimimos el botón o no
   while (true){
      if(bit_test(BTN))
         putchar('E');
      else
         putchar('A');
   }
}
