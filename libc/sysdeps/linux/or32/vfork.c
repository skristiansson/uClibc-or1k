#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/errno.h>

#ifndef __NR_vfork
#define __NR_vfork __NR_fork
#endif

pid_t __vfork(void) attribute_hidden;
#define __NR___vfork __NR_vfork
_syscall0(pid_t, __vfork);

libc_hidden_proto(vfork)
weak_alias(__vfork, vfork)
libc_hidden_weak(vfork)
