# The C callable assembly language function (echo.s)
# Followed steps from Lecture #9 slides.

# Initialization and declaration of values.
	.data
        UART_LSR = 5			# Line Status Register
        UART_LSR_THRE = 0x20		# Transmit Holding Register Empty
        UART_LSR_DR = 0x01		# Data Ready

        .text
        .global echo

# Creating main stack frame for echo
echo:
	pushl	%ebp			# Starting point push ebp
	movl	%esp, %ebp		# And moving esp to ebp
	subl	8(%ebp), %esp
	pushl	%edx			# Setting up register edx
	movl	8(%ebp), %edx		# Com port address

L1:
	addl	$UART_LSR, %edx		# Line status using "UART_LSR"

L2:
	inb	(%dx), %al		# Retrieving data ready
	andb	$UART_LSR_DR, %al	# Read character using "UART_LSR_DR"
	jz	L2			# Jump if zero to L2
	subl	$UART_LSR, %edx		# Data port using "UART_LSR"
	inb	%dx, %al 		# Getting character
	cmpb	12(%ebp), %al		# Comparing
	jz	end			# Jump if zero to end
	outb	%al, %dx
	jmp	L1			# Unconditional jump to L1

end:
	movl	%ebp, %esp 		# Moving data
	popl	%ebp			# Remove ebp using pop
	popl	%edx			# Remove edx using pop
	leave 				# Leave doing opposite, restoring caller's frame
	ret				# Simple return
.end					# End

