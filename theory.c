#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_OF_NOTES 128
#define MAX_BUFFER_LINE_LENGTH 50

typedef struct
{
    int status;
    int note;
    char name[10];
    int octave;
} Note;

static Note keyboard[MAX_NUM_OF_NOTES] = {0};
static int notes_per_scale = 12;

void create_keyboard()
{
}

//  Removes csv control characters ('\n' and/or '\r') from the provided char[]
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
            string[i] = '\0';
            break;
        }

        if (string[i] == '\n')
        {
            string[i] = '\0';
        }
    }
}

// Prints all the ASCII decimal values from char[]
void get_dec_ancii(char string[])
{
    printf("ASCII DEC Values (before): ");

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
        // printf("%d ", (unsigned char)string[i]);
        printf("%d ", string[i]);
    }

    printf("\n");
}

// Tokenizes and parses the provided char[]
int line_parser(char string[], int counter)
{
    Note note;

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

    // set note.status to off
    note.status = 0;
    // printf("%d\n", counter);
    //  add to keyboard array
    if (counter < MAX_NUM_OF_NOTES)
    {
        keyboard[counter] = note;
    }

    // printf("Note Struct: %i, %i, %s, %i\n\n", note.status, note.note, note.name, note.octave);
    return 0;
}

// Reads the midi_notes.csv file
int read_cvs()
{
    // OS provides a handle for us to read the file.
    FILE *file = fopen("midi_notes.csv", "r");

    // pointer will be NULL if the file can't be opened ex. wrong path, no permissions, file doesn't exit.
    if (file == NULL)
    {
        // TODO - get more information on using erno & perror
        return -1;
    }

    /* holds one line of characters (MAX_BUFFER_LINE_LENGTH - 1),
       including the control characters (or non-printing characters)
       "\n" line feed
       "\r" carriage return
       "\0" null character */
    char buffer[MAX_BUFFER_LINE_LENGTH] = {0};

    // reads the header and discards it.
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        break;
    }

    //
    int counter = 0;

    // buffer - is used to hold temporary data (one line from csv)
    // returns a pointer to the buffer or NULL if an error occurs or if the End of File (EOF) has reached.
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {

        line_parser(buffer, counter);
        counter++;
    }

    // for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
    // {
    //     printf("Note Struct: %i, %i, %s, %i\n", keyboard[i].status, keyboard[i].note, keyboard[i].name, keyboard[i].octave);
    // }

    fclose(file);
    return 0;
}
