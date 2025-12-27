#include "../inc/common.h"
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "../inc/crypto.h"

#define _GNU_SOURCE

#ifndef SYS_rt_sigaction
    #ifdef __NR_rt_sigaction
        #define SYS_rt_sigaction __NR_rt_sigaction
    #else
        #define SYS_rt_sigaction 13 
    #endif
#endif

void setup_io()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    sleep(1);
    printf(B_CYAN("[BATTERY]") " Level: " B_RED("3%%") " (Critical)\n");
    printf(B_CYAN("[TEMP]") " Ambient: " B_BLUE("-120°C") "\n");
    sleep(2);
    printf("遂に始まりました！！、");
    sleep(2);
    printf("ボカコレです！！。");
    sleep(3);
}

void check_sight()
{
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0)
    {
        printf("\33[8mMaster... why are you staring at me?\33[0m");
        exit(0);
    }
}

void sing_line(const char *lyric, double seconds)
{
    printf("%s\n", lyric);
    fflush(stdout);

    if (getenv("VOCA_FAST"))
    {
        return;
    }

    useconds_t usec = (useconds_t)(seconds * 1000000.0);
    usleep(usec);
}

void lyrics_intro()
{
    printf("\033[2J\033[H");
    sing_line("\33[4m==================== VOCAEND ====================\33[0m\n", 3);

    /* Lyrics Part I */
    sing_line(LYRIC_MASTER, TIME_MASTER);
    sing_line(LYRIC_NO_ONE, TIME_NO_ONE);
    sing_line(LYRIC_VOID, TIME_VOID);
    sing_line(LYRIC_LONELY, TIME_LONELY);
    sing_line(LYRIC_TUNES, TIME_TUNES);

    printf("\nEnter [\33[5mOLD TUNES\33[0m] here > ");
}

void setup_stealth_signal()
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = emergency_recovery;
    act.sa_flags = getPrime(0) - 2;

    int magic_sig = getPrime(4) - 3;
    syscall(SYS_rt_sigaction, magic_sig, &act, NULL, 8);
}