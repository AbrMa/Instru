#INCLUDE  <16f877a.h>
#DEVICE ADC=10
#FUSES XT, NOWDT, NOPROTECT, NOLVP, PUT, BROWNOUT
#USE DELAY (CLOCK=4MHz)
#USE RS232 (baud =9600, xmit = pin_c6, rcv=pin_c7, bits=8)

#DEFINE echo PIN_B0
#DEFINE trigger PIN_B1

float distancia;
double tiempo;

int16 duty;
int Timer2, poscaler;

void main ()
{
setup_timer_1(T1_internal|T1_div_by_1);
Timer2=249;

poscaler=1;
set_tris_c(0b11111110);
setup_ccp1 (ccp_pwm);
duty=0;

while (true)
{
set_pwm1_duty(duty);

output_high(trigger);
delay_us(10);
output_low(trigger);

while (!input(echo));
set_timer1 (0);

while (input (echo));
tiempo=get_timer1();
distancia=(tiempo/2)*(.0343);

printf("\r Distancia =%f cm" , distancia);
printf("\r Tiempo =%f seg", tiempo);

delay_ms(500);

if (distancia<= (3.5))
{
duty=0;
}
else if ( distancia>=331)
{
duty=331*3;
}
else 
{
duty=distancia*3;
}
delay_ms(200);
}
}







