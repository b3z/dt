/*
    dtach - A simple program that emulates the detach feature of screen.
    Copyright (C) 2001, 2004-2016 Ned T. Crigler
    dt - further development
    Copyright (C) 2020 b3z
*/
#ifndef dt_h
#define dt_h

#include <config.h>

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if TIME_WITH_SYS_TIME
#include <sys/time.h>
#include <time.h>
#else
#if HAVE_SYS_TIME_H
#include <sys/time.h>
#else
#include <time.h>
#endif
#endif

#ifdef HAVE_PTY_H
#include <pty.h>
#endif

#ifdef HAVE_UTIL_H
#include <util.h>
#endif

#ifdef HAVE_LIBUTIL_H
#include <libutil.h>
#endif

#ifdef HAVE_STROPTS_H
#include <stropts.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#ifdef HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif

#include <termios.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>

#ifndef S_ISREG
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif

#ifndef S_ISSOCK
#define S_ISSOCK(m) (((m) & S_IFMT) == S_IFSOCK)
#endif

extern char *progname, *sockname;
extern int detach_char, no_suspend, redraw_method;
extern struct termios orig_term;
extern int dont_have_tty;

enum
{
	MSG_PUSH	= 0,
	MSG_ATTACH	= 1,
	MSG_DETACH	= 2,
	MSG_WINCH	= 3,
	MSG_REDRAW	= 4,
};

enum
{
	REDRAW_UNSPEC	= 0,
	REDRAW_NONE	= 1,
	REDRAW_CTRL_L	= 2,
	REDRAW_WINCH	= 3,
};

/* The client to master protocol. */
struct packet
{
	unsigned char type;
	unsigned char len;
	union
	{
		unsigned char buf[sizeof(struct winsize)];
		struct winsize ws;
	} u;
};

/*
** The master sends a simple stream of text to the attaching clients, without
** any protocol. This might change back to the packet based protocol in the
** future. In the meantime, however, we minimize the amount of data sent back
** and forth between the client and the master. BUFSIZE is the size of the
** buffer used for the text stream.
*/
#define BUFSIZE 4096

/* This hopefully moves to the bottom of the screen */
#define EOS "\033[999H"

int attach_main(int noerror);
int master_main(char **argv, int waitattach, int dontfork);
int push_main(void);

#ifdef sun
#define BROKEN_MASTER
#endif
#endif
