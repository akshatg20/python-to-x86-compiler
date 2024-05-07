	.file	"test7.c"
	
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"Inside the constructor for MathOperation class\n"
	.text
	.globl	_Z22MathOperation___init__P13MathOperation
	.type	_Z22MathOperation___init__P13MathOperation, @function
_Z22MathOperation___init__P13MathOperation:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	_Z22MathOperation___init__P13MathOperation, .-_Z22MathOperation___init__P13MathOperation
	
	.section	.rodata
.LC1:
	.string	"This is never called\n"
	.text
	.globl	_Z22MathOperation_uncalledP13MathOperationi
	.type	_Z22MathOperation_uncalledP13MathOperationi, @function
_Z22MathOperation_uncalledP13MathOperationi:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	_Z22MathOperation_uncalledP13MathOperationi, .-_Z22MathOperation_uncalledP13MathOperationi
	
	.section	.rodata
	.align 8
.LC2:
	.string	"This is a simple testcase for classes\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-1(%rbp), %rax
	movq	%rax, %rdi
	call	_Z22MathOperation___init__P13MathOperation
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
