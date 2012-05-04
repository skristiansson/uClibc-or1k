/* vi: set sw=4 ts=4: */
/*
 * lstat64() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>

#if defined __UCLIBC_HAS_LFS__ && (defined __NR_lstat64 || defined __NR_fstatat64)
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "xstatconv.h"


int lstat64(const char *file_name, struct stat64 *buf)
{
	int result;
	struct kernel_stat64 kbuf;

# if defined __NR_lstat64
	result = INLINE_SYSCALL(lstat64, 2, file_name, &kbuf);
# elif defined __NR_fstatat64
	result = INLINE_SYSCALL(fstatat64, 4, AT_FDCWD, file_name, &kbuf, AT_SYMLINK_NOFOLLOW);
# endif
	if (result == 0) {
		__xstat64_conv(&kbuf, buf);
	}
	return result;
}
libc_hidden_def(lstat64)

#endif
