	.file	"test1.py"

	.text
	.section	.rodata
.LC0:
	.string "Value of factorial of "
.LC1:
	.string "%d"
.LC2:
	.string " is equal to "
.LC3:
	.string "%d"
.LC4:
	.string "\n"
	.text
	.globl _Z4mainv
	.type  _Z4mainv, @function
_Z4mainv:
.LFB0:
	.cfi_startproc
	endbr64
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq %rsp, %rbp
	.cfi_def_cfa_register 6
	subq $0, %rsp
	movq $10, -4(%rbp)
	movq $0, -8(%rbp)
.L0:
	movq  -4(%rbp), %rbx
	addq $1, %rbx
	cmpl %rbx, -8(%rbp)
	jge .L3
	movq $1, -12(%rbp)
	movq $0, -16(%rbp)
.L1:
	cmpl -8(%rbp), -16(%rbp)
	jge .L2
	movq  -16(%rbp), %r10
	addq $1, %r10
	imull %r10, -12(%rbp)
	addq $1, -16(%rbp)
	jmp .L1
.L2:
	leaq  .LC0(%rip), %rdi
	movq $0, %rax
	call  printf@PLT
	movq -8(%rbp), %r11
	leaq  .LC1(%rip), %rdi
	movq %r11, %rsi
	movq $0, %rax
	call  printf@PLT
	leaq  .LC2(%rip), %rdi
	movq $0, %rax
	call  printf@PLT
	movq -12(%rbp), %r12
	leaq  .LC3(%rip), %rdi
	movq %r12, %rsi
	movq $0, %rax
	call  printf@PLT
	leaq  .LC4(%rip), %rdi
	movq $0, %rax
	call  printf@PLT
	addq $1, -8(%rbp)
	jmp .L0
.L3:
	jmp .LFX0
.LFX0:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size  _Z4mainv, .-_Z4mainv
	.text
	.globl main
	.type  main, @function
main:
.LFB1:
	.cfi_startproc
	endbr64
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq %rsp, %rbp
	.cfi_def_cfa_register 6
	jmp .LFX1
.LFX1:
	leave
	popq 	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size  main, .-main
