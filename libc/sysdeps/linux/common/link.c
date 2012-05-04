/* vi: set sw=4 ts=4: */
/*
 * link() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
#if defined(__NR_link)
_syscall2(int, link, const char *, oldpath, const char *, newpath)
#elif defined(__NR_linkat)
int link(const char * oldpath, const char * newpath)
{
	return INLINE_SYSCALL(linkat, 5, AT_FDCWD, oldpath, AT_FDCWD, newpath, 0);
}
#endif
