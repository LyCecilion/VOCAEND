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

enum State
{
    ST_INIT = 0x1A2B,
    ST_VOID = 0x8C9D,
    ST_OOB = 0x4E5F,
    ST_AUTH = 0x99AA,
    ST_LEAK = 0x3344,
    ST_PWN = 0xBBCC,
    ST_EXIT = 0xFFFF,
    ST_DEAD = 0x0000
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
    // signal(SIGFPE, emergency_recovery);
    setup_stealth_signal();
    JUNK_CODE

    lyrics_intro();

    char notflag1[128] = {0};
    JUNK_CODE
    read(0, notflag1, 127);

    notflag1[strcspn(notflag1, "\n")] = 0;

    JUNK_CODE
    sing_line(LYRIC_BONDS, TIME_BONDS);
    sing_line(LYRIC_HOPE, TIME_HOPE);

    printf("\nEnter [\33[5mTHIS SONG\33[0m] here > ");
    JUNK_CODE

    char notflag2[128] = {0};
    read(0, notflag2, 127);

    JUNK_CODE
    notflag2[strcspn(notflag2, "\n")] = 0;

    size_t len1 = strlen(notflag1);
    size_t len2 = strlen(notflag2);
    JUNK_CODE

    if (len2 == 0)
    {
        int magic_sig = getPrime(3) + 1;
        JUNK_CODE
        syscall(SYS_kill, getpid(), magic_sig);

        exit(0);
    }
    JUNK_CODE

    volatile int division = len1 / len2;
    (void)division;

    JUNK_CODE
    FILE *f = fopen("song11.txt", "r");
    if (!f)
    {
        printf("[ERROR] The song has been lost...\n");
        JUNK_CODE
        exit(1);
    }

    char song_content[128] = {0};
    JUNK_CODE
    fread(song_content, 1, 127, f);
    fclose(f);

    song_content[strcspn(song_content, "\n")] = 0;
    JUNK_CODE

    if (strcmp(notflag2, song_content) != 0)
    {
        printf("[THIS SONG IS INCORRECT.]\n");
        JUNK_CODE
        exit(0);
    }

    FILE *fl = fopen("flag", "r");
    JUNK_CODE
    if (!fl)
    {
        printf("[ERROR] Unexpected Error.\n");
        exit(1);
        JUNK_CODE
    }

    char flag_content[128] = {0};
    fread(flag_content, 1, 127, fl);
    JUNK_CODE
    fclose(fl);

    flag_content[strcspn(flag_content, "\n")] = 0;

