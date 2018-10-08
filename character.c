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
