# makefile for building C or assembly language programs for the
# Standalone 486 or Pentium IBM PC running in 32-bit protected mode, 
# or "SA PC" for short.
# Single-source-file makefile--needs editing for multiple-module programs

# For a C source, say myprog.c, override the "C=ctest" below by
#  setting C in the make command line: "make C=myprog myprog.lnx"
#  or just "make C=myprog", since $(C).lnx is the first make target.
#  Then myprog.lnx is ready for downloading via "mtip -f myprog.lnx"
#  (followed by ~r and ~d inside the mtip program)
C = ctest

# For an assembler source, say myprog.s, override the "A=atest" below by
#  setting A in the make command line: "make A=myprog myprog.lnx"
#  Then myprog.lnx is ready for downloading via "mtip -f myprog.lnx"
#  (followed by ~d inside the mtip program)
A = atest

# also "make clean" to clean up non-source files in a directory

# system directories needed for compilers, libraries, header files--
# assumes the environment variables 
#    SAPC_TOOLS = /home/cheungr/serl/tutor-linux
#    
# All UNIX tools from ulab had been moved to LINUX by
#
#     Ron Cheung (2/28/2020)
#
# 
SAPC_TOOLS = /home/cheungr/serl/tutor-linux
PC_LIB = $(SAPC_TOOLS)/libc
PC_INC = $(SAPC_TOOLS)/include

PC_CC    = gcc
PC_CFLAGS  = -gdwarf-2 -gstrict-dwarf -march=i586 -m32 -fno-builtin -fno-stack-protector -nostdlib     -c -Wall -I$(PC_INC)
PC_AS    = as --32
PC_NM    = nm
PC_LD    = ld -m elf_i386

# File suffixes:
# .c	C source (often useful both for UNIX host and SAPC)
# .s 	assembly language source
# .lnx  executable image (bits as in memory), for SA PC (Linux a.out format)
# .syms text file of .lnx's symbols and their values (the "symbol table")
# Symbol file "syms"--for most recently built executable in directory

# PC executable--tell ld to start code at 0x100100, load special startup
# module, special PC C libraries--

$(C).lnx: $(C).o $(PC_LIB)/libc.a $(PC_LIB)/startup.o $(PC_LIB)/startup0.o
	$(PC_LD) -N -Ttext 100100 -o $(C).lnx \
		$(PC_LIB)/startup0.o $(PC_LIB)/startup.o \
		$(C).o $(PC_LIB)/libc.a
	rm -f syms;$(PC_NM) -n $(C).lnx>$(C).syms;ln -s $(C).syms syms

# tell gcc to use $(PC_INC) for #include <...> headers--
$(C).o: $(C).c
	$(PC_CC) $(PC_CFLAGS) -I$(PC_INC) -c -o $(C).o $(C).c
	
$(A).lnx: $(A).o $(PC_LIB)/libc.a $(PC_LIB)/startup.o $(PC_LIB)/startup0.o
	$(PC_LD) -N -Ttext 100100 -o $(A).lnx \
		$(PC_LIB)/startup0.o $(PC_LIB)/startup.o \
		$(A).o $(PC_LIB)/libc.a
	rm -f syms;$(PC_NM) -n $(A).lnx>$(A).syms;ln -s $(A).syms syms

$(A).o: $(A).s
	$(PC_AS) -o $(A).o $(A).s

clean:
	rm -f *.o *.syms *.lnx core syms
