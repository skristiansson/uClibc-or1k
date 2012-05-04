/* vi: set sw=4 ts=4: */
/*
 * lchown() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>
#include <bits/wordsize.h>
#include <fcntl.h>

#if (__WORDSIZE == 32 && defined(__NR_lchown32)) || __WORDSIZE == 64
# ifdef __NR_lchown32
#  undef __NR_lchown
#  define __NR_lchown __NR_lchown32
# endif

_syscall3(int, lchown, const char *, path, uid_t, owner, gid_t, group)

#else

int lchown(const char *path, uid_t owner, gid_t group)
{
	if (((owner + 1) > (uid_t) ((__kernel_uid_t) - 1U))
		|| ((group + 1) > (gid_t) ((__kernel_gid_t) - 1U))) {
		__set_errno(EINVAL);
		return -1;
	}
# if defined(__NR_lchown)
	return INLINE_SYSCALL(lchown, 3, path, owner, group);
# elif defined(__NR_fchownat)
	return INLINE_SYSCALL(fchownat, 5, AT_FDCWD, path, owner, group, AT_SYMLINK_NOFOLLOW);
# endif
}

#endif
