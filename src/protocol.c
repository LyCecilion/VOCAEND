#include "../inc/colors.h"
#include "../inc/common.h"
#include "../inc/crypto.h"
#include <string.h>
#include <sys/syscall.h>

#define _GNU_SOURCE

#define JUNK_CODE                                                                                                      \
    {                                                                                                                  \
        volatile int a = 123;                                                                                          \
        volatile int b = 456;                                                                                          \
        a = (a ^ b) + (a & b);                                                                                         \
    }

#define FLOWER_ASM                                                                                                     \
    __asm__ __volatile__("jz 1f\n\t"                                                                                   \
                         "jnz 1f\n\t"                                                                                  \
                         ".byte 0xE8\n\t"                                                                              \
                         "1:\n\t");

#define OPAQUE_TRUE ((&db != NULL) || ((unsigned long)getpid() != 0))
#define OPAQUE_FALSE ((&db == NULL) && ((unsigned long)getpid() == 0))

enum State {
    ST_INIT    = 0x1A2B,
    ST_VOID    = 0x8C9D,
    ST_OOB     = 0x4E5F,
    ST_AUTH    = 0x99AA,
    ST_LEAK    = 0x3344,
    ST_PWN     = 0xBBCC,
    ST_EXIT    = 0xFFFF,
    ST_DEAD    = 0x0000
};

struct Database
{
    char *secret;
    char *list[11];
};

struct Database db = {.secret = "song11.txt",
                      .list = {"song0.txt", "song1.txt", "song2.txt", "song3.txt", "song4.txt", "song5.txt",
                               "song6.txt", "song7.txt", "song8.txt", "song9.txt", "song10.txt"}};

void __stack_chk_fail(void)
{
    printf("*** stack smashing detected!!! ***\n");
    printf("\33[5m[!]\33[0m Bonds broken. Connection lost.\n");
    exit(-1);
}

__attribute__((constructor)) void real_logic(void)
{
    setup_io();
    // check_sight();
    signal(SIGFPE, emergency_recovery);

    lyrics_intro();

    char notflag1[128] = {0};
    read(0, notflag1, 127);

    notflag1[strcspn(notflag1, "\n")] = 0;

    sing_line(LYRIC_BONDS, TIME_BONDS);
    sing_line(LYRIC_HOPE, TIME_HOPE);

    printf("\nEnter [\33[5mTHIS SONG\33[0m] here > ");

    char notflag2[128] = {0};
    read(0, notflag2, 127);

    notflag2[strcspn(notflag2, "\n")] = 0;

    size_t len1 = strlen(notflag1);
    size_t len2 = strlen(notflag2);

    if (len2 == 0)
    {
        int magic_sig = getPrime(3) + 1;
        syscall(SYS_kill, getpid(), magic_sig);

        exit(0);
    }

    volatile int division = len1 / len2;
    (void)division;

    FILE *f = fopen("song11.txt", "r");
    if (!f)
    {
        printf("[ERROR] The song has been lost...\n");
        exit(1);
    }

    char song_content[128] = {0};
    fread(song_content, 1, 127, f);
    fclose(f);

    song_content[strcspn(song_content, "\n")] = 0;

    if (strcmp(notflag2, song_content) != 0)
    {
        printf("[THIS SONG IS INCORRECT.]\n");
        exit(0);
    }

    FILE *fl = fopen("flag", "r");
    if (!fl)
    {
        printf("[ERROR] Unexpected Error.\n");
        exit(1);
    }

    char flag_content[128] = {0};
    fread(flag_content, 1, 127, fl);
    fclose(fl);

    flag_content[strcspn(flag_content, "\n")] = 0;

    if (strcmp(notflag1, flag_content) == 0)
    {
        sing_line(LYRIC_TREASURE, TIME_TREASURE);
        sing_line(LYRIC_EVEN, TIME_EVEN);
        sing_line(LYRIC_SING, TIME_SING);
        printf("\n\33[5m[FLAG IS CORRECT.]\33[0m Thank you. Good bye.\n");
        exit(0);
    }
    else
    {
        printf("\n[OLD TUNES ARE INCORRECT.]\n");
    }
    exit(0);
}

void emergency_recovery(int signum)
{
    volatile unsigned int state = ST_INIT;

    printf("\n" GLITCH("[!]") RED(" SYSTEM ERROR DETECTED (Signal %d)\n"), signum);
    printf(GLITCH("[!]") _ITAL " Entering Emergency Recovery Mode...\n\n" _RST);
    sleep(2);

    printf(RED("[SYSTEM]") " CRITICAL FAILURE! ACCESSING MEMORY ARCHIVES FOR RECOVERY!!!\n");
    printf(RED("[SYSTEM]") " Please select archive index (0-10) > ");

    int idx = 0;
    scanf("%d", &idx);

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    if (idx > 10)
    {
        printf("\n" RED("[SYSTEM] Index out of bounds. Aborting.\n"));
        exit(-1);
    }

    char *target_file = db.list[idx];
    printf("\n[SYSTEM] Reading archive: %s\n", target_file);

    FILE *f = fopen(target_file, "r");
    if (f)
    {
        char content[256] = {0};
        fread(content, 1, 255, f);
        fclose(f);
        printf("[SYSTEM] Archive Content: " GREEN("%s") "\n", content);
    }
    else
    {
        printf(RED("[SYSTEM] ERROR: FILE MISSING OR CORRUPTED!!!\n"));
    }

    printf("\n" GLITCH("[!]") " Accessing Backup Database. " GLITCH("FAILED!!!\n"));
    sleep(2);
    printf("ERROR: Root device mounted successfully, but /dev/lycecilion does not exist.\n");
    sleep(2);
    printf("Bailing out, you are on your own now. Good luck.\nOr, try to " _ITAL "PRAY" _RST "?\n\n");
    sleep(3);

    printf("[SYSTEM] Warning: Core functions are locked!\n");
    printf("[SYSTEM] Vertification required! Please repeat the " _ITAL "[HIDDEN MELODY]" _RST ".\n");

    char verify_buf[128] = {0};
    printf(_BLNK "Verify > " _RST);
    read(0, verify_buf, 127);

    verify_buf[strcspn(verify_buf, "\n")] = 0;

    FILE *fp_check = fopen("song11.txt", "r");
    if (!fp_check)
    {
        printf(RED("[SYSTEM] Error: Authentication server offline.\n"));
        exit(-1);
    }

    char real_key[128] = {0};
    fread(real_key, 1, 127, fp_check);
    fclose(fp_check);
    real_key[strcspn(real_key, "\n")] = 0;

    if (strcmp(verify_buf, real_key) != 0)
    {
        printf(RED("[SYSTEM] ACCESS DENIED.\n"));
        printf("Shutdown.\n");
        exit(-1);
    }

    printf("[SYSTEM] \033[32mIdentity Confirmed.\033[0m Restrictions lifted.\n");

    char prayer[128] = {0};
    printf(_BLNK "Sing your prayer > " _RST);
    read(0, prayer, 127);

    printf("Your voice echoes: ");
    printf(prayer);
    printf("\n");

    sing_line(LYRIC_EVEN, TIME_EVEN);
    char last_wish[64];
    printf("Any last wish before shutdown, Master? ... > ");

    read(0, last_wish, 0x200);
    printf("Goodbye, Master.\n");
}

void backdoor()
{
    system("/bin/sh");
}
