#include <stdio.h>
#include "csv_reader/csv_reader.h"
#include "theory/theory.h"
#include "midi/midi.h"

#define CSV_DATA_PATH "./data/midi_notes.csv"

int main()
{
    // get data from csv
    char rows[CSV_MAX_ROWS][CSV_MAX_BUFFER_SIZE] = {};
    int rows_read = csv_read(CSV_DATA_PATH, rows);

    if (rows_read < 0)
    {
        printf("main: failed to load data from '%s'\n", CSV_DATA_PATH);
        return 1;
    }

    // parse and load data
    for (int row = 0; row < rows_read; row++)
    {
        thry_row_parser(rows[row]);
    }

    // start midi detection
    PmError err = midi_start();

    if (err != pmNoError)
    {
        printf("main: failed to load PortMIDI");
        return 1;
    }

    return 0;
};

// clang src/main.c src/csv_reader/*.c src/theory/*.c src/utility/*.c src/midi/*.c -I/usr/local/include -L/usr/local/lib -lportmidi -o build/nashville_transposer
// ./build/nashville_transposer