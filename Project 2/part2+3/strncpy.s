# Program to copy n characters of a string (strncpy.s)
        .text
        .global mystrncpy

# Creating main stack frame mystrncpy
mystrncpy:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%esi
.loop2:
	movl	16(%ebp), %ebx
	decl	16(%ebp)
	cmpl	$0, %ebx
	je	.loop3
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	movb	(%ebx), %dl
	movb	%dl, (%esi)
	incl	12(%ebp)
	incl	8(%ebp)
	cmpb	$0, %bl
	je	.loop3
	jmp	.loop2
.loop3:
	leal	-8(%ebp), %esp
	popl	%esi
	popl	%ebx
	leave
	ret
.end
