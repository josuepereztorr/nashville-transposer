#include "scales.h"

#define OCTAVE 12

/* given a midi note (midi number 0-127) and a key (as semitone 0-11), return the corresponding scale degree (1-7).
   returns -1 if the note is not in the scale or a value (1-7) for the scale degree */
int get_scale_degree(int midi_note, int key_root)
{

    // PART 1: CHECK IF THE MIDI NOTE IS IN THE SCALE

    // calculates the chromatic scale position (0-11) ex. C would be 0, g would be 7 etc
    int target_position = midi_note % 12;

    // get the appropriate major scale
    const int *major_scale = lookup_table[key_root];

    // check if the note is in the scale
    int is_note_in_scale = major_scale[target_position];

    // if false, we can't provide a scale degree
    if (!is_note_in_scale)
    {
        return -1;
    }

    // PART 2: FIND THE THE DEGREE RELATIVE TO THE MAJOR SCALE
    // walks up the chromatic scale starting at root_key until it reaches the midi_note postiion (0-11)
    // the degree
    int major_scale_degree = 0;
    for (int offset = 0; offset < OCTAVE; offset++)
    {
        // position we're currently checking, starting at the root
        // offset (0-11) is used to move root position forward in semitones.
        int position = (key_root + offset) % 12;

        // if position is in the major scale, increase counter
        if (major_scale[position])
        {
            major_scale_degree++;
        }

        // stop once we find the note
        if (position == target_position)
        {
            break;
        }
    }

    return major_scale_degree;
}

/* given a scale degree (1-7) and a target key (0-11),
   return the chromatic position */
int get_transposed_note(int input_degree, int target_key_index)
{
    // get the appropriate major scale
    const int *major_scale = lookup_table[target_key_index];

    // traverse the octave
    int major_scale_degree = 0;
    for (int offset = 0; offset < OCTAVE; offset++)
    {
        // position we're currently checking, starting at the root
        // offset (0-11) is used to move root position forward in semitones.
        int position = (target_key_index + offset) % 12;

        // if position is in the major scale, increase counter
        if (major_scale[position])
        {
            major_scale_degree++;

            // if the both degrees match, return the position
            if (major_scale_degree == input_degree)
            {
                return position;
            }
        }
    }

    // the degree wasn't found
    return -1;
}