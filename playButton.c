#include "pio.h"
#include "playButton.h"


#define BTN_PIO PIO_DEFINE(PORT_D, 7)

/** Return non-zero if button pressed.  */
int button_pressed (void)
{
    return pio_input_get(BTN_PIO);
}


/** Initialise button1.  */
void button_init (void)
{
    pio_config_set(BTN_PIO, PIO_INPUT);
}
