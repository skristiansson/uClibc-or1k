/* vi: set sw=4 ts=4: */
/*
 * chown() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>
#include <bits/wordsize.h>
#include <fcntl.h>


#if (__WORDSIZE == 32 && defined(__NR_chown32)) || __WORDSIZE == 64
# ifdef __NR_chown32
#  undef __NR_chown
#  define __NR_chown __NR_chown32
# endif

_syscall3(int, chown, const char *, path, uid_t, owner, gid_t, group)

#else
int chown(const char *path, uid_t owner, gid_t group)
{
	if (((owner + 1) > (uid_t) ((__kernel_uid_t) - 1U))
		|| ((group + 1) > (gid_t) ((__kernel_gid_t) - 1U))) {
		__set_errno(EINVAL);
		return -1;
	}
# ifdef __NR_chown
	return INLINE_SYSCALL(chown, 3, path, owner, group);
# elif defined __NR_fchownat
	return INLINE_SYSCALL(fchownat, 5, AT_FDCWD, path, owner, group, 0);
# endif
}
#endif

libc_hidden_def(chown)
