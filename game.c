#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "character.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10


int main (void)
{
    char charList[3] = {'P','S','R'};
    char character = charList[0];
    int index = 0;
    system_init ();

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);

    //Initialise navigation switch driver
    navswitch_init();

    pacer_init (PACER_RATE);

    while(1) {
        pacer_wait ();
        tinygl_update ();

        navswitch_update();

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            character = increment_char(charList, index);
        }

        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            character = decrement_char(charList, index);
        }
        display_char(character);
    }
    return 0;
}
