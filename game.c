#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "character.h"
#include "ir_uart.h"
#include "stdbool.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10

char charList[3] = {'P','S','R'};

int main (void)
{
    char character = charList[0];
    char sentChar;
    char recvChar;
    int index = 0;
    int rounds = 0;
    int winCount = 0;
    system_init ();

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    ir_uart_init();

    //Initialise navigation switch driver
    navswitch_init();

    pacer_init (PACER_RATE);
    bool transmitted = false;
    bool received = false;

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


        //transmitting character to other device
        if(navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ir_uart_putc(character);
            sentChar = character;
            transmitted = true;
        }
        //receive character
        if(ir_uart_read_ready_p()) {
            recvChar = ir_uart_getc();
            received = true;
        }

        if (transmitted && received) {
            transmitted = false;
            received = false;
            character = checkWinner(sentChar, recvChar);
            if (character == 'W') {
                winCount += 1;
            }
            if (character != 'T') {
                rounds += 1;
            }

            //display_char(character);
        }

        if (rounds >= 3 && winCount > (rounds - winCount)) {
            tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
            tinygl_text("WINNER");
        } else {
            tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
            tinygl_text("LOSER");
        }
        display_char(character);
    }
    return 0;
}
