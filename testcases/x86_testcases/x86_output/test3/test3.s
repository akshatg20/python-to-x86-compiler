	.file	"test3.py"
	
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
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	cmpl	$1, -4(%rbp)
	jg	.L0
	movl	$1, %eax
	jmp	.L1
.L0:
	movl	-4(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %edi
	call	_Z9factoriali
	imull	-4(%rbp), %eax
.L1:
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
.LC3:
	.string	"%d"
.LC4:
	.string	"\n"
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
.L2:
	movl	-8(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, -12(%rbp)
	jge	.L3
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
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -12(%rbp)
	jmp	.L2
.L3:
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
