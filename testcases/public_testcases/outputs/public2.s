	.file	"public2.c"
	.text
	.globl	data
	.data
	.align 16
	.type	data, @object
	.size	data, 20
data:
	.long	3222483763
	.long	1078523331
	.long	1063675494
	.long	1093664768
	.long	3239156122
	.globl	size
	.align 4
	.type	size, @object
	.size	size, 4
size:
	.long	5
	.text
	.globl	compute_min
	.type	compute_min, @function
compute_min:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	data(%rip), %xmm0
	movss	%xmm0, -4(%rbp)
	movl	$1, -8(%rbp)
	jmp	.L2
.L5:
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	data(%rip), %rax
	movss	(%rdx,%rax), %xmm1
	movss	-4(%rbp), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L3
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	data(%rip), %rax
	movss	(%rdx,%rax), %xmm0
	movss	%xmm0, -4(%rbp)
.L3:
	addl	$1, -8(%rbp)
.L2:
	movl	size(%rip), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L5
	movss	-4(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	compute_min, .-compute_min
	.globl	compute_avg
	.type	compute_avg, @function
compute_avg:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pxor	%xmm0, %xmm0
	movss	%xmm0, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L9
.L10:
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	data(%rip), %rax
	movss	(%rdx,%rax), %xmm0
	movss	-4(%rbp), %xmm1
	addss	%xmm1, %xmm0
	movss	%xmm0, -4(%rbp)
	addl	$1, -8(%rbp)
.L9:
	movl	size(%rip), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L10
	movl	size(%rip), %eax
	cvtsi2ssl	%eax, %xmm1
	movss	-4(%rbp), %xmm0
	divss	%xmm1, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	compute_avg, .-compute_avg
	.section	.rodata
.LC1:
	.string	"Minimum value: %f\n"
.LC2:
	.string	"Average value: %f\n"
	.text
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
	subq	$16, %rsp
	movl	$0, %eax
	call	compute_min
	movd	%xmm0, %eax
	movl	%eax, -4(%rbp)
	cvtss2sd	-4(%rbp), %xmm0
	leaq	.LC1(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, %eax
	call	compute_avg
	movd	%xmm0, %eax
	movl	%eax, -8(%rbp)
	cvtss2sd	-8(%rbp), %xmm0
	leaq	.LC2(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
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
