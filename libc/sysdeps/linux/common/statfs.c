/* vi: set sw=4 ts=4: */
/*
 * statfs() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <string.h>
#include <sys/param.h>
#include <sys/vfs.h>

#if defined __NR_statfs
extern __typeof(statfs) __libc_statfs attribute_hidden;
#define __NR___libc_statfs __NR_statfs
_syscall2(int, __libc_statfs, const char *, path, struct statfs *, buf)
#elif defined __NR_statfs64
int __libc_statfs(const char *path, struct statfs *buf)
{
	struct statfs64 st;
	int err;

	err = INLINE_SYSCALL(statfs64, 3, path, sizeof(st), &st);
	if (err)
		return err;

	buf->f_type = st.f_type;
	buf->f_bsize = st.f_bsize;
	buf->f_blocks = st.f_blocks;
	buf->f_bfree = st.f_bfree;
	buf->f_bavail = st.f_bavail;
	buf->f_files = st.f_files;
	buf->f_ffree = st.f_ffree;
	buf->f_fsid = st.f_fsid;
	buf->f_namelen = st.f_namelen;
	buf->f_frsize = st.f_frsize;

	return 0;
}
#endif

#if defined __UCLIBC_LINUX_SPECIFIC__ || defined __UCLIBC_HAS_THREADS_NATIVE__
/* statfs is used by NPTL, so it must exported in case */
weak_alias(__libc_statfs,statfs)
#endif
