#include <stdio.h>
#include "csv_parser.h"

/* Reads a csv file from the provided filename. Returns the number of rows read.
   If a -1 is returned, the filename provided is incorrect or the file is empty. */
int csv_read(char filename[], char rows[][CSV_MAX_BUFFER_SIZE])
{
    // OS provides a handle for us to read the file.
    FILE *file = fopen(filename, "r");

    // pointer will be NULL if the file can't be opened ex. wrong path, no permissions, file doesn't exit.
    if (file == NULL)
    {
        // TODO - get more information on using erno & perror
        return -1;
    }

    printf("File Opened\n");

    // counter tracks the number of lines.
    int counter = 0;

    // reads the header and discards it.
    fgets(rows[counter], CSV_MAX_BUFFER_SIZE, file);

    printf("Header Removed\n\n");

    /* fgets() - returns a pointer *char (if data is available).
       Otherwise, it will return NULL if an error occurs or if the End of File (EOF) has been reached. */
    while (fgets(rows[counter], CSV_MAX_BUFFER_SIZE, file) != NULL)
    {
        counter++;
    }

    // check which type of null - erno

    fclose(file);
    return counter;
}
