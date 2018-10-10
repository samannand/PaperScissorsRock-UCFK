#include "tinygl.h"
void display_char (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

char change_char (char* charList, int *index)
{
    *index = (*index + 3) % 3;
    char character = charList[*index];
    return character;
}

char checkWinner(char sent, char recv) {

    char result = 'T';
    if (sent == recv) {
        return result;
    } else if (sent == 'P') {
        if (recv == 'S') {
            result = 'L';
        } else {
            result = 'W';
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


