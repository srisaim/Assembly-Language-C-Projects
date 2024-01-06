# Program to print binary characters (printbin.s) 
# Comments just to remember and keep track of code
        .text
        .global printbin
        asc:
                .ascii "0011 1101\0"

# Creating main stack frame for printbin
printbin:
        pushl 	%ebp			# Starting point push ebp
        movl	%esp, %ebp         	# And moving esp to ebp
        subl	$8, %esp
        movl	8(%ebp), %eax	     	# User input is moved to eax
        movl	%eax, -4(%ebp)    	# Stores input in variable
        movl	$0, -8(%ebp)
        movl	%eax, -8(%ebp)    	# Input in variable
        sarl	$4, -8(%ebp)       	# Shifting 4 spaces to right
        movl	$asc, %edx         	# Saves asc

        call	donibble           	# Call donibble
        addl	$1, %edx
        movl	-4(%ebp), %eax     	# Move input to eax
        movl	%eax, -8(%ebp)     	# Move input to ebp

        call	donibble           	# Call donibble
        movl	$asc, %eax         	# Move asc to eax
        movl	%ebp, %esp
        popl	%ebp               	# Pop ebp
        ret                    		# Return 

        movl	$asc, %eax         	# Moving asc
        movl	%ebp, %esp
        popl	%ebp               	# Pop ebp
        ret                     	# Return

# Creating a new stack for donibble
donibble:
        pushl	%ebp			# Starting point push ebp
        movl	%esp, %ebp		# And moving esp to ebp
        subl	$16, %esp
        movl	8(%ebp), %eax		# User input is moved to eax
        movb	%al, -4(%ebp)
        movl	$4, -12(%ebp)
        movl	$3, -16(%ebp)
        jmp	string			# Jump String

.data

# Creating another stack for return string storage.
string:
        movl	8(%ebp),%eax		# Move input to eax
        movl	%eax, -8(%ebp)		# Move input to ebp
        movl	-16(%ebp), %ecx
        sarl	%cl, -8(%ebp)
        andl	$1, -8(%ebp)		# Get last bit
        movzbl	-8(%ebp), %eax		# Bit is stored in eax
        addb	$0x30, %al
        movb	%al, (%edx)
        addl	$1, %edx
        subl	$1, -16(%ebp)
        subl	$1, -12(%ebp)
        cmpb	$0, -12(%ebp)		# Testing to check null
        jne	string			# Jump if not equal
        movl	%ebp, %esp
        popl	%ebp			# Pop ebp
        ret              		# Return

.end

