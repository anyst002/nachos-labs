# NOTE: this is a GNU Makefile.  You must use "gmake" rather than "make".
#
# Makefile for the threads assignment.  The threads assignment must
#  be done first!
#
# Copyright (c) 1992 The Regents of the University of California.
# All rights reserved.  See copyright.h for copyright notice and limitation
# of liability and disclaimer of warranty provisions.

DEFINES = -DTHREADS
INCPATH = -I../threads -I../machine
HFILES = $(THREAD_H)
CFILES = $(THREAD_C)
C_OFILES = $(THREAD_O)

include ../Makefile.common
include ../Makefile.dep
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
main.o: ../threads/main.cc ../threads/copyright.h ../threads/utility.h \
  ../threads/bool.h ../machine/sysdep.h /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/system.h ../threads/thread.h \
  ../threads/scheduler.h ../threads/list.h ../machine/interrupt.h \
  ../machine/stats.h ../machine/timer.h
list.o: ../threads/list.cc ../threads/copyright.h ../threads/list.h \
  ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h
scheduler.o: ../threads/scheduler.cc ../threads/copyright.h \
  ../threads/scheduler.h ../threads/list.h ../threads/utility.h \
  ../threads/bool.h ../machine/sysdep.h /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/thread.h ../threads/system.h \
  ../machine/interrupt.h ../machine/stats.h ../machine/timer.h
synch.o: ../threads/synch.cc ../threads/copyright.h ../threads/synch.h \
  ../threads/thread.h ../threads/utility.h ../threads/bool.h \
  ../machine/sysdep.h /usr/include/stdio.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/list.h ../threads/system.h \
  ../threads/scheduler.h ../machine/interrupt.h ../machine/stats.h \
  ../machine/timer.h
synchlist.o: ../threads/synchlist.cc ../threads/copyright.h \
  ../threads/synchlist.h ../threads/list.h ../threads/utility.h \
  ../threads/bool.h ../machine/sysdep.h /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/synch.h ../threads/thread.h
system.o: ../threads/system.cc ../threads/copyright.h ../threads/system.h \
  ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/thread.h ../threads/scheduler.h \
  ../threads/list.h ../machine/interrupt.h ../machine/stats.h \
  ../machine/timer.h
thread.o: ../threads/thread.cc ../threads/copyright.h ../threads/thread.h \
  ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/switch.h ../threads/synch.h \
  ../threads/list.h ../threads/system.h ../threads/scheduler.h \
  ../machine/interrupt.h ../machine/stats.h ../machine/timer.h
utility.o: ../threads/utility.cc ../threads/copyright.h \
  ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h
threadtest.o: ../threads/threadtest.cc ../threads/copyright.h \
  ../threads/system.h ../threads/utility.h ../threads/bool.h \
  ../machine/sysdep.h /usr/include/stdio.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/thread.h ../threads/scheduler.h \
  ../threads/list.h ../machine/interrupt.h ../machine/stats.h \
  ../machine/timer.h
interrupt.o: ../machine/interrupt.cc ../threads/copyright.h \
  ../machine/interrupt.h ../threads/list.h ../threads/utility.h \
  ../threads/bool.h ../machine/sysdep.h /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/system.h ../threads/thread.h \
  ../threads/scheduler.h ../machine/stats.h ../machine/timer.h
sysdep.o: ../machine/sysdep.cc ../threads/copyright.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/stdlib.h \
  /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
  /usr/include/endian.h /usr/include/bits/endian.h /usr/include/xlocale.h \
  /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/bits/sigset.h \
  /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/alloca.h /usr/include/string.h /usr/include/signal.h \
  /usr/include/bits/signum.h /usr/include/bits/siginfo.h \
  /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h \
  /usr/include/asm/sigcontext.h /usr/include/bits/sigstack.h \
  /usr/include/sys/ucontext.h /usr/include/bits/sigthread.h \
  /usr/include/sys/time.h /usr/include/sys/socket.h \
  /usr/include/sys/uio.h /usr/include/bits/uio.h \
  /usr/include/bits/socket.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/bits/xopen_lim.h \
  /usr/include/bits/sockaddr.h /usr/include/asm/socket.h \
  /usr/include/asm/sockios.h /usr/include/sys/file.h /usr/include/fcntl.h \
  /usr/include/bits/fcntl.h /usr/include/sys/stat.h \
  /usr/include/bits/stat.h /usr/include/sys/un.h /usr/include/sys/mman.h \
  /usr/include/bits/mman.h /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/environments.h \
  /usr/include/bits/confname.h /usr/include/getopt.h \
  ../machine/interrupt.h ../threads/list.h ../threads/utility.h \
  ../threads/bool.h ../machine/sysdep.h ../threads/system.h \
  ../threads/thread.h ../threads/scheduler.h ../machine/stats.h \
  ../machine/timer.h
stats.o: ../machine/stats.cc ../threads/copyright.h ../threads/utility.h \
  ../threads/bool.h ../machine/sysdep.h /usr/include/stdio.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../machine/stats.h
timer.o: ../machine/timer.cc ../threads/copyright.h ../machine/timer.h \
  ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
  /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/3.3.3/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/wordsize.h \
  /usr/include/bits/typesizes.h /usr/include/libio.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h ../threads/stdarg.h /usr/include/bits/stdio_lim.h \
  /usr/include/bits/sys_errlist.h /usr/include/string.h \
  /usr/include/xlocale.h ../threads/system.h ../threads/thread.h \
  ../threads/scheduler.h ../threads/list.h ../machine/interrupt.h \
  ../machine/stats.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
