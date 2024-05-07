	.file	"test1.py"

	.text
	.globl _Z9factoriali
	.type  _Z9factoriali, @function
_Z9factoriali:
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
	cmpl $1, -4(%rbp)
	jg .L0
	movq $1, %rax
	jmp .L1
.L0:
	movq  -4(%rbp), %rbx
	subq $1, %rbx
	movq %rbx, %rdi
	call  _Z9factoriali
	movq %rax, %r10
	movq -4(%rbp), %r11
	imull %r10, %r11
	movq %r11, %rax
.L1:
	jmp .LFX0
.LFX0:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size  _Z9factoriali, .-_Z9factoriali
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
.LFB1:
	.cfi_startproc
	endbr64
	pushq %rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq %rsp, %rbp
	.cfi_def_cfa_register 6
	subq $0, %rsp
	movq $10, -8(%rbp)
	movq $0, -12(%rbp)
.L2:
	movq  -8(%rbp), %rbx
	addq $1, %rbx
	cmpl %rbx, -12(%rbp)
	jge .L3
	movq -12(%rbp), %rdi
	call  _Z9factoriali
	movq %rax, -16(%rbp)
	leaq  .LC0(%rip), %rdi
	movq $0, %rax
	call  printf@PLT
	movq -12(%rbp), %r10
	leaq  .LC1(%rip), %rdi
	movq %r10, %rsi
	movq $0, %rax
	call  printf@PLT
	leaq  .LC2(%rip), %rdi
	movq $0, %rax
	call  printf@PLT
	movq -16(%rbp), %r11
	leaq  .LC3(%rip), %rdi
	movq %r11, %rsi
	movq $0, %rax
	call  printf@PLT
	leaq  .LC4(%rip), %rdi
	movq $0, %rax
	call  printf@PLT
	addq $1, -12(%rbp)
	jmp .L2
.L3:
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
