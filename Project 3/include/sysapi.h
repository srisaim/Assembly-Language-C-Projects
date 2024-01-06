/* sysapi.h: Device-independent i/o for Tutor and downloaded programs */
/* plus various device-specific calls as well. */
/* This file is included from stdio.h */
#ifndef SYSAPI_H
#define SYSAPI_H

#ifndef EOF
#define EOF (-1)
#endif

/* Used in getc and elsewhere--break out to Tutor.  By using a macro,
   we get a more useful report on the EIP when we get to Tutor */
#define breakpoint()  asm ( "int $3" )

/* for setting EOF from input from user */
#define EOFCHAR '\004'
/* for aborting user input, abort to Tutor--control-C */
#define ESCAPE_TO_TUTOR '\003'

/* Device numbers */
/* logical console */
#define CONSOLE 100
/* logical debug console, for echoing CONSOLE output to debugline */
#define DEBUG_CONSOLE 99
/* combination of monitor for output and keyboard for input */
#define KBMON 0
/* COM lines, i.e, RS232 serial lines */
#define COM1 1
#define COM2 2
#define COM3 3
#define COM4 4

/* Device-independent i/o API, using above device numbers */

/* init: init device driver, possibly claiming some memory starting
 * at mem_start, to whatever address is returned, but this is
 * done only the very first time init is called */
unsigned long init(int dev, unsigned long mem_start);

/* putc: output one char, with lf-> crlf, CONSOLE->console_dev, delay
 * if hostline, broadcase if dev < 0 */
int putc(int dev,char ch);

/* rawputc: output one char, by polling or equivalent, no interpretation
 * of char, but CONSOLE->console_dev mapping provided */
int rawputc(int dev, char ch);

/* getc: get one char from device by polling or equiv., convert CR
 * to '\n', abort if requested, echo if CONSOLE */
int getc(int dev);

/* rawgetc: get one char from device by polling or equiv., no interp. of
 * char, but CONSOLE->console_dev mapping provided */
int rawgetc(int dev);

/* readyc: check if char ready to be getc'd (returns Boolean),
 * with CONSOLE->console_dev mapping */
int readyc(int dev);

/* misc. device control fns */
int devcontrol(int dev, int fn, void *param);

/* text description of dev */
int devdescript(int dev, char *descript);

/* device's official name (KBMON, COM1, etc.) */
char *devname(int dev);

/* device independent i/o (polling) */
typedef unsigned long (*PFIL)(int, unsigned long);
typedef int (*PFI)(int);
typedef int (*PFIC)(int, char);
typedef int (*PFIIP)(int, int, void *);
typedef int (*PFIP)(int, char *);

typedef struct dev_struct {
  PFIL devinit;
  PFIC devputc;			/* no interpretation */
  PFI devgetc;			/* no interpretation */
  PFI devreadyc;		/* return TRUE if char ready to read */
} Device;
/* leave room to grow--real devs: */
#define MAXDEVS 10

#define MAXNAME 20
typedef struct sys_dev_struct {
  PFIL devinit;
  PFIC devputc;			/* no interpretation */
  PFI devgetc;			/* no interpretation */
  PFI devreadyc;		/* return TRUE if char ready to read */
  PFIIP devcontrol;		/* misc. fns. */
  PFIP devdescript;		/* text description of dev */
  char devname[MAXNAME];	/* KBMON, etc. */
} Sys_Device;

/* devs and pseudodevs--through CONSOLE==100 */
#define MAXSYSDEVS 101
extern Sys_Device sys_devtab[];

/* The following struct contains the system API.  The kernel
   creates the master copy of this and the downloaded program
   obtains a pointer to it and uses it for system services */

