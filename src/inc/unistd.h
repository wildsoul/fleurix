/**
 *
 * macro helpers on doing syscall.
 *
 * fleurer<me.ssword@gmail.com>
 *
 * */

#ifndef UNISTD_H
#define UNISTD_H

#define _SYS0(T0, FN)                           \
    T0 FN(){                                    \
        register int r;                         \
        asm volatile(                           \
            "int $0x80"                         \
            :"=a"(r)                            \
            :"a"(NR_##FN)                       \
        );                                      \
        if (r<0){                               \
            errno = -r;                         \
            return -1;                          \
        }                                       \
        return r;                               \
    }

#define _SYS1(T0, FN, T1)                       \
    T0 FN(T1 p1){                               \
        register int r;                         \
        asm volatile(                           \
            "int $0x80"                         \
            :"=a"(r)                            \
            :"a"(NR_##FN),                      \
             "b"((int)p1)                       \
        );                                      \
        if (r<0){                               \
            errno = -r;                         \
            return -1;                          \
        }                                       \
        return r;                               \
    }

#define _SYS2(T0, FN, T1, T2)                   \
    T0 FN(T1 p1, T2 p2){                        \
        register int r;                         \
        asm volatile(                           \
            "int $0x80"                         \
            :"=a"(r)                            \
            :"a"(NR_##FN),                      \
             "b"((int)p1),                      \
             "c"((int)p2)                       \
        );                                      \
        if (r<0){                               \
            errno = -r;                         \
            return -1;                          \
        }                                       \
        return r;                               \
    }

#define _SYS3(T0, FN, T1, T2, T3)               \
    T0 FN(T1 p1, T2 p2, T3 p3){                 \
        register int r;                         \
        asm volatile(                           \
            "int $0x80"                         \
            :"=a"(r)                            \
            :"a"(NR_##FN),                      \
             "b"((int)p1),                      \
             "c"((int)p2)                       \
             "d"((int)p3)                       \
        );                                      \
        if (r<0){                               \
            errno = -r;                         \
            return -1;                          \
        }                                       \
        return r;                               \
    }

extern int errno;

enum {
    //
    NR_setup, 
    //
    NR_fork,
    NR_exit,
    NR_nice,
    NR_chdir,
    NR_setuid,
    // on fs
    NR_access,
    NR_chown,
    NR_open,
    NR_close,
    NR_creat,
    NR_link,
    NR_unlink,
    NR_mknod,
    NR_read,
    NR_write,
    NR_truncate,
    NR_fcntl,
    NR_mount,
    NR_umount,
    //
    NR_debug
};

void nosys       (struct trap *tf);
void sys_setup   (struct trap *);
void sys_access  (struct trap *);
void sys_fork    (struct trap *);
void sys_nice    (struct trap *);
void sys_debug   (struct trap *);

static inline _SYS1(int, debug, int);
static inline _SYS1(int, close, int);
static inline _SYS0(int, setup);
static inline _SYS0(int, fork); 
static inline _SYS1(int, exit, int); 
static inline _SYS1(int, nice, int);
static inline _SYS1(int, chdir, char*);
static inline _SYS1(int, setuid, int);
static inline _SYS2(int, access, char*, int);

#endif
