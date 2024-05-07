	.file	"public4.c"
	.text
	.globl	binarySearch
	.type	binarySearch, @function
binarySearch:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	%ecx, -36(%rbp)
	jmp	.L2
.L6:
	movl	-36(%rbp), %eax
	subl	-32(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, %edx
	movl	-32(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	%eax, -28(%rbp)
	jne	.L3
	movl	-4(%rbp), %eax
	jmp	.L4
.L3:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	%eax, -28(%rbp)
	jle	.L5
	movl	-4(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -32(%rbp)
	jmp	.L2
.L5:
	movl	-4(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -36(%rbp)
.L2:
	movl	-32(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jle	.L6
	movl	$-1, %eax
.L4:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	binarySearch, .-binarySearch
	.section	.rodata
	.align 8
.LC0:
	.string	"Element is present at index: %d\n"
.LC1:
	.string	"Element is not present"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	$3, -48(%rbp)
	movl	$4, -44(%rbp)
	movl	$5, -40(%rbp)
	movl	$6, -36(%rbp)
	movl	$7, -32(%rbp)
	movl	$8, -28(%rbp)
	movl	$9, -24(%rbp)
	movl	$7, -4(%rbp)
	movl	-4(%rbp), %eax
	leal	-1(%rax), %edx
	leaq	-48(%rbp), %rax
	movl	%edx, %ecx
	movl	$0, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	binarySearch
	movl	%eax, -8(%rbp)
	cmpl	$-1, -8(%rbp)
	je	.L8
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L9
.L8:
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
.L9:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
