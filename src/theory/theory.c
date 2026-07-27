#include "theory.h"

// std lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// shared
#include "../utility/utility.h"

// Specifies the maximum number of notes per the MIDI standard. Ranges from 0-127.
#define MAX_MIDI_NOTES 128

// Stores the full range of notes (0-127) as Note structs.
Note keyboard[MAX_MIDI_NOTES] = {0};

// Verifies rows read matches MAX_NUM_OF_NOTES.
int row_counter = 0;

static void print_note(Note note);

int theory_row_parser(char string[])
{
    if (string == NULL)
    {
        fprintf(stderr, "theory_row_parser: string is NULL\n");
        return -1;
    }

    // empty string
    if (string[0] == '\0')
    {
        fprintf(stderr, "string is empty\n");
        return -1;
    }

    Note note = {0};

    // String Tokenizer
    char *midi_note = strtok(string, ",");

    if (midi_note == NULL)
    {
        // handle EOF or error
        return -1;
    }

    util_truncate_control_char(midi_note);
    note.note = atof(midi_note);

    char *note_name = strtok(NULL, ",");

    if (note_name == NULL)
    {
        // handle EOF or error
        return -1;
    }

    util_truncate_control_char(note_name);

    // strcopy could overwrite past the destination source so I made the name[] larger.
    strcpy(note.name, note_name);

    char *octave = strtok(NULL, ",");

    if (octave == NULL)
    {
        // handle EOF or error
        return -1;
    }

    util_truncate_control_char(octave);
    note.octave = atof(octave);

    note.status = 0;

    if (row_counter < MAX_MIDI_NOTES)
    {
        keyboard[row_counter] = note;
        row_counter++;
    }

    return 0;
}

void theory_print_keyboard()
{
    for (int i = 0; i < MAX_MIDI_NOTES; i++)
    {
        print_note(keyboard[i]);
    }
}

// Prints a formatted string from a Note struct.
static void print_note(Note note)
{
    printf("Status: %i\nNote: %i\nName: %s\nOctave: %i\n\n", note.status, note.note, note.name, note.octave);
}
