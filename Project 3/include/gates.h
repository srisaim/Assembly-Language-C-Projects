/* gates.h: gate descriptor structure */
#ifndef GATES_H
#define GATES_H

typedef struct desc_struct {
	unsigned short addr_lo;	/* bits 0-15: part of handler offset */
	unsigned short selector; /* bits 16-31: selector of handler */
	unsigned char zero;	/* bits 32-39: all 0 */
	unsigned char flags;	/* bits 40-47: valid, dpl, type */
	unsigned short addr_hi;	/* bits 48-63: part of handler offset */
} Gate_descriptor;

/* flags */
#define GATE_P (1<<7)		/* present bit */
#define GATE_DPL_KERNEL (0<<5)	/* only kernel code can enter */
#define GATE_INTGATE (14)	/* this is an interrupt gate */
#define GATE_TRAPGATE (15)      /* this is a trap gate */

#endif
