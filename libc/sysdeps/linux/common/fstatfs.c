/* vi: set sw=4 ts=4: */
/*
 * fstatfs() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <sys/vfs.h>

#ifndef __USE_FILE_OFFSET64
extern int fstatfs (int __fildes, struct statfs *__buf)
     __THROW __nonnull ((2));
#else
# ifdef __REDIRECT_NTH
extern int __REDIRECT_NTH (fstatfs, (int __fildes, struct statfs *__buf),
	fstatfs64) __nonnull ((2));
# else
#  define fstatfs fstatfs64
# endif
#endif

#ifdef __NR_fstatfs
extern __typeof(fstatfs) __libc_fstatfs attribute_hidden;
#define __NR___libc_fstatfs __NR_fstatfs
_syscall2(int, __libc_fstatfs, int, fd, struct statfs *, buf)
#elif defined __NR_fstatfs64
int __libc_fstatfs(int fd, struct statfs *buf)
{
	struct statfs64 st;
	int err;

	err = INLINE_SYSCALL(fstatfs64, 3, fd, sizeof(st), &st);
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

#if defined __UCLIBC_LINUX_SPECIFIC__
weak_alias(__libc_fstatfs,fstatfs)
#endif
