# Program memory.s to demonstrate page table operations
# Build it in linux using:
#         as --32 -al -o memory.o memory.s
#         ld -m elf_i386 -N -Ttext 0x100100 -o memory.lnx memory.o
# 
#         Date: December 4,2019
#               August 12,2020 
#
# Run the lnx file using the tutor VM
# Clear the A bit and D bit of vpn#0x100, 0x101, 0x102 after loading
#    to see a clearer demonstration of the important bit operations
# Single step through the program using the command t
# Examine the A and D bits of vpn#0x100, 0x101, 0x102 after each step 
#
#
     
.globl _start, label1
	.text
_start:                      #Program start in vpn# 0x100
	 movl $0x100, %eax    
	 movl locate1, %ebx   #Acessing memory in vpn# 0x102
	 movl %ebx, locate1   #Writing in memory in vpn# 0x102
	 jmp label1

	.space 0x001000
 label1:                      #Program in vpn# 0x101
         movl $0x300, %eax
         movl %eax, locate1
	 
	 .space 0x001000
         .data
 locate1:
	 .long 0x400         #Data is stored in vpn# 0x102
	 .end

