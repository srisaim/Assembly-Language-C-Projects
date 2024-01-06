#ifdef __cplusplus
#define asmlinkage extern "C"
#else
#define asmlinkage
#endif
#ifndef EOF
#define EOF (-1)
#endif
#ifndef NULL
#define NULL 0
#endif

#ifndef __ASSEMBLY__
/* built-in user program */
 /* void main(void);  */

/* kernel inter-module calls, some of which are accessible to non-kernel
   code via sysapi interface */

/* in devsupp.c */
/* accessible via sysapi */
void enter_kernel(void);
void exit_kernel(void);
int get_console_dev(void);
void set_console_dev(int dev);
int get_hostline_dev(void);
void set_hostline_dev(int dev);
int get_debugline_dev(void);
void set_debugline_dev(int dev);
unsigned long cons_kbd_init(int dev, unsigned long memory_start);
int kbmon_control(int comline, int fn, void * param);
int kbmon_descript(int dev, char *descript);
int read_uport(int port);
int write_uport(int port, unsigned char val);
int install_dev(int dev, unsigned long (*init)(int, unsigned long),
		int (*putc)(int, char), int (*getc)(int), int (*readyc)(int),
		int (*control)(int,int,void *), int (*descript)(int, char *),
		char *name);
int deinstall_dev(int dev);

/* not accessible via sysapi (kernel private) */
void init_devs(unsigned long memory_start);

/* in saconsole.c */
/* accessible via sysapi */
int cons_putc(int dev, char ch);
/* not accessible via sysapi (kernel private) */
unsigned long con_init(unsigned long kmem_start);

/* in saserial.c */
/* accessible via sysapi */
unsigned long com_init(int dev, unsigned long mem_start);
unsigned long null_init(int dev, unsigned long mem_start);
int com_putc(int comline, char ch);
int com_getc(int comline);
int com_ready(int comline);
int com_control(int comline, int fn, void * param);
void com_readbuf(int comline, char *buf, int nbytes);
int com_cts(int comline);
int com_get_baudrate(int comline);
int com_set_baudrate(int comline, int baudrate);
void com_fast_trans_mode(int console_line, int host_line, char escape_char);
int com_descript(int dev, char *buf);
void com_enable_rints(int dev);
void com_disable_rints(int dev);
/* not accessible via sysapi, at least directly (kernel private) */
void com_enter_kernel(void);
void com_exit_kernel(void);

/* in sakeyboard.c */
/* accessible via sysapi */
int kbd_getc(int dev);
int kbd_ready(int dev);
void hard_reset_now(void);
/* not accessible via sysapi (kernel private) */
unsigned long kbd_init(unsigned long);
void kbd_enter_kernel(void);
void kbd_exit_kernel(void);

/* in saconsole.c */
/* accessible via sysapi */
int cons_descript(char *buf);
void cons_set_vt100_mode(int mode);
int cons_get_vt100_mode(void);
/* not accessible via sysapi (kernel private) */
unsigned long con_init(unsigned long kmem_start);
void console_print(const char *s);

/* in saprintk.c */
/* not accessible via sysapi (kernel private) */
void register_console(void (*proc)(const char *));
int printk(const char *fmt, ...);

/* in i386-stu.c */
/* not accessible via sysapi (kernel private) */
void set_debug_traps(void);

/* in sairq.c */
/* accessible via sysapi */
void arm_trap(int trapnm, void (*traphand)(void));
/* not accessible via sysapi (kernel private) */
void init_IRQ(void);
extern int request_irq(unsigned int irq,void (*handler)(int));
void free_irq(unsigned int irq);
void save_gate(unsigned int irq_nr, char *oldgate);
void restore_gate(unsigned int irq_nr, char *oldgate);
void irq_enter_kernel(void);
void irq_exit_kernel(void);
int irq_read_uport(int port);
int irq_write_uport(int port, unsigned char val);
#endif /* __ASSEMBLY__ */




