/* vi: set sw=4 ts=4: */
/*
 * utimes() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <utime.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fcntl.h>

#ifdef __NR_utimes
_syscall2(int, utimes, const char *, file, const struct timeval *, tvp)
#elif defined __NR_utimensat

int utimes(const char *file, const struct timeval tvp[2])
{
	struct timespec ts[2];

	if (tvp) {
		if (tvp[0].tv_usec >= 1000000 || tvp[0].tv_usec < 0 ||
		    tvp[1].tv_usec >= 1000000 || tvp[1].tv_usec < 0)
			return -EINVAL;

		ts[0].tv_sec = tvp[0].tv_sec;
		ts[0].tv_nsec = 1000 * tvp[0].tv_usec;
		ts[1].tv_sec = tvp[1].tv_sec;
		ts[1].tv_nsec = 1000 * tvp[1].tv_usec;

		return INLINE_SYSCALL(utimensat, 4, AT_FDCWD, file, ts, 0);
	} else {
		return INLINE_SYSCALL(utimensat, 4, AT_FDCWD, file, NULL, 0);
	}
}
#else
#include <stdlib.h>


int utimes(const char *file, const struct timeval tvp[2])
{
	struct utimbuf buf, *times;

	if (tvp) {
		times = &buf;
		times->actime = tvp[0].tv_sec;
		times->modtime = tvp[1].tv_sec;
	} else {
		times = NULL;
	}
	return utime(file, times);
}
#endif
libc_hidden_def(utimes)
