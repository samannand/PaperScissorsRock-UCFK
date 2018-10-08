#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "character.h"
#include "ir_uart.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10

char charList[3] = {'P','S','R'};

int main (void)
{
    char character = charList[0];
    int index = 0;
    system_init ();

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);

    //Initialise navigation switch driver
    navswitch_init();

    pacer_init (PACER_RATE);

    while(1) {
        pacer_wait ();
        tinygl_update ();

        navswitch_update();

        //choosing characters
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            index ++;
            character = change_char(charList, &index);
        }

        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            index --;
            character = change_char(charList, &index);
        }
        display_char(character);

        //transmitting character to other device
        if(navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ir_uart_putc(character);
        }
        //receive character
        if(ir_uart_read_ready_p()) {
            char received_character = ir_uart_getc();
        }
    }
    return 0;
}