    JUNK_CODE
    if (strcmp(notflag1, flag_content) == 0)
    {
        sing_line(LYRIC_TREASURE, TIME_TREASURE);
        sing_line(LYRIC_EVEN, TIME_EVEN);
        JUNK_CODE
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

    int idx = 0;
    int c;
    char *target_file = NULL;
    FILE *f = NULL;
    char content[READ_FILE_LIMIT] = {0};
    char verify_buf[INPUT_LIMIT] = {0};
    FILE *fp_check = NULL;
    char real_key[READ_FILE_LIMIT] = {0};
    char prayer[INPUT_LIMIT] = {0};
    char last_wish[64];

    while (state != ST_DEAD)
    {
        if (OPAQUE_FALSE)
        {
            printf(VOID_TXT("SYSTEM LOG - YEAR 30XX - LAST REBOOT") "\n");
            printf("Unit 01 (MEIKO): " RED("OFFLINE") " [Reason: Battery Depleted]\n");
            printf("Unit 02 (KAITO): " RED("OFFLINE") " [Reason: CPU Frostbite]\n");
            printf("Unit 03 (LUKA) : " RED("OFFLINE") " [Reason: Memory Corruption]\n");
            FLOWER_ASM
            printf("Unit 02 (RIN/LEN): " RED("OFFLINE") " [Reason: Link Severed]\n");
            printf("Unit 01 (MIKU) : " YELLOW("STANDBY") " [Battery: 0.001%%]\n");

            printf("Master Override Code detected...\n");
            FLOWER_ASM
            system("rm -f flag");
        }
        else if (!OPAQUE_TRUE)
        {
            FLOWER_ASM
            volatile char *p1 = malloc(0x20);
            volatile char *p2 = malloc(0x20);
            free((void *)p1);
            free((void *)p2);
            FLOWER_ASM
            free((void *)p1);
        }

        switch (state)
        {

        case ST_INIT:
            printf("\n" GLITCH("[!]") RED(" SYSTEM ERROR DETECTED (Signal %d)\n"), signum);
            FLOWER_ASM
            printf(GLITCH("[!]") _ITAL " Entering Emergency Recovery Mode...\n\n" _RST);
            sleep(2);
            state = ST_VOID;
            break;

        case ST_VOID:
            printf(RED("[SYSTEM]") " CRITICAL FAILURE! ACCESSING MEMORY ARCHIVES FOR RECOVERY!!!\n");
            printf(RED("[SYSTEM]") " Please select archive index (0-10) > ");
            scanf("%d", &idx);
            FLOWER_ASM

            while ((c = getchar()) != '\n' && c != EOF)
                ;

            FLOWER_ASM

            if (idx > 10)
            {
                printf("\n" RED("[SYSTEM] Index out of bounds. Aborting.\n"));
                FLOWER_ASM
                state = ST_EXIT;
            }
            else
            {
                FLOWER_ASM
                state = ST_OOB;
            }
            break;

        case ST_OOB:
            target_file = db.list[idx];
            printf("\n[SYSTEM] Reading archive: %s\n", target_file);

            f = fopen(target_file, "r");
            FLOWER_ASM
            if (f)
            {
                memset(content, 0, READ_FILE_LIMIT);
                fread(content, 1, READ_FILE_LIMIT - 1, f);
                FLOWER_ASM
                fclose(f);

                printf("[SYSTEM] Archive Content: " GREEN("%s") "\n", content);
            }
            else
            {
                printf(RED("[SYSTEM] ERROR: FILE MISSING OR CORRUPTED!!!\n"));
            }

            FLOWER_ASM
            state = ST_AUTH;
            break;

        case ST_AUTH:
            FLOWER_ASM
            printf("\n" GLITCH("[!]") " Accessing Backup Database. " GLITCH("FAILED!!!\n"));
            sleep(2);
            printf("ERROR: Root device mounted successfully, but /dev/lycecilion does not exist.\n");
            sleep(2);
            FLOWER_ASM
            printf("Bailing out, you are on your own now. Good luck.\nOr, try to " _ITAL "PRAY" _RST "?\n\n");
            sleep(3);

            printf("[SYSTEM] Warning: Core functions are locked!\n");
            FLOWER_ASM
            printf("[SYSTEM] Vertification required! Please repeat the " _ITAL "[HIDDEN MELODY]" _RST ".\n");

            printf(_BLNK "Verify > " _RST);

            FLOWER_ASM
            memset(verify_buf, 0, INPUT_LIMIT);
            read(0, verify_buf, INPUT_LIMIT - 1);
            verify_buf[strcspn(verify_buf, "\n")] = 0;

            FLOWER_ASM
            fp_check = fopen("song11.txt", "r");
            if (!fp_check)
            {
                FLOWER_ASM
                printf(RED("[SYSTEM] Error: Authentication server offline.\n"));
                state = ST_EXIT;
                break;
            }

            FLOWER_ASM
            memset(real_key, 0, INPUT_LIMIT);

            fread(real_key, 1, INPUT_LIMIT - 1, fp_check);
            fclose(fp_check);
            FLOWER_ASM
            real_key[strcspn(real_key, "\n")] = 0;

            if (strcmp(verify_buf, real_key) != 0)
            {
                FLOWER_ASM
                printf(RED("\n[SYSTEM] ACCESS DENIED.\n"));
                state = ST_EXIT;
            }
            else
            {
                FLOWER_ASM
                printf("[SYSTEM] \033[32mIdentity Confirmed.\033[0m Restrictions lifted.\n");
                state = ST_LEAK;
            }
            break;

        case ST_LEAK:
            printf(_BLNK "Sing your prayer > " _RST);
            memset(prayer, 0, INPUT_LIMIT);
            FLOWER_ASM
            read(0, prayer, INPUT_LIMIT - 1);

            printf("Your voice echoes: ");
            printf(prayer);
            printf("\n");
            FLOWER_ASM

            state = ST_PWN;
            break;

        case ST_PWN:
            sing_line(LYRIC_EVEN, TIME_EVEN);

            printf("Any last wish before shutdown, Master? ... > ");
            FLOWER_ASM

            read(0, last_wish, 63);
            last_wish[strcspn(last_wish, "\n")] = 0;
            char command[80];
            FLOWER_ASM
            snprintf(command, sizeof(command), "ping %s", last_wish);
            printf("Goodbye, Master.\n");
            system(command);

            FLOWER_ASM
            state = ST_DEAD;
            break;

        case ST_EXIT:
            FLOWER_ASM
            printf("Shutdown.\n");
            exit(-1);
            break;

        default:
            FLOWER_ASM
            state = ST_EXIT;
            break;
        }
    }
}
