/* vi: set sw=4 ts=4: */
/*
 * __syscall_fcntl() for uClibc
 *
 * Copyright (C) 2006 Steven J. Hill <sjhill@realitydiluted.com>
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <stdarg.h>
#ifdef __UCLIBC_HAS_THREADS_NATIVE__
#include <sysdep-cancel.h>	/* Must come before <fcntl.h>.  */
#endif
#include <fcntl.h>
#include <bits/wordsize.h>

/*
 * The fcntl64 syscall only exists on 32-Bit systems. It is identical to
 * the fcntl syscall except for additial commands providing 32-bit systems
 * with file locking operations using 64-bit offsets.
 */
# if __WORDSIZE == 32 && defined __NR_fcntl64
#define INLINE_SYSCALL_FCNTL(a,b,c) INLINE_SYSCALL(fcntl64, 3, (a), (b), (c))
#else
#define INLINE_SYSCALL_FCNTL(a,b,c) INLINE_SYSCALL(fcntl, 3, (a), (b), (c))
#endif

extern __typeof(fcntl) __libc_fcntl;
libc_hidden_proto(__libc_fcntl)

int __fcntl_nocancel (int fd, int cmd, ...)
{
	va_list ap;
	void *arg;

	va_start (ap, cmd);
	arg = va_arg (ap, void *);
	va_end (ap);

# if __WORDSIZE == 32 && !(defined __UCLIBC_HAS_LFS__ && defined __NR_fcntl64)
	if (cmd == F_GETLK64 || cmd == F_SETLK64 || cmd == F_SETLKW64) {
		__set_errno(ENOSYS);
		return -1;
	}
# endif
	return INLINE_SYSCALL_FCNTL (fd, cmd, arg);
}
libc_hidden_def(__fcntl_nocancel)

#ifdef __UCLIBC_HAS_THREADS_NATIVE__
int __libc_fcntl (int fd, int cmd, ...)
{
	va_list ap;
	void *arg;

	va_start (ap, cmd);
	arg = va_arg (ap, void *);
	va_end (ap);

#if __WORDSIZE == 32 && !(defined __UCLIBC_HAS_LFS__ && defined __NR_fcntl64)
	if (cmd == F_GETLK64 || cmd == F_SETLK64 || cmd == F_SETLKW64) {
		__set_errno(ENOSYS);
		return -1;
	}
#endif

	if (SINGLE_THREAD_P || (cmd != F_SETLKW && cmd != F_SETLKW64))
		return INLINE_SYSCALL_FCNTL (fd, cmd, arg);
	int oldtype = LIBC_CANCEL_ASYNC ();

	int result = INLINE_SYSCALL_FCNTL (fd, cmd, arg);

	LIBC_CANCEL_RESET (oldtype);

	return result;
}
#else
strong_alias(__fcntl_nocancel,__libc_fcntl)
#endif
libc_hidden_def(__libc_fcntl)

libc_hidden_proto(fcntl)
weak_alias(__libc_fcntl,fcntl)
libc_hidden_weak(fcntl)
