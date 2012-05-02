/* vi: set sw=4 ts=4: */
/*
 * stat() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "xstatconv.h"

#undef stat

int stat(const char *file_name, struct stat *buf)
{
	int result;
#if defined __NR_stat64 || defined __NR_fstatat64
	/* normal stat call has limited values for various stat elements
	 * e.g. uid device major/minor etc.
	 * so we use 64 variant if available
	 * in order to get newer versions of stat elements
	 */
	struct kernel_stat64 kbuf;
#ifdef __NR_stat64
	result = INLINE_SYSCALL(stat64, 2, file_name, &kbuf);
#else
	result = INLINE_SYSCALL(fstatat64, 4, AT_FDCWD, file_name, &kbuf, 0);
#endif
	if (result == 0) {
		__xstat32_conv(&kbuf, buf);
	}
#else
	struct kernel_stat kbuf;

	result = INLINE_SYSCALL(stat, 2, file_name, &kbuf);
	if (result == 0) {
		__xstat_conv(&kbuf, buf);
	}
#endif
	return result;
}
libc_hidden_def(stat)

#if ! defined __NR_stat64 && defined __UCLIBC_HAS_LFS__
strong_alias_untyped(stat,stat64)
libc_hidden_def(stat64)
#endif
