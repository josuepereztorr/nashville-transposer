#include <stdio.h>
#include "csv_reader.h"

/* Reads a csv file from the provided filename. Returns the number of rows read.
   If a -1 is returned, the filename provided is incorrect, the file is empty, or there was an error during reading. */
int csv_read(char filename[], char rows[][CSV_MAX_BUFFER_SIZE])
{
    // OS provides a handle for us to read the file.
    FILE *file = fopen(filename, "r");

    // pointer will be NULL if the file can't be opened ex. wrong path, no permissions, file doesn't exit.
    if (file == NULL)
    {
        // handle senario where the file cannot be opened
        printf("csv_reader: cannot open file: %s\n", filename);
        return -1;
    }

    printf("csv_reader: filename '%s' opened\n", filename);

    /* fgets() - returns a pointer (char *) to the buffer it wrote to on success. Otherwise, it will
                 return NULL if an error occurs or if the End of File (EOF) has been reached.
       char * - pointer to the buffer where each line is written.
       int n - max number of characters to write to buffer.
       File * - file to read from.
    */

    // counter tracks the number of lines.
    int counter = 0;

    // reads the header and discards it.
    while (fgets(rows[counter], CSV_MAX_BUFFER_SIZE, file) == NULL)
    {
        if (ferror(file))
        {
            printf("csv_reader: error discarding the header row\n");
            fclose(file);
            return -1;
        }
        printf("csv_reader: no header row exits\n");
    };

    printf("csv_reader: header removed\n");

    while (fgets(rows[counter], CSV_MAX_BUFFER_SIZE, file) != NULL)
    {
        counter++;
    }

    if (ferror(file))
    {
        printf("csv_reader: error reading rows\n");
        fclose(file);
        return -1;
    }

    printf("csv_reader: file read %i rows successfully\n", counter);
    fclose(file);
    return counter;
}
