#define PROT_READ       0x1             /* Page can be read.  */
#define PROT_WRITE      0x2             /* Page can be written.  */
#define MAP_PRIVATE     0x02            /* Changes are private.  */
#define MAP_ANONYMOUS 0x20            /* Don't use a file.  */
#define MAP_POPULATE       0x8000
#define MAP_FIXED   0x10
#define MAP_GROWSDOWN      0x0100
#define O_RDWR 2
#define O_NOCTTY 00000400
#define O_RDONLY 00000000


int read(int fd, char* buf, int len) {
    __asm__("mov rax, 0");
    __asm__("syscall");
}

int write(int fd, char* buf, int len) {
    __asm__("mov rax, 1");
    __asm__("syscall");
}

int open(char* filename, int flags) {
    __asm__("mov rax, 2");
    __asm__("syscall");
}

int close(int fd) {
    __asm__("mov rax, 3");
    __asm__("syscall");
}

void exit(int status) {
    __asm__("mov rax, 60");
    __asm__("syscall");

}

int ioctl(unsigned int fd, unsigned int cmd, unsigned long* arg) {
    __asm__("mov rax, 16");
    __asm__("syscall");
}

void *mmap(void *addr, unsigned long length, int prot, int flags, int fd, unsigned long offset) {
    __asm__("mov r10, rcx");
    __asm__("mov rax, 9");
    __asm__("syscall");
}


int strlen(char* string) {
    int len = 0;
    for (; *(string++) != '\x00'; len++) {}
    return len;
}

void puts(char* string) {
    int len = strlen(string);
    write(1, string, len);
}

void memset(char* a, char b, int len) {
    int i;
    for (i=0; i<len; i++) {
        a[i] = b;
    }
}




int ptmx_fds[0x100];

void open_ptmx(void) {
    for (int i=0; i<0x100; i++)
        ptmx_fds[i] = open("/dev/ptmx", O_NOCTTY|O_RDWR);
}

void close_ptmx(void) {
    for (int i=0; i<0x100; i++)
        close(ptmx_fds[i]);
}

void _start(void) {


    return;
}
