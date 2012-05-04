/* vi: set sw=4 ts=4: */
/*
 * mkdir() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <sys/stat.h>
#include <fcntl.h>


int mkdir(const char *pathname, mode_t mode)
{
#ifdef __NR_mkdir
	return INLINE_SYSCALL(mkdir, 2, pathname, (__kernel_mode_t)mode);
#else
	return INLINE_SYSCALL(mkdirat, 3, AT_FDCWD, pathname, (__kernel_mode_t)mode);
#endif
}
libc_hidden_def(mkdir)
