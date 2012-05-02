/* vi: set sw=4 ts=4: */
/*
 * dup2() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>


#ifdef __NR_dup2
_syscall2(int, dup2, int, oldfd, int, newfd)
#elif defined __NR_dup3
#include <fcntl.h>

int
dup2 (int fd, int fd2)
{
	/* For the degenerate case, check if the fd is valid (by trying to
	   get the file status flags) and return it, or else return EBADF.  */
	if (fd == fd2) {
		int err;
#ifdef __NR_fcntl64
		err = INLINE_SYSCALL(fcntl64, 3, fd, F_GETFL, 0);
#else
		err = INLINE_SYSCALL(fcntl, 3, fd, F_GETFL, 0);
#endif
		return err < 0 ? -1 : fd;
	}

	return INLINE_SYSCALL(dup3, 3, fd, fd2, 0);
}
#endif
libc_hidden_def(dup2)
