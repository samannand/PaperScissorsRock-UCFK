#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "character.h"


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

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            index ++;
            character = change_char(charList, &index);
        }

        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            index --;
            character = change_char(charList, &index);
        }
        display_char(character);
    }
    return 0;
}
