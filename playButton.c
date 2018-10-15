/**
 * @file playButton.c
 * @author Sam Annand, Alysha Voon
 * @brief button module
 * @date_created 12 Oct 2018
 * @date_modified 15 Oct 2018
 * */

#include "pio.h"
#include "playButton.h"


#define BTN_PIO PIO_DEFINE(PORT_D, 7)

/** If the button was pressed.
 * @return non-zero if the button is pressed */
int button_pressed (void)
{
    return pio_input_get(BTN_PIO);
}


/** Initialise button.  */
void button_init (void)
{
    pio_config_set(BTN_PIO, PIO_INPUT);
}
