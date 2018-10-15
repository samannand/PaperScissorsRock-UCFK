/**
 * @file character.h
 * @author Sam Annand, Alysha Voon
 * @brief Character header file
 * @date_created 8 Oct 2018
 * @date_modified 15 Oct 2018
 * */


/** Displays the character
 * @param character the user chose
 *  */
void display_char(char character);


/**
 * Functionality for changing the characters upon navswitch up or down
 * @param the list of characters
 * @param the index
 * @return the new character
 *
 * */
char change_char (char* charList, int *index);

/**
 * Functionality to check both characters and determine if it was a tie, win or loss
 * @param character that was sent
 * @param character that was received
 * @return character indicating a tie, win or loss
 * */
char checkWinner(char sent, char recv);
