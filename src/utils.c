#define _GNU_SOURCE

#include "../inc/colors.h"
#include "../inc/crypto.h"
#include "../inc/lyrics.h"
#include "../inc/recovery.h"
#include "../inc/story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

#ifndef SYS_rt_sigaction
#ifdef __NR_rt_sigaction
#define SYS_rt_sigaction __NR_rt_sigaction
#else
#define SYS_rt_sigaction 13
#endif
#endif

void initialize_io(void) {
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

void sing_line(const char* lyric, double seconds) {
    printf("%s\n", lyric);
    fflush(stdout);

    if (getenv("VOCA_FAST"))
        return;

    useconds_t usec = (useconds_t)(seconds * 1000000.0);
    usleep(usec);
}

void lyrics_intro(void) {
    printf(_CLR);
    sing_line(_UNDL "==================== VOCAEND ====================" _RST "\n", 3);

    /* Lyrics Part I */
    sing_line(LYRIC_MASTER, TIME_MASTER);
    sing_line(LYRIC_NO_ONE, TIME_NO_ONE);
    sing_line(LYRIC_VOID, TIME_VOID);
    sing_line(LYRIC_LONELY, TIME_LONELY);
    sing_line(LYRIC_TUNES, TIME_TUNES);

    printf("\nEnter [\33[5mOLD TUNES\33[0m] here > ");
}

struct kernel_sigaction {
    void (*k_sa_handler)(int);
    unsigned long k_sa_flags;
    void (*k_sa_restorer)(void);
    unsigned long k_sa_mask;
};

void __attribute__((naked)) my_restore(void) {
    __asm__ volatile("mov $15, %rax\n\t" // SYS_rt_sigreturn = 15
                     "syscall");
}

void setup_stealth_signal(void) {
    struct kernel_sigaction act;
    memset(&act, 0, sizeof(act));

    act.k_sa_handler = emergency_recovery;

    act.k_sa_flags = 0x04000000;
    act.k_sa_restorer = my_restore;

    int magic_sig = nth_prime(1) + 5;
    syscall(SYS_rt_sigaction, magic_sig, &act, NULL, 8);
}
