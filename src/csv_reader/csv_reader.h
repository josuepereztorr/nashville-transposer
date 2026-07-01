#ifndef CSV_READER_H
#define CSV_READER_H

// Specifies the maximum number of characters per line
#define CSV_MAX_BUFFER_SIZE 50
// Specifies the maximum number of rows
#define CSV_MAX_ROWS 150

/* Reads a csv file from the provided filename. Returns the number of rows read.
   If a -1 is returned, the filename provided is incorrect, the file is empty, or there was an error during reading. */
int csv_read(char filename[], char rows[][CSV_MAX_BUFFER_SIZE]);

#endif