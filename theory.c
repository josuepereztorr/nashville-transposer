#include <stdio.h>
#include <stdlib.h>
#include "utility.c"

#define MAX_NUM_OF_NOTES 128
#define MAX_BUFFER_LINE_LENGTH 50

typedef struct
{
    int status;
    int note;
    char name[10];
    int octave;
} Note;

Note keyboard[MAX_NUM_OF_NOTES] = {0};

int line_parser(char string[], int counter);
int read_csv();
void print_keyboard();
void print_note(Note note);

// Tokenizes and parses the provided char[].
int line_parser(char string[], int counter)
{
    Note note = {0};

    // String Tokenizer
    char *midi_note = strtok(string, ",");

    if (midi_note == NULL)
    {
        // handle EOF or error
        return -1;
    }

    truncate_control_char(midi_note);
    note.note = atof(midi_note);

    char *note_name = strtok(NULL, ",");

    if (note_name == NULL)
    {
        // handle EOF or error
        return -1;
    }

    truncate_control_char(note_name);

    // doesn't work since it passes a pointer not the value.
    // note.name = note_name;

    // have to pass a copy of the value at *note_name
    strcpy(note.name, note_name);

    char *octave = strtok(NULL, ",");

    if (octave == NULL)
    {
        // handle EOF or error
        return -1;
    }

    truncate_control_char(octave);
    note.octave = atof(octave);

    note.status = 0;

    if (counter < MAX_NUM_OF_NOTES)
    {
        keyboard[counter] = note;
    }

    return 0;
}

// Reads the midi_notes.csv file
int read_csv()
{
    // OS provides a handle for us to read the file.
    FILE *file = fopen("midi_notes.csv", "r");

    // pointer will be NULL if the file can't be opened ex. wrong path, no permissions, file doesn't exit.
    if (file == NULL)
    {
        // TODO - get more information on using erno & perror
        return -1;
    }

    // holds one row from the csv file, including control characters (or non-printing characters)
    char buffer[MAX_BUFFER_LINE_LENGTH] = {0};

    // reads the header and discards it.
    while (fgets(buffer, MAX_BUFFER_LINE_LENGTH, file) != NULL)
    {
        break;
    }

    // counter tracks the number of lines tokenized and parsed.
    int counter = 0;

    /* fgets() - returns a pointer *char (if data is available).
       Otherwise, it will return NULL if an error occurs or if the End of File (EOF) has been reached. */
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        line_parser(buffer, counter);
        counter++;
    }

    fclose(file);
    return 0;
}

// Prints all notes from the keyboard[].
void print_keyboard()
{
    for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
    {
        Note note = keyboard[i];
        print_note(note);
    }
}

// Prints a Note.
void print_note(Note note)
{
    printf("Status: %i\nNote: %i\nName: %s\nOctave: %i\n\n", note.status, note.note, note.name, note.octave);
}
