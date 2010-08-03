/* vi: set sw=4 ts=4: */
/* syscall for or32/uClibc
 *
 * Based on arm/uClibc version.
 *
 * Copyright (C) 2002 by Erik Andersen <andersen@uclibc.org>
 * Copyright (C) 2010 by Jonas Bonn <jonas@southpole.se>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <features.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/syscall.h>

long syscall(long sysnum, long a, long b, long c, long d, long e, long f)
{
	register long __sc_ret __asm__ ("r11") = (long)(sysnum);
	register long __a __asm__ ("r3") = (long)(a);
	register long __b __asm__ ("r4") = (long)(b);
	register long __c __asm__ ("r5") = (long)(c);
	register long __d __asm__ ("r6") = (long)(d);
	register long __e __asm__ ("r7") = (long)(e);
	register long __f __asm__ ("r8") = (long)(f);
	__asm__ __volatile__ (
			"l.sys     1"
			: "=r" (__sc_ret)
			: "r" (__sc_ret), "r" (__a), "r" (__b), "r" (__c), "r" (__d), "r" (__e), "r" (__f));
	__asm__ __volatile__ ("l.nop");
	if (__sc_ret > (unsigned long) -4095) {
		errno = -__sc_ret;
		__sc_ret = -1;
	}
	return (long) __sc_ret;
}
