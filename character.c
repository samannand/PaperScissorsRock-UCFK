/**
 * @file character.c
 * @author Sam Annand, Alysha Voon
 * @brief Character module
 * @date_created 8 Oct 2018
 * @date_modified 15 Oct 2018
 * */

#include "tinygl.h"
#include "character.h"


/** Displays the character
 * @param character the user chose
 *  */
void display_char (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

/**
 * Functionality for changing the characters upon navswitch up or down
 * @param the list of characters
 * @param the index
 * @return the new character
 *
 * */
char change_char (char* charList, int *index)
{
    *index = (*index + 3) % 3;
    char character = charList[*index];
    return character;
}

/**
 * Functionality to check both characters and determine if it was a tie, win or loss
 * @param character that was sent
 * @param character that was received
 * @return character indicating a tie, win or loss
 * */
char checkWinner(char sent, char recv) {

    char result = 'T'; //Tie

    if (!(recv == 'R' || recv == 'P' || recv == 'S')) {
        result = 'E';
        return result;
    }

    if (sent == recv) {
        return result;
    } else if (sent == 'P') {
        if (recv == 'S') {
            result = 'L'; //Loss
        } else {
            result = 'W'; //Win
        }
    } else if (sent == 'R') {
        if (recv == 'P') {
            result = 'L';
        } else {
            result = 'W';
        }

    } else if (sent == 'S') {
        if (recv == 'R') {
            result = 'L';
        } else {
            result = 'W';
        }
    }
    return result;

}


