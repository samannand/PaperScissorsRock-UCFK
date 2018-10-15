/**
 * @file blueLed.c
 * @author Sam Annand, Alysha Voon
 * @brief led module
 * @date_created 12 Oct 2018
 * @date_modified 15 Oct 2018
 * */

#include "pio.h"
#include "blueLed.h"

#define LED_PIO PIO_DEFINE(PORT_C, 2)

/** Turn LED on.  */
void led_on (void)
{
  pio_output_high(LED_PIO);
}


/** Turn LED off.  */
void led_off (void)
{
   pio_output_low(LED_PIO);
}


/** Initialise LED.  */
void led_init (void)
{
    pio_config_set(LED_PIO, PIO_OUTPUT_LOW);
}

