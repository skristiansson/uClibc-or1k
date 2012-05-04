/* vi: set sw=4 ts=4: */
/*
 * symlink() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#if defined __USE_BSD || defined __USE_UNIX98 || defined __USE_XOPEN2K
#include <unistd.h>
#include <fcntl.h>
# ifdef __NR_symlink
_syscall2(int, symlink, const char *, oldpath, const char *, newpath)
# elif defined __NR_symlinkat
int symlink(const char *oldpath, const char *newpath)
{
	return INLINE_SYSCALL(symlinkat, 3, oldpath, AT_FDCWD, newpath);
}
# endif
#endif
