/*
 * Based on arm/bits/syscalls.h
 */

#ifndef _BITS_SYSCALLS_H
#define _BITS_SYSCALLS_H
#ifndef _SYSCALL_H
# error "Never use <bits/syscalls.h> directly; include <sys/syscall.h> instead."
#endif

/*
   Some of the sneaky macros in the code were taken from
   glibc-2.3.2/sysdeps/unix/sysv/linux/arm/sysdep.h
*/

#ifdef __ASSEMBLER__

/* TODO: recheck this */

/* Call a given syscall, with arguments loaded.  Unlike the DO_CALL
   macro in glibc, this macro does not load syscall arguments.  */
#undef DO_CALL
#define DO_CALL(syscall_name)			\
    l.lwz r11, =SYS_ify (syscall_name);		\
    l.sys 1					\
    l.nop

#else

#include <errno.h>

#define INTERNAL_SYSCALL_NCS(name, err, nr, args...)			\
  ({ unsigned long __sys_result;					\
     {									\
       register long __sc_ret __asm__ ("r11") = name;			\
       LOAD_ARGS_##nr (args)						\
       __asm__ __volatile__ ("l.sys     1"				\
                             : "=r" (__sc_ret)				\
                             : "r" (__sc_ret) ASM_ARGS_##nr);		\
       __asm__ __volatile__ ("l.nop");					\
       __sys_result = __sc_ret;						\
     }									\
     (long) __sys_result; })

#define LOAD_ARGS_0()
#define ASM_ARGS_0
#define LOAD_ARGS_1(a)				\
  LOAD_ARGS_0 ()				\
  register long __a __asm__ ("r3") = (long)(a);
#define ASM_ARGS_1	ASM_ARGS_0, "r" (__a)
#define LOAD_ARGS_2(a, b)			\
  LOAD_ARGS_1 (a)				\
  register long __b __asm__ ("r4") = (long)(b);
#define ASM_ARGS_2	ASM_ARGS_1, "r" (__b)
#define LOAD_ARGS_3(a, b, c)			\
  LOAD_ARGS_2 (a, b)				\
  register long __c __asm__ ("r5") = (long)(c);
#define ASM_ARGS_3	ASM_ARGS_2, "r" (__c)
#define LOAD_ARGS_4(a, b, c, d)			\
  LOAD_ARGS_3 (a, b, c)				\
  register long __d __asm__ ("r6") = (long)(d);
#define ASM_ARGS_4	ASM_ARGS_3, "r" (__d)
#define LOAD_ARGS_5(a, b, c, d, e)		\
  LOAD_ARGS_4 (a, b, c, d)			\
  register long __e __asm__ ("r7") = (long)(e);
#define ASM_ARGS_5	ASM_ARGS_4, "r" (__e)
#define LOAD_ARGS_6(a, b, c, d, e, f)		\
  LOAD_ARGS_5 (a, b, c, d, e)			\
  register long __f __asm__ ("r8") = (long)(f);
#define ASM_ARGS_6	ASM_ARGS_5, "r" (__f)

#endif /* __ASSEMBLER__ */
#endif /* _BITS_SYSCALLS_H */
