# C callable assembler function that counts the number of characters in a string.
	.global count
	.text

count:
        push	%ebp
        mov	%esp, %ebp
        sub	$4, %esp
        push	%ebx
        movb	12(%ebp), %dl
        movb	%dl, 12(%ebp)
        movl	$0, -4(%ebp)
.L2:
        movl	8(%ebp), %ebx
        cmpb	$0, (%ebx)
        je	.L3
        movl	8(%ebp), %ebx
        movb	(%ebx), %dl
        cmpb	12(%ebp), %dl
        jne	.L4
        incl	-4(%ebp)
.L4:
        incl	8(%ebp)
        jmp	.L2
.L3:
        movl	-4(%ebp), %eax
        jmp	.L1
.L1:
        leal	-8(%ebp), %esp
        pop	%ebx
        leave
        ret
	.end

