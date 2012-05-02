/* vi: set sw=4 ts=4: */
/*
 * pipe() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>


#if defined(__NR_pipe)
_syscall1(int, pipe, int *, filedes)
#elif defined(__NR_pipe2)
int pipe(int filedes[2])
{
	return INLINE_SYSCALL(pipe2, 2, filedes, 0);
}
#endif
libc_hidden_def(pipe)
