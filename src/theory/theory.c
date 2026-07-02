#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "theory.h"
#include "../utility/utility.h"

// Specifies the maximum number of notes per the MIDI standard. Ranges from 0-127.
#define MAX_NUM_OF_NOTES 128

typedef struct
{
    int status;
    int note;
    char name[10];
    int octave;
} Note;

// Stores the full range of notes (0-127) as Note structs.
Note keyboard[MAX_NUM_OF_NOTES] = {0};
int line_counter = 0;

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

    if (line_counter < MAX_NUM_OF_NOTES)
    {
        keyboard[line_counter] = note;
        line_counter++;
    }

    return 0;
}

void theory_print_keyboard()
{
    for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
    {
        print_note(keyboard[i]);
    }
}

// Prints a formatted string from a Note struct.
static void print_note(Note note)
{
    printf("Status: %i\nNote: %i\nName: %s\nOctave: %i\n\n", note.status, note.note, note.name, note.octave);
}
