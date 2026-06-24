#include <string.h>
#include <stdio.h>

#define MAX_NUM_OF_NOTES 128
#define MAX_BUFFER_LINE_LENGTH 50

typedef struct
{
    int status;
    int note;
    char name[2];
    int octave;
} Note;

static Note keyboard[MAX_NUM_OF_NOTES] = {0};
static int notes_per_scale = 12;

void create_keyboard()
{
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

    // buffer - is used to hold temporary data (one line from csv)
    // returns a pointer to the buffer or NULL if an error occurs or if the End of File (EOF) has reached.
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // what to do with the data
        // parse data by removing the control characters
        char *data = strtok(buffer, ",");
        printf("Note: %s\n", data);
    }

    // NULL case

    fclose(file);
    return 0;
}