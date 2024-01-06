# The C callable assembly language function (largest.s) to find the largest number in an array of integers.
	.text
	.global largest

# Creating main stack frame for largest
largest:
	pushl	%ebp			# Starting point push ebp
	movl	%esp, %ebp		# And moving esp to ebp
	subl	$8, %esp		# Setting up room for local variables
	pushl	%ebx			# Setting up register ebx
	pushl	%esi			# Setting up register esi
	pushl	%edi			# Setting up register edi
	movl	8(%ebp), %ebx		# Stores memory location value in ebx

	movl	(%ebx), %edx		# Move data from ebx into edx
	movl	%edx, -8(%ebp)		
	movl	$1, -4(%ebp)		# Counter into memory address

L2:
	movl	12(%ebp), %edx		# Move data from ebp+12 into edx
	cmpl	-4(%ebp), %edx		# Comparing data
	jle	L3			# Jump to L3 when less than or equal to after compare
	movl	-4(%ebp), %ebx		# Move data into ebx
	movl	%ebx, %esi		# Restore esi
	sall	$2, %esi		# Left shit
	movl	8(%ebp), %edi		# Move data into edi
	movl	-8(%ebp), %edx		# Move data into edx
	cmpl	(%esi, %edi), %edx	# Comparing data
	jge	L5			# Jump to L5 when greater than or equal to after compare
	movl	-4(%ebp), %ebx		# Moving data
	movl	%ebx, %esi		# Restore esi
	sall	$2, %esi		# Left shift

	movl	8(%ebp), %edi
	movl	(%esi, %edi), %edx	# Data movement
	movl	%edx, -8(%ebp)

L5:
	incl	-4(%ebp)		# Incrementation
	jmp	L2			# Unconditional jump to L2

L3:
	movl	-8(%ebp), %eax		# Stores memory location value in eax
	jmp	end			# Unconditional jump to end

end:	
	leal	-20(%ebp), %esp		# Assigning esp the value
	popl	%edi			# Remove edi using pop
	popl	%esi                    # Remove esi using pop
	popl	%ebx			# Remove ebx using pop
	leave				# Leave doing opposite, restoring the caller's frame
	ret				# Simple return
.end					# End
