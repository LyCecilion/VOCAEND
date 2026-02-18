#include "../inc/common.h"
#include "../inc/crypto.h"
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <unistd.h>


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

/*

int check_sight_safe()
{
    int pipefd[2];
    if (pipe(pipefd) < 0)
        return 0; // 管道失败就算了，放行

    pid_t pid = fork();

    if (pid < 0)
    {
        return 0; // fork失败，放行
    }

    if (pid == 0)
    {
        // === 子进程逻辑 ===
        close(pipefd[0]); // 关闭读端

        // 尝试依附父进程 (getppid)
        // 如果父进程正在被 GDB 调试，这里会返回 -1
        long ret = ptrace(PTRACE_ATTACH, getppid(), NULL, NULL);

        char result = (ret < 0) ? 1 : 0; // 1=被调试, 0=安全

        // 如果 attach 成功了，记得赶紧 detach，否则父进程会卡住
        if (ret == 0)
        {
            waitpid(getppid(), NULL, 0); // 等待父进程停止（Attach副作用）
            ptrace(PTRACE_DETACH, getppid(), NULL, NULL);
        }

        // 把结果发给父进程
        write(pipefd[1], &result, 1);
        close(pipefd[1]);
        exit(0);
    }
    else
    {
        // === 父进程逻辑 ===
        close(pipefd[1]); // 关闭写端

        char result = 0;
        // 等待子进程的侦查报告
        read(pipefd[0], &result, 1);
        close(pipefd[0]);

        // 回收子进程，防止僵尸
        waitpid(pid, NULL, 0);

        return result; // 1 或 0
    }
}

void check_sight()
{
    if (check_sight_safe())
    {
        printf("\33[8mMaster... why are you staring at me?\33[0m");
        exit(0);
    }
}

*/

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

/*

void setup_stealth_signal()
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = emergency_recovery;
    act.sa_flags = getPrime(0) - 2;

    int magic_sig = getPrime(4) - 3;
    syscall(SYS_rt_sigaction, magic_sig, &act, NULL, 8);
}

*/

struct kernel_sigaction
{
    void (*k_sa_handler)(int);
    unsigned long k_sa_flags;
    void (*k_sa_restorer)(void);
    unsigned long k_sa_mask;
};

void __attribute__((naked)) my_restore(void)
{
    __asm__ volatile("mov $15, %rax\n\t" // SYS_rt_sigreturn = 15
                     "syscall");
}

void setup_stealth_signal()
{
    struct kernel_sigaction act;
    memset(&act, 0, sizeof(act));

    act.k_sa_handler = emergency_recovery;

    act.k_sa_flags = 0x04000000;
    act.k_sa_restorer = my_restore;

    int magic_sig = getPrime(1) + 5;
    syscall(SYS_rt_sigaction, magic_sig, &act, NULL, 8);
}
