#ifndef THEORY_H
#define THEORY_H

/* Parses the provided row into a Note and loads it into keyboard[]. */
int thry_row_parser(char string[]);

// Prints a all Notes from the keyboard array. Internally uses print_note(note)
void print_keyboard();

#endif