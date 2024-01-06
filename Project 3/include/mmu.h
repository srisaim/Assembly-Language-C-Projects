/* mmu.h */
#ifndef MMU_H
#define MMU_H

typedef union {
unsigned char flags;		/* low 8 bits have flags */
unsigned long pf_addr;		/* after zero-ing out low bits  */
} PTE;

#define PTE_PCD (1<<4)
#define PTE_PWT (3<<4)

#define USER_MEM_START 0x100000
#define USER_MEM_END 0x400000
#define PAGESIZE 0x1000

void set_user_pages_uncacheable();
void set_user_pages_cacheable();
#endif
