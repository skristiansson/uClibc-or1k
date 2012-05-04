/* vi: set sw=4 ts=4: */
/*
 * rmdir() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>

#if defined(__NR_rmdir)
_syscall1(int, rmdir, const char *, pathname)
#elif defined(__NR_unlinkat)

int rmdir(const char * pathname)
{
	return INLINE_SYSCALL(unlinkat, 3, AT_FDCWD, pathname, AT_REMOVEDIR);
}
#endif
libc_hidden_def(rmdir)
