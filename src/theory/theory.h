#ifndef THEORY_H
#define THEORY_H

/* Parses the provided string into Note structs
   which then and get added to the keyboard array. */
int th_line_parser(char string[]);

// Prints a all Notes from the keyboard array. Internally uses print_note(note)
void print_keyboard();

#endif