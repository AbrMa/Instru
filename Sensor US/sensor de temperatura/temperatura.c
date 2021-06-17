#include <16f877a.h> // biblioteca del micro
#device adc=10 //adc de 10 bits
#include <stdio.h> //input output c
#include <math.h> //floor 
#fuses XT, NOWDT, NOPROTECT
#use delay (clock = 4MHz) // XT = 4MHz
#use rs232 (baud = 9600, parity = N, xmit = pin_c6, rcv = pin_c7, bits = 8 ) // configuración del puerto serial

void main () {
   int16 LSB;
   float voltajeTemperatura, temperatura;
   
   setup_adc_ports(all_analog);
   setup_adc(ADC_CLOCK_internal);
   
   while (true) {
      set_adc_channel(1);
      delay_ms(1000);
      LSB = read_adc();
      voltajeTemperatura = (LSB * 5.0) / 1023.0;
      temperatura = 20.0 * voltajeTemperatura;
      printf("Voltaje Temperatura %2.2f \r\n", voltajeTemperatura);
      printf("Temperatura %2.2f \r\n", floor(temperatura));
   }
}
