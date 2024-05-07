	.file	"test1.py"

	.text
	.section	.rodata
.LC0:
	.string "Value of factorial of "
.LC1:
	.string "%d"
.LC2:
	.string " can be found.\n"
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
	movq $5, -4(%rbp)
	movq $0, -8(%rbp)
.L0:
	movq  -4(%rbp), %rbx
	addq $1, %rbx
	cmpl %rbx, -8(%rbp)
	jge .L1
	leaq  .LC0(%rip), %rdi
	movq $0, %rax
	call  printf@PLT
	movq -8(%rbp), %r10
	leaq  .LC1(%rip), %rdi
	movq %r10, %rsi
	movq $0, %rax
	call  printf@PLT
	leaq  .LC2(%rip), %rdi
	movq $0, %rax
	call  printf@PLT
	addq $1, -8(%rbp)
	jmp .L0
.L1:
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
	call  _Z4mainv
	jmp .LFX1
.LFX1:
	leave
	popq 	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size  main, .-main
