#include "tinygl.h"
void display_char (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

char increment_char (char* charList, int index)
{
    if(index == 2) {
        index = 0;
    } else {
        index ++;
    }
    char character = charList[index];
    return character;
}


char decrement_char (char* charList, int index)
{
    if (index == 0) {
        index = 2;
    } else {
        index --;
    }
    char character = charList[index];
    return character;
}
