	.file	"test1.py"
	
	.text
	.section	.rodata
.LC0:
	.string	"Value of factorial of "
.LC1:
	.string	"%d"
.LC2:
	.string	" can be found."
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
	movl	$5, -4(%rbp)
	movl	$0, -8(%rbp)
.L0:
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cmpl	%eax, -8(%rbp)
	jge	.L1
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	addl	$1, -8(%rbp)
	jmp	.L0
.L1:
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
