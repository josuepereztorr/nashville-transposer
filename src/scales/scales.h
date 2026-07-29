/*
 * ============================================================
 * File    : scales.h
 * Project : Nashville Transposer
 * ============================================================
 * Author   : Josue Perez Torres
 * Created  : 07-28-2026
 * Modified : 07-28-2026
 * Version  : 1.0.0
 * ============================================================
 * Description:
 *     Major scales lookup tables and scale-degree/transposition
 *     function declarations.
 * ============================================================
 * Dependencies:
 *     None.
 * ============================================================
 */

#ifndef SCALES_H
#define SCALES_H

// ------------------------------------------------------------
// CONSTANT & MACROS
// ------------------------------------------------------------

// each array marks which of the 12 chromatic semitones belong to that key's major scale
static const int scale_c[12] = {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1};
static const int scale_c_sharp[12] = {1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0};
static const int scale_d[12] = {0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1};
static const int scale_d_sharp[12] = {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0};
static const int scale_e[12] = {0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1};
static const int scale_f[12] = {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0};
static const int scale_f_sharp[12] = {0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1};
static const int scale_g[12] = {1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1};
static const int scale_g_sharp[12] = {1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0};
static const int scale_a[12] = {0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1};
static const int scale_a_sharp[12] = {1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0};
static const int scale_b[12] = {0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1};

// NOTE: lookup_table[] and major_scales[] must stay in the same order.
static const int *lookup_table[12] = {
    scale_c, scale_c_sharp, scale_d, scale_d_sharp, scale_e, scale_f,
    scale_f_sharp, scale_g, scale_g_sharp, scale_a, scale_a_sharp, scale_b};

static const char *major_scales[12] = {
    "C Major", "C# Major", "D Major", "D# Major", "E Major", "F Major",
    "F# Major", "G Major", "G# Major", "A Major", "A# Major", "B Major"};

static const char *note_names[12] = {
    "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

// ------------------------------------------------------------
// PUBLIC FUNCTION PROTOTYPES
// ------------------------------------------------------------

int get_scale_degree(int midi_note, int key_root);

int get_transposed_note(int input_degree, int target_key_index);

#endif