typedef struct {
Device devtab[MAXDEVS];

/* in samain.c */
/* give the kernel a chance to reestablish essential handlers,
   called when returning from executing unknown code */
void (*enter_kernel)(void);

/* undo whatever had to be done by kernel, restoring handlers
   that the other code had established */
void (*exit_kernel)(void);

/* in devio.c */
/* get device number of current console */
int (*get_console_dev)(void);

/* set console to a certain device */
void (*set_console_dev)(int dev);

/* get dev number of current hostline (line for putc slowdown) */
int (*get_hostline_dev)(void);

/* set hostline to certain device */
void (*set_hostline_dev)(int dev);

/* in saconsole.c */
/* return a string describing the monitor */
int (*cons_descript)(char *buf);

/* set vt100 emulation on monitor to 1 for on, 0 for off */
void (*cons_set_vt100_mode)(int mode);

/* get current vt100 emulation mode */
int (*cons_get_vt100_mode)(void);

/* in/for saserial.c */
/* read nbytes from comline, for fast service */
void (*com_readbuf)(int comline, char *buf, int nbytes);

/* get RS232 CTS line's current signal value */
int (*com_cts)(int comline);

/* get COM line's current baudrate from UART */
int (*com_get_baudrate)(int comline);

/* set COM line's baudrate */
int (*com_set_baudrate)(int comline, int baudrate);

/* get string describing UART */
int (*com_descript)(int dev, char *buf);

/* enable receiver interrupts and queue received characters for
   later pickup by getc.  Normally getc uses polling, no queuing */
void (*com_enable_rints)(int dev);

/* disable receiver interrupts, returning to normal getc processing */
void (*com_disable_rints)(int dev);

/* poll on both COM lines, shuttling chars back and forth, until
   escape char is received on console_line */
void (*com_fast_trans_mode)(int console_line, int host_line, char escape_char);

/* in sakeyboard.c */
/* reboot system */
void (*hard_reset_now)(void);

/* in devsupp.c */
int (*read_uport)(int port);
int (*write_uport)(int port, unsigned char val);

void (*report_pic_regs)(unsigned short *user_irr,unsigned short *user_isr);

/* get dev number of current debugline (line being devoted to debugging) */
int (*get_debugline_dev)(void);

/* set debugline to certain device */
void (*set_debugline_dev)(int dev);

/* install a device in master devtab */
int (*install_dev)(int dev, PFIL initfn, PFIC putcfn, PFI getcfn, 
		   PFI readycfn, PFIIP controlfn, char *name);

} SysAPI;
extern SysAPI *sysapi;		/* pointer to the interface */

typedef struct {
Sys_Device *devtab;			/* device table */

/* in samain.c */
/* give the kernel a chance to reestablish essential handlers,
   called when returning from executing unknown code */
void (*enter_kernel)(void);

/* undo whatever had to be done by kernel, restoring handlers
   that the other code had established */
void (*exit_kernel)(void);

/* read, write saved user port vals (currently only ports 0x21
   and 0xa1, PIC mask regs).  Returns -1 if no saved info for port. */
int (*read_uport)(int port);
int (*write_uport)(int port, unsigned char val);

/* install a device in master devtab */
int (*install_dev)(int dev, PFIL initfn, PFIC putcfn, PFI getcfn,
		   PFI readycfn,  PFIIP control, PFIP descript, char *name);
int (*deinstall_dev)(int dev);

/* in devio.c */
/* get device number of current console */
int (*get_console_dev)(void);

/* set console to a certain device */
void (*set_console_dev)(int dev);

/* get dev number of current hostline (line for putc slowdown) */
int (*get_hostline_dev)(void);

/* set hostline to certain device */
void (*set_hostline_dev)(int dev);

/* get dev number of current debugline (line being devoted to debugging) */
int (*get_debugline_dev)(void);

/* set debugline to certain device */
void (*set_debugline_dev)(int dev);

/* in saconsole.c */
/* set vt100 emulation on monitor to 1 for on, 0 for off */
void (*cons_set_vt100_mode)(int mode);

/* get current vt100 emulation mode */
int (*cons_get_vt100_mode)(void);

/* in/for saserial.c */
/* read nbytes from comline, for fast service */
void (*com_readbuf)(int comline, char *buf, int nbytes);

/* get RS232 CTS line's current signal value */
int (*com_cts)(int comline);

/* get COM line's current baudrate from UART */
int (*com_get_baudrate)(int comline);

/* set COM line's baudrate */
int (*com_set_baudrate)(int comline, int baudrate);

/* enable receiver interrupts and queue received characters for
   later pickup by getc.  Normally getc uses polling, no queuing */
void (*com_enable_rints)(int dev);

/* disable receiver interrupts, returning to normal getc processing */
void (*com_disable_rints)(int dev);

/* poll on both COM lines, shuttling chars back and forth, until
   escape char is received on console_line */
void (*com_fast_trans_mode)(int console_line, int host_line, char escape_char);

/* in sakeyboard.c */
/* reboot system */
void (*hard_reset_now)(void);

} SysAPI2;
extern SysAPI2 *sysapi2;	/* pointer to the interface */

