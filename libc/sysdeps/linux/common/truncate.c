/* vi: set sw=4 ts=4: */
/*
 * truncate() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>


#ifdef __NR_truncate
_syscall2(int, truncate, const char *, path, __off_t, length)
#elif defined(__NR_truncate64)
int truncate(const char *path, __off_t length)
{
	return truncate64(path, length);
}
#endif
libc_hidden_def(truncate)
