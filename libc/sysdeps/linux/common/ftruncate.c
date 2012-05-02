/* vi: set sw=4 ts=4: */
/*
 * ftruncate() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>


#ifdef __NR_ftruncate
_syscall2(int, ftruncate, int, fd, __off_t, length)
#elif defined __NR_truncate64
int ftruncate(int fd, __off_t length)
{
	return ftruncate64(fd, length);
}
#endif
libc_hidden_def(ftruncate)