#ifdef SAPC_KERNEL

/* sasys.h has these plus kernel-private inter-module prototypes */
#include <sasys.h>

#else
/* These calls represent the official programming interface
   to the system, like the system calls of a real OS */
/* non-kernel code accesses these api functions via sysapi2 pointer-- */
/* sys_init is normally only used by kernel */
#define sys_init(dev, kmem_start) sysapi2->devtab[dev].devinit(dev, kmem_start)
#define sys_getc(dev) sysapi2->devtab[dev].devgetc(dev)
#define sys_putc(dev, ch) sysapi2->devtab[dev].devputc(dev, ch)
#define sys_readyc(dev) sysapi2->devtab[dev].devreadyc(dev)
#define sys_devcontrol(dev, fn, param) \
              sysapi2->devtab[dev].devcontrol(dev,fn,param)
#define sys_devdescript(dev, str) sysapi2->devtab[dev].devdescript(dev, str)
#define sys_devname(dev) sysapi2->devtab[dev].devname
#define sys_enter_kernel() sysapi2->enter_kernel()
#define sys_exit_kernel() sysapi2->exit_kernel()
#define sys_get_console_dev() sysapi2->get_console_dev()
#define sys_set_console_dev(dev) sysapi2->set_console_dev(dev)
#define sys_get_hostline_dev() sysapi2->get_hostline_dev()
#define sys_set_hostline_dev(dev) sysapi2->set_hostline_dev(dev)
#define sys_get_debugline_dev() sysapi2->get_debugline_dev()
#define sys_set_debugline_dev(dev) sysapi2->set_debugline_dev(dev)
#define sys_cons_set_vt100_mode(mode) sysapi2->cons_set_vt100_mode(mode)
#define sys_cons_get_vt100_mode() sysapi2->cons_get_vt100_mode()
#define sys_com_readbuf(comline, buf, nbytes) \
                sysapi2->com_readbuf(comline,buf,nbytes)
#define sys_com_cts(comline) sysapi2->com_cts(comline)
#define sys_com_get_baudrate(comline) sysapi2->com_get_baudrate(comline)
#define sys_com_set_baudrate(comline, baudrate) \
          sysapi2->com_set_baudrate(comline, baudrate)
#define sys_com_enable_rints(dev) sysapi2->com_enable_rints(dev)
#define sys_com_disable_rints(dev) sysapi2->com_disable_rints(dev)
#define sys_com_fast_trans_mode(console_line,host_line, escape_char) \
          sysapi2->com_fast_trans_mode(console_line,host_line, escape_char)
#define sys_hard_reset_now() sysapi2->hard_reset_now()
#define sys_read_uport(port) sysapi2->read_uport(port)
#define sys_write_uport(port, val) sysapi2->write_uport(port, val)
#define sys_install_dev(dev,init,putc,getc,readyc,control,descript,name) \
             sysapi2->install_dev(dev,init,putc,getc,readyc,control, \
				  descript, name)
#define sys_deinstall_dev(dev)
#endif /* !SAPC_KERNEL */
#endif /* SYSAPI_H */

