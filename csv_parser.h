#ifndef CSV_PARSER_H
#define CSV_PARSER_H

// Specifies the maximum number of characters per line
#define CSV_MAX_BUFFER_SIZE 50
// Specifies the maximum number of rows
#define CSV_MAX_ROWS 150

/* Reads a csv file from the provided filename. Returns the number of rows read.
   If a -1 is returned, the filename provided is incorrect or the file is empty. */
int csv_read(char filename[], char rows[][CSV_MAX_BUFFER_SIZE]);

#endif