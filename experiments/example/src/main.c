#include <platform.h>
#include <gpio.h>
#include <stdlib.h>

#define P_but PC_13
#define P_led PA_5
#define LED_ON 1

static int count =0;

//function that  handle the led
void led_set(int led_on)
{
	gpio_set(P_led , (!led_on) != LED_ON);
}

//function that initialize the led
void led_init(void)
{
	gpio_set_mode(P_led , Output);			 // we set the pin PA_5 as output
	led_set(0);                          //at the beggining we set the led closed
}

//interrupt handler for button
void button_press_isr(int sources)
{
	if((sources << GET_PIN_INDEX(P_but)) & (1 << GET_PIN_INDEX(P_but))){
		count ++;
	}
}

int main(void)
{
	led_init();
	led_set(0);
	
	//Set up on board swithc
	gpio_set_mode(P_but , PullUp);
	gpio_set_trigger(P_but , Rising);
	gpio_set_callback(P_but , button_press_isr);
	
	
	__enable_irq();
	
	while(1)
	{
		led_set(count & 1);
	}
}
