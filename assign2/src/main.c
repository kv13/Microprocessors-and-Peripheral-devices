#include <platform.h>
#include <gpio.h>
#include "delay.h"
#include <stdlib.h>

#define P_button PC_13
#define P_led    PA_5
#define LED_ON      1

static int counter; 
static int checker;
volatile double total_reaction_time;

void led_set(int led_on)
{
	gpio_set(P_led , (!led_on) != LED_ON);
}
void button_press_isr(int sources )
{
	if((sources << GET_PIN_INDEX(P_button)) & (1 << GET_PIN_INDEX(P_button))){
		led_set(0);
		checker = 1;
		total_reaction_time = counter*1/SystemCoreClock;
	}
}
void led_init(void)
{
	gpio_set_mode(P_led , Output);
	led_set(0);
}


int main(void)
{	
	//Set up on-board switch
	gpio_set_mode(P_button , PullUp);
	gpio_set_trigger(P_button , Rising);
	gpio_set_callback(P_button , button_press_isr);
	__enable_irq();
	double average_time =0;
	int i =0;
	led_init();
	led_set(0);
	
	//Set up on-board switch
	i=0;
	checker=0;
	counter=1;
	while(i < 5 )
	{
		delay_ms(rand()%9000+1000);
		led_set(1);
		while(checker==0){
			counter = counter + 20;
		}
		average_time = average_time + total_reaction_time;
		counter = 0;
		checker = 0;
		i=i+1;
	}
	average_time = average_time/5;
}
