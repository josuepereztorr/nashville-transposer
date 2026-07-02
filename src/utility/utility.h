#ifndef UTILITY_H
#define UTILITY_H

/* Prints ASCII decimal values from the provided string.
   The function does truncate (LN and CR) special control characters. */
void util_get_dec_ancii(char string[]);

//  Removes OS specifc control characters ('\r\n' or '\n') from the provided string[]
void util_truncate_control_char(char string[]);

#endif