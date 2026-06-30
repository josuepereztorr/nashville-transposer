#include <stdio.h>
#include <string.h>
#include "utility.h"

void truncate_control_char(char string[])
{
    size_t length = strlen(string);

    for (int i = 0; i < length; i++)
    {
        // removing control characters which could be "\r\n" or '\n'
        // "\n" line feed
        // "\r" carriage return
        if (string[i] == '\r' && string[i + 1] == '\n')
        {
            // set the null terminator to the current index where "\r\n" was found
            string[i] = '\0';
            break;
        }

        if (string[i] == '\n')
        {
            string[i] = '\0';
        }
    }
}

void get_dec_ancii(char string[])
{
    printf("ASCII DEC Values (before): ");

    // prints all characters until the null terminator '\0'
    for (int i = 0; string[i] != '\0'; i++)
    {
        printf("%d ", string[i]);
    }

    printf("\n");

    truncate_control_char(string);

    printf("ASCII DEC Values (after): ");

    // prints the decimal equivalent of all characters in the array, except '\0'
    for (int i = 0; string[i] != '\0'; i++)
    {
        printf("%d ", string[i]);
    }

    printf("\n");
}