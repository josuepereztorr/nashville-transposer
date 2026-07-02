#ifndef THEORY_H
#define THEORY_H

/* Parses the provided row into a Note and loads it into keyboard[]. */
int theory_row_parser(char string[]);

/* Prints a all Notes from the keyboard array. Internally uses print_note(note)
   Note: atof() is used to convert a string to a double but, it doesn't provide any error hanlding.
         strcpy() is used to copy the src bytes to the destination bytes.
         Warning: could overwrite bytes if the destination is not large enough.
*/
void theory_print_keyboard();

#endif