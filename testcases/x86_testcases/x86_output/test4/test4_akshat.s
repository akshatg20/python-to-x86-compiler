	.file	"test1.py"

	.text
	.globl _Z9array_sumPii
	.type  _Z9array_sumPii, @function
_Z9array_sumPii:
.LFB0:
	.cfi_startproc
	endbr64
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq %rsp, %rbp
	.cfi_def_cfa_register 6
	subq $0, %rsp
	movq %rdi, -4(%rbp)
	movq rsi, -8(%rbp)
	movq $0, -12(%rbp)
	movq $0, -16(%rbp)
.L2:
	cmpl -8(%rbp), -16(%rbp)
	jge .L3
	movq -16(%rbp), %r10
	leaq 0(,%r10,4), %r11
	movq -4(%rbp), %r10
	addq %r11, %r10
	addq %rbx, -12(%rbp)
	addq $1, -16(%rbp)
	jmp .L2
.L3:
	movq -12(%rbp), %rax
	jmp .LFX0
.LFX0:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size  _Z9array_sumPii, .-_Z9array_sumPii
	.text
	.section	.rodata
.LC0:
	.string "The array is given by"
.LC1:
	.string "\n"
.LC2:
	.string "%d"
.LC3:
	.string "The sum of array elements is "
.LC4:
	.string "%d"
	.text
	.globl _Z4mainv
	.type  _Z4mainv, @function
_Z4mainv:
.LFB1:
	.cfi_startproc
	endbr64
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq %rsp, %rbp
	.cfi_def_cfa_register 6
	subq $0, %rsp
	movq $1, -20(%rbp)
	movq $2, -24(%rbp)
	movq $3, -28(%rbp)
	movq $4, -32(%rbp)
	movq $5, -36(%rbp)
	movq $20, -40(%rbp)
	movq $-4, -44(%rbp)
	movq $5, -48(%rbp)
	movq $8, -52(%rbp)
	movq -52(%rbp), %rdi
	movq -20(%rbp), %rsi
	call  _Z9array_sumPii
	movq %rax, %rbx
	movq %rbx, -12(%rbp)
	leaq  .LC0(%rip), %rdi
	movq $0, %rax
	call  printf@PLT
	leaq  .LC1(%rip), %rdi
	movq $0, %rax
	call  printf@PLT
	movq $0, -56(%rbp)
.L0:
	cmpl -52(%rbp), -56(%rbp)
	jge .L1
	movq -56(%rbp), %r11
	leaq 0(,%r11,4), %r12
	movq -20(%rbp), %r11
	addq %r12, %r11
	leaq  .LC2(%rip), %rdi
	movq %r10, %rsi
	movq $0, %rax
	call  printf@PLT
	leaq  .LC1(%rip), %rdi
	movq $0, %rax
	call  printf@PLT
	addq $1, -56(%rbp)
	jmp .L0
.L1:
	leaq  .LC3(%rip), %rdi
	movq $0, %rax
	call  printf@PLT
	movq -12(%rbp), %r13
	leaq  .LC4(%rip), %rdi
	movq %r13, %rsi
	movq $0, %rax
	call  printf@PLT
	leaq  .LC1(%rip), %rdi
	movq $0, %rax
	call  printf@PLT
	jmp .LFX1
.LFX1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size  _Z4mainv, .-_Z4mainv
	.text
	.globl main
	.type  main, @function
main:
.LFB2:
	.cfi_startproc
	endbr64
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq %rsp, %rbp
	.cfi_def_cfa_register 6
	call  _Z4mainv
	jmp .LFX2
.LFX2:
	leave
	popq 	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size  main, .-main
