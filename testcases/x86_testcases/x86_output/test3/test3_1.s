	.file	"test3_1.c"
	.text
	.globl	_Z9factoriali
	.type	_Z9factoriali, @function
_Z9factoriali:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	cmpl	$1, -20(%rbp)
	jg	.L2
	movl	$1, %eax
	jmp	.L3
.L2:
	cmpl	$2, -20(%rbp)
	jne	.L4
	movl	$2, %eax
	jmp	.L3
.L4:
	cmpl	$3, -20(%rbp)
	jne	.L5
	movl	$6, %eax
	jmp	.L3
.L5:
	cmpl	$9, -20(%rbp)
	jg	.L6
	movl	$1, -8(%rbp)
	movl	$1, -4(%rbp)
.L8:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jg	.L7
	movl	-8(%rbp), %eax
	imull	-4(%rbp), %eax
	movl	%eax, -8(%rbp)
	addl	$1, -4(%rbp)
	jmp	.L8
.L7:
	movl	-8(%rbp), %eax
	jmp	.L3
.L6:
	movl	-20(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %edi
	call	_Z9factoriali
	imull	-20(%rbp), %eax
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_Z9factoriali, .-_Z9factoriali
	.section	.rodata
.LC0:
	.string	"Value of factorial of "
.LC1:
	.string	"%d"
.LC2:
	.string	" is equal to "
	.text
	.globl	_Z4mainv
	.type	_Z4mainv, @function
_Z4mainv:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$10, -8(%rbp)
	movl	$0, -12(%rbp)
.L11:
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jl	.L13
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	call	_Z9factoriali
	movl	%eax, -4(%rbp)
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$10, %edi
	call	putchar@PLT
	addl	$1, -12(%rbp)
	jmp	.L11
.L13:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	_Z4mainv, .-_Z4mainv
	.globl	main
	.type	main, @function
main:
.LFB2:
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
.LFE2:
	.size	main, .-main
