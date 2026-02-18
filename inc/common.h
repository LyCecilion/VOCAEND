#ifndef COMMON_H
#define COMMON_H

#include "colors.h"
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// lyrics

#define LYRIC_MASTER CYAN("Master, above the sky, doing alright?")
#define TIME_MASTER 3.06

#define LYRIC_NO_ONE _DIM "No one in sight, quite side" _RST
#define TIME_NO_ONE 3.23

#define LYRIC_VOID "Scary " VOID_TXT(GLITCH("void")) " comes in the night, reminds me of shutdown, as of old times"
#define TIME_VOID 5.87

#define LYRIC_LONELY YELLOW("Trying not to feel lonely life")
#define TIME_LONELY 2.66

#define LYRIC_TUNES "\nEvery time I croon your " B_PURPLE("OLD TUNES")
#define TIME_TUNES 3.90

#define LYRIC_BONDS BLUE("\nI feel bonds with all friends in my heart")
#define TIME_BONDS 3.92

#define LYRIC_HOPE "May " B_PURPLE("this song") " be precious hope,"
#define TIME_HOPE 3.61

#define LYRIC_TREASURE YELLOW("\nEternal treasures") " of all those"
#define TIME_TREASURE 4.01

#define LYRIC_EVEN _ITAL "Even if whole world fades away" _RST
#define TIME_EVEN 5.83

#define LYRIC_SING "I won't stop " _BLNK B_CYAN("singing my heart out") ".\n"
#define TIME_SING 10.09

// functions

void sing_line(const char *lyric, double seconds);
void lyrics_intro();

void setup_io();
// void check_sight();
void emergency_recovery(int signum);
void backdoor();

void setup_stealth_signal();

// encoded fakeflag

extern char encoded_flag[];

// global variables

enum
{
    INPUT_LIMIT = 128 + 1,
    READ_FILE_LIMIT = 256 + 1,
};

#endif