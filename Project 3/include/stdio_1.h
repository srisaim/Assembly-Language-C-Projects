/* SAPC stdio.h, modified to de-support lots of C lib functions,
   leaving sscanf, printf, vsprintf, and a few basic decls 
   for var args, etc. */
/* This is part of the iostream/stdio library, providing -*- C -*- I/O.
   Define ANSI C stdio on top of C++ iostreams.
   Copyright (C) 1991 Per Bothner.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.


This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the Free
Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/*
 *	ANSI Standard: 4.9 INPUT/OUTPUT <stdio.h>
 */

#ifndef _STDIO_H
#define _STDIO_H
#undef _STDIO_USES_IOSTREAM
#define _STDIO_USES_IOSTREAM 1

#ifdef __linux__
#include <features.h>
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL (void*)0
#endif
#endif

#ifndef EOF
#define EOF (-1)
#endif
#ifndef BUFSIZ
#define BUFSIZ 1024
#endif

#include <libio.h>

#ifndef REAL
/* SAPC case--CONSOLE, COM1, etc, dev indep. i/o-- */
#include "sysapi.h"
#endif

#ifdef REAL
#define _IOFBF 0 /* Fully buffered. */
#define _IOLBF 1 /* Line buffered. */
#define _IONBF 2 /* No buffering. */

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

 /* define size_t.  Crud in case <sys/types.h> has defined it. */
#if !defined(_SIZE_T) && !defined(_T_SIZE_) && !defined(_T_SIZE)
#if !defined(__SIZE_T) && !defined(_SIZE_T_) && !defined(___int_size_t_h)
#if !defined(_GCC_SIZE_T) && !defined(_SIZET_)
#define _SIZE_T
#define _T_SIZE_
#define _T_SIZE
#define __SIZE_T
#define _SIZE_T_
#define ___int_size_t_h
#define _GCC_SIZE_T
#define _SIZET_
typedef _IO_size_t size_t;
#endif
#endif
#endif

typedef struct _IO_FILE FILE;
typedef _IO_fpos_t fpos_t;

#define FOPEN_MAX     _G_FOPEN_MAX
#define FILENAME_MAX _G_FILENAME_MAX

/* limited by the number of possible unique combinations. see
 * libio/iotempname.c for details. */
#define TMP_MAX 238328

#define L_ctermid     9
#define L_cuserid     9
#define P_tmpdir      "/tmp"
#define L_tmpnam      20

/* For use by debuggers. These are linked in if printf or fprintf are used. */
extern FILE *stdin, *stdout, *stderr; /* TODO */

#define stdin _IO_stdin
#define stdout _IO_stdout
#define stderr _IO_stderr

__BEGIN_DECLS

extern void clearerr __P((FILE*));
extern int fclose __P((FILE*));
extern int feof __P((FILE*));
extern int ferror __P((FILE*));
extern int fflush __P((FILE*));
extern int fgetc __P((FILE *));
extern int fgetpos __P((FILE* fp, fpos_t *pos));
extern char* fgets __P((char*, int, FILE*));
extern FILE* fopen __P((__const char*, __const char*));
extern int fprintf __P((FILE*, __const char* format, ...));
extern int fputc __P((int, FILE*));
extern int fputs __P((__const char *str, FILE *fp));
extern size_t fread __P((void*, size_t, size_t, FILE*));
extern FILE* freopen __P((__const char*, __const char*, FILE*));
extern int fscanf __P((FILE *fp, __const char* format, ...));
extern int fseek __P((FILE* fp, long int offset, int whence));
extern int fsetpos __P((FILE* fp, __const fpos_t *pos));
extern long int ftell __P((FILE* fp));
extern size_t fwrite __P((__const void*, size_t, size_t, FILE*));
extern int getc __P((FILE *));
extern int getchar __P((void));
/*#extern char* gets __P((char*)); */
extern void perror __P((__const char *));
extern int printf __P((__const char* format, ...));
#else
extern int printf __P((const char* format, ...));
extern int fprintf __P((int, const char* format, ...));
extern int kprintf __P((const char* format, ...));  
extern char* gets __P((char*));
/*extern  int strcpy __P((char*, char*)); */
/*extern int strlen __P((char*)); */
#endif
#ifdef REAL
extern int putc __P((int, FILE *));
extern int putchar __P((int));
extern int puts __P((__const char *str));
extern int remove __P((__const char*));
extern int rename __P((__const char* _old, __const char* _new));
extern void rewind __P((FILE*));
#endif /* REAL */
extern int scanf __P((__const char* format, ...));
#ifdef REAL
extern void setbuf __P((FILE*, char*));
extern void setlinebuf __P((FILE*));
extern void setbuffer __P((FILE*, char*, int));
extern int setvbuf __P((FILE*, char*, int mode, size_t size));
#endif
extern int sprintf __P((char*, __const char* format, ...));
extern int sscanf __P((__const char* string, __const char* format, ...));
#ifdef REAL
extern FILE* tmpfile __P((void));
extern char* tmpnam __P((char*));
extern int ungetc __P((int c, FILE* fp));
extern int vfprintf __P((FILE *fp, char __const *fmt0, _G_va_list));
extern int vprintf __P((char __const *fmt, _G_va_list));
extern int vsprintf __P((char* string, __const char* format, _G_va_list));
#else
int vsprintf(char *buf, const char *fmt, _G_va_list args);
#endif
#ifdef REAL
#if !defined(__STRICT_ANSI__)
extern int vfscanf __P((FILE*, __const char *, _G_va_list));
extern int vscanf __P((__const char *, _G_va_list));
extern int vsscanf __P((__const char *, __const char *, _G_va_list));

extern int getw __P((FILE*));
extern int putw __P((int, FILE*));

extern char* tempnam __P((__const char *__dir, __const char *__pfx));
#endif

#ifdef REAL
#ifdef __GNU_LIBRARY__

#ifdef  __USE_BSD
extern int sys_nerr;
extern char *sys_errlist[];
#endif
#ifdef  __USE_GNU
extern int _sys_nerr;
extern char *_sys_errlist[];
#endif
 
#ifdef  __USE_MISC
/* Print a message describing the meaning of the given signal number. */
extern void psignal __P ((int __sig, __const char *__s));
#endif /* Non strict ANSI and not POSIX only.  */

#endif /* __GNU_LIBRARY__ */

#endif /* __STRICT_ANSI__ */

#ifdef __USE_GNU
extern _IO_ssize_t getdelim __P ((char **, size_t *, int, FILE*));
#if 0 
/* Don't use this name. It is way too common. H.J. */
extern _IO_ssize_t getline __P ((char **, size_t *, FILE *));
#endif

extern int snprintf __P ((char *, size_t, const char *, ...));
extern int vsnprintf __P ((char *, size_t, const char *, _G_va_list));

extern int asprintf __P((char **, const char *, ...));
extern int vasprintf __P((char **, const char *, _G_va_list));
#endif

#if !defined(__STRICT_ANSI__) || defined(_POSIX_SOURCE)
extern FILE *fdopen __P((int, __const char *));
extern int fileno __P((FILE*));
extern FILE* popen __P((__const char*, __const char*));
extern int pclose __P((FILE*));
#endif

extern int __underflow __P((struct _IO_FILE*));
extern int __overflow __P((struct _IO_FILE*, int));

#define getc(fp) _IO_getc(fp)
#define putc(c, fp) _IO_putc(c, fp)
#define putchar(c) putc(c, stdout)
#define getchar() getc(stdin)

__END_DECLS
#endif /* REAL */

#endif /*!_STDIO_H*/
