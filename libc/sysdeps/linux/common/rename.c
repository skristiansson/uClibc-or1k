/* vi: set sw=4 ts=4: */
/*
 * rename() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#include <sys/param.h>
#include <stdio.h>
#include <fcntl.h>

int rename(const char * oldpath, const char * newpath)
{
# ifdef __NR_rename
	return INLINE_SYSCALL(rename, 2, oldpath, newpath);
# else
	return INLINE_SYSCALL(renameat, 4, AT_FDCWD, oldpath, AT_FDCWD, newpath);
# endif
}

