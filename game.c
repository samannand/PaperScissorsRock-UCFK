/**
 * @file game.c
 * @author Sam Annand, Alysha Voon
 * @brief Game module
 * @date_created 5 Oct 2018
 * @date_modified 15 Oct 2018
 * */

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "character.h"
#include "ir_uart.h"
#include "stdbool.h"
#include "playButton.h"
#include "blueLed.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10
#define MAX_TICK 500
#define MAX_ROUNDS 3

char charList[3] = {'P','S','R'};

int main (void)
{

    //initialisations
    system_init ();
    navswitch_init();
    button_init();
    led_init();
    pacer_init (PACER_RATE);
    ir_uart_init();

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);


    int index = 0;
    int rounds = 0;
    int winCount = 0;
    int lossCount = 0;
    int tick = 0;

    char character = charList[0];
    char sentChar = charList[0];
    char recvChar = charList[0];


    bool transmitted = false;
    bool received = false;
    bool gameOver = false;
    bool displayScore = false;


    while(1) {
        pacer_wait ();
        tinygl_update ();

        navswitch_update();

        //choosing characters
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            led_off();
            index ++;
            character = change_char(charList, &index);
        }

        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            led_off();
            index --;
            character = change_char(charList, &index);
        }



        //transmitting character to other device
        if(navswitch_push_event_p(NAVSWITCH_PUSH) && !transmitted) {
            ir_uart_putc(character);
            sentChar = character;
            transmitted = true;
        }
        //receiving character
        if(ir_uart_read_ready_p() && !received) {
            recvChar = ir_uart_getc();
            received = true;
        }

        //Calculating winner and scores
        if (transmitted && received) {
            transmitted = false;
            received = false;
            character = checkWinner(sentChar, recvChar);
            if(character == 'E') { //error handling
                character = charList[index];
                transmitted = true;
            } else if (character == 'K') {
                character = charList[index];
                received = true;
            }
            display_char(character);
            displayScore = true;
            if (character == 'W') { //won the round
                winCount += 1;
                led_on();
                rounds += 1;
            } else if (character == 'L') { //lost the round
                lossCount += 1;
                rounds += 1;
            }


        }

        //displaying the score
        if (displayScore) {
            if (tick >= MAX_TICK) {
                char tempCount = winCount;
                character = tempCount + '0';
                displayScore = false;
                tick = 0;
            }
            tick ++;
        }

        //Showing who won the overall game
        if (rounds < MAX_ROUNDS) {
            display_char(character);
        } else if (winCount > lossCount && !gameOver) { //won the game
            tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
            tinygl_text("WINNER");
            gameOver = true;

        } else if (lossCount > winCount && !gameOver) { //lost the game
            tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
            tinygl_text("LOSER");
            gameOver = true;
        }

        //Reset game (start over)
        if(button_pressed() && gameOver) {
            led_on();
            rounds = 0;
            winCount = 0;
            lossCount = 0;
            transmitted = false;
            received = false;
            tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
            index = 0;
            character = charList[index];
            gameOver = false;

        }

    }
    return 0;
}
