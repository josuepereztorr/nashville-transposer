#include "csv_parser/csv_parser.h"
#include "theory/theory.h"

int main()
{
    // read csv file
    char rows[CSV_MAX_ROWS][CSV_MAX_BUFFER_SIZE] = {};
    int rows_read = csv_read("./data/midi_notes.csv", rows);

    // parse data and verify keyboard array is successfuly filled
    for (int row = 0; row < rows_read; row++)
    {
        th_line_parser(rows[row]);
    }
    print_keyboard();

    // start midi detection

    return 0;
};

// clang main.c -I/usr/local/include -L/usr/local/lib -lportmidi -o nashville_transposer
// ./nashville_transposer