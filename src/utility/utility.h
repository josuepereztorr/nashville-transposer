#ifndef UTILITY_H
#define UTILITY_H

/* Prints ASCII decimal values from the provided string. 
   The function does truncate (LN and CR) special control characters. */
void get_dec_ancii(char string[]);

//  Removes OS specifc control characters ('\r\n' or '\n') from the provided string[]
void truncate_control_char(char string[]);

#endif