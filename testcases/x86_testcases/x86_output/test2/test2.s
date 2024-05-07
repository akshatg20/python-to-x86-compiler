	.file	"test2.py"
	
	.text
	.section	.rodata
.LC0:
	.string	"Value of factorial of "
.LC1:
	.string	"%d"
.LC2:
	.string	" is equal to "
.LC3:
	.string	"%d"
.LC4:
	.string	"\n"
	.text
	.globl	_Z4mainv
	.type	_Z4mainv, @function
_Z4mainv:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$10, -4(%rbp)
	movl	$0, -16(%rbp)
.L0:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, -16(%rbp)
	jge	.L3
	movl	$1, -12(%rbp)
	movl	$0, -8(%rbp)
.L1:
	movl	-8(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jge	.L2
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	-12(%rbp), %eax
	imull	%edx, %eax
	movl	%eax, -12(%rbp)
	addl	$1, -8(%rbp)
	jmp	.L1
.L2:
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-16(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -16(%rbp)
	jmp	.L0
.L3:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_Z4mainv, .-_Z4mainv
	
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
	call	_Z4mainv
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
