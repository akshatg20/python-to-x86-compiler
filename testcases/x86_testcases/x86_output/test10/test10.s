	.file	"test10.cpp"
	.text
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.text._ZN8EmployeeC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,"axG",@progbits,_ZN8EmployeeC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,comdat
	.align 2
	.weak	_ZN8EmployeeC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
	.type	_ZN8EmployeeC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_, @function
_ZN8EmployeeC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_:
.LFB1523:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1523
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB0:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE0:
	movq	-24(%rbp), %rax
	leaq	32(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
.LEHB1:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE1:
	movq	-24(%rbp), %rax
	leaq	64(%rax), %rdx
	movq	-48(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
.LEHB2:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE2:
	jmp	.L6
.L5:
	endbr64
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	addq	$32, %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L3
.L4:
	endbr64
	movq	%rax, %rbx
.L3:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB3:
	call	_Unwind_Resume@PLT
.LEHE3:
.L6:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1523:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZN8EmployeeC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,"aG",@progbits,_ZN8EmployeeC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,comdat
.LLSDA1523:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1523-.LLSDACSB1523
.LLSDACSB1523:
	.uleb128 .LEHB0-.LFB1523
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1523
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L4-.LFB1523
	.uleb128 0
	.uleb128 .LEHB2-.LFB1523
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L5-.LFB1523
	.uleb128 0
	.uleb128 .LEHB3-.LFB1523
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSE1523:
	.section	.text._ZN8EmployeeC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,"axG",@progbits,_ZN8EmployeeC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,comdat
	.size	_ZN8EmployeeC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_, .-_ZN8EmployeeC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
	.weak	_ZN8EmployeeC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
	.set	_ZN8EmployeeC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,_ZN8EmployeeC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
	.section	.rodata
.LC0:
	.string	"Name: "
.LC1:
	.string	"Employee ID: "
.LC2:
	.string	"Department: "
	.section	.text._ZN8Employee12display_infoEv,"axG",@progbits,_ZN8Employee12display_infoEv,comdat
	.align 2
	.weak	_ZN8Employee12display_infoEv
	.type	_ZN8Employee12display_infoEv, @function
_ZN8Employee12display_infoEv:
.LFB1525:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	.LC0(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKNSt7__cxx1112basic_stringIS4_S5_T1_EE@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	leaq	.LC1(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	addq	$32, %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKNSt7__cxx1112basic_stringIS4_S5_T1_EE@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	leaq	.LC2(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	addq	$64, %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKNSt7__cxx1112basic_stringIS4_S5_T1_EE@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1525:
	.size	_ZN8Employee12display_infoEv, .-_ZN8Employee12display_infoEv
	.section	.text._ZN8EmployeeD2Ev,"axG",@progbits,_ZN8EmployeeD5Ev,comdat
	.align 2
	.weak	_ZN8EmployeeD2Ev
	.type	_ZN8EmployeeD2Ev, @function
_ZN8EmployeeD2Ev:
.LFB1528:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$64, %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-8(%rbp), %rax
	addq	$32, %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1528:
	.size	_ZN8EmployeeD2Ev, .-_ZN8EmployeeD2Ev
	.weak	_ZN8EmployeeD1Ev
	.set	_ZN8EmployeeD1Ev,_ZN8EmployeeD2Ev
	.section	.rodata
.LC3:
	.string	""
	.section	.text._ZN7ManagerC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,"axG",@progbits,_ZN7ManagerC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,comdat
	.align 2
	.weak	_ZN7ManagerC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
	.type	_ZN7ManagerC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_, @function
_ZN7ManagerC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_:
.LFB1530:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1530
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$168, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -152(%rbp)
	movq	%rsi, -160(%rbp)
	movq	%rdx, -168(%rbp)
	movq	%rcx, -176(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-152(%rbp), %rbx
	movq	-176(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB4:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE4:
	movq	-168(%rbp), %rdx
	leaq	-96(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB5:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE5:
	movq	-160(%rbp), %rdx
	leaq	-128(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB6:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE6:
	leaq	-64(%rbp), %rcx
	leaq	-96(%rbp), %rdx
	leaq	-128(%rbp), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB7:
	call	_ZN8EmployeeC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
.LEHE7:
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-152(%rbp), %rax
	leaq	96(%rax), %rbx
	leaq	-129(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-129(%rbp), %rdx
	leaq	-64(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB8:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE8:
	leaq	-130(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-130(%rbp), %rdx
	leaq	-96(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB9:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE9:
	leaq	-131(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-131(%rbp), %rdx
	leaq	-128(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB10:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE10:
	leaq	-64(%rbp), %rcx
	leaq	-96(%rbp), %rdx
	leaq	-128(%rbp), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB11:
	call	_ZN8EmployeeC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
.LEHE11:
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-131(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-130(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-129(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	-152(%rbp), %rax
	leaq	192(%rax), %rbx
	leaq	-129(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-129(%rbp), %rdx
	leaq	-64(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB12:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE12:
	leaq	-130(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-130(%rbp), %rdx
	leaq	-96(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB13:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE13:
	leaq	-131(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-131(%rbp), %rdx
	leaq	-128(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB14:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE14:
	leaq	-64(%rbp), %rcx
	leaq	-96(%rbp), %rdx
	leaq	-128(%rbp), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB15:
	call	_ZN8EmployeeC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
.LEHE15:
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-131(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-130(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-129(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	-152(%rbp), %rax
	movl	$0, 288(%rax)
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L23
	jmp	.L35
.L26:
	endbr64
	movq	%rax, %rbx
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L12
.L25:
	endbr64
	movq	%rax, %rbx
.L12:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L13
.L24:
	endbr64
	movq	%rax, %rbx
.L13:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB16:
	call	_Unwind_Resume@PLT
.L30:
	endbr64
	movq	%rax, %rbx
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L15
.L29:
	endbr64
	movq	%rax, %rbx
.L15:
	leaq	-131(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L16
.L28:
	endbr64
	movq	%rax, %rbx
.L16:
	leaq	-130(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L17
.L27:
	endbr64
	movq	%rax, %rbx
.L17:
	leaq	-129(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	jmp	.L18
.L34:
	endbr64
	movq	%rax, %rbx
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L20
.L33:
	endbr64
	movq	%rax, %rbx
.L20:
	leaq	-131(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L21
.L32:
	endbr64
	movq	%rax, %rbx
.L21:
	leaq	-130(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L22
.L31:
	endbr64
	movq	%rax, %rbx
.L22:
	leaq	-129(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	-152(%rbp), %rax
	addq	$96, %rax
	movq	%rax, %rdi
	call	_ZN8EmployeeD1Ev
.L18:
	movq	-152(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8EmployeeD2Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE16:
.L35:
	call	__stack_chk_fail@PLT
.L23:
	addq	$168, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1530:
	.section	.gcc_except_table._ZN7ManagerC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,"aG",@progbits,_ZN7ManagerC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,comdat
.LLSDA1530:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1530-.LLSDACSB1530
.LLSDACSB1530:
	.uleb128 .LEHB4-.LFB1530
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB5-.LFB1530
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L24-.LFB1530
	.uleb128 0
	.uleb128 .LEHB6-.LFB1530
	.uleb128 .LEHE6-.LEHB6
	.uleb128 .L25-.LFB1530
	.uleb128 0
	.uleb128 .LEHB7-.LFB1530
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L26-.LFB1530
	.uleb128 0
	.uleb128 .LEHB8-.LFB1530
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L27-.LFB1530
	.uleb128 0
	.uleb128 .LEHB9-.LFB1530
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L28-.LFB1530
	.uleb128 0
	.uleb128 .LEHB10-.LFB1530
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L29-.LFB1530
	.uleb128 0
	.uleb128 .LEHB11-.LFB1530
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L30-.LFB1530
	.uleb128 0
	.uleb128 .LEHB12-.LFB1530
	.uleb128 .LEHE12-.LEHB12
	.uleb128 .L31-.LFB1530
	.uleb128 0
	.uleb128 .LEHB13-.LFB1530
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L32-.LFB1530
	.uleb128 0
	.uleb128 .LEHB14-.LFB1530
	.uleb128 .LEHE14-.LEHB14
	.uleb128 .L33-.LFB1530
	.uleb128 0
	.uleb128 .LEHB15-.LFB1530
	.uleb128 .LEHE15-.LEHB15
	.uleb128 .L34-.LFB1530
	.uleb128 0
	.uleb128 .LEHB16-.LFB1530
	.uleb128 .LEHE16-.LEHB16
	.uleb128 0
	.uleb128 0
.LLSDACSE1530:
	.section	.text._ZN7ManagerC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,"axG",@progbits,_ZN7ManagerC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,comdat
	.size	_ZN7ManagerC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_, .-_ZN7ManagerC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
	.weak	_ZN7ManagerC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
	.set	_ZN7ManagerC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,_ZN7ManagerC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
	.section	.text._ZN8EmployeeaSERKS_,"axG",@progbits,_ZN8EmployeeaSERKS_,comdat
	.align 2
	.weak	_ZN8EmployeeaSERKS_
	.type	_ZN8EmployeeaSERKS_, @function
_ZN8EmployeeaSERKS_:
.LFB1533:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEaSERKS4_@PLT
	movq	-16(%rbp), %rax
	leaq	32(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	$32, %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEaSERKS4_@PLT
	movq	-16(%rbp), %rax
	leaq	64(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	$64, %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEaSERKS4_@PLT
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1533:
	.size	_ZN8EmployeeaSERKS_, .-_ZN8EmployeeaSERKS_
	.section	.rodata
	.align 8
.LC4:
	.string	"No more space for any technician under manager "
	.section	.text._ZN7Manager14add_technicianE8Employee,"axG",@progbits,_ZN7Manager14add_technicianE8Employee,comdat
	.align 2
	.weak	_ZN7Manager14add_technicianE8Employee
	.type	_ZN7Manager14add_technicianE8Employee, @function
_ZN7Manager14add_technicianE8Employee:
.LFB1532:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	288(%rax), %eax
	testl	%eax, %eax
	jne	.L39
	movq	-8(%rbp), %rax
	leaq	96(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZN8EmployeeaSERKS_
	movq	-8(%rbp), %rax
	movl	288(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 288(%rax)
	jmp	.L38
.L39:
	movq	-8(%rbp), %rax
	movl	288(%rax), %eax
	cmpl	$1, %eax
	jne	.L41
	movq	-8(%rbp), %rax
	leaq	192(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZN8EmployeeaSERKS_
	movq	-8(%rbp), %rax
	movl	288(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 288(%rax)
	jmp	.L38
.L41:
	leaq	.LC4(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKNSt7__cxx1112basic_stringIS4_S5_T1_EE@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	nop
.L38:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1532:
	.size	_ZN7Manager14add_technicianE8Employee, .-_ZN7Manager14add_technicianE8Employee
	.section	.rodata
	.align 8
.LC5:
	.string	"Technicians under this manager:"
	.section	.text._ZN7Manager17display_team_infoEv,"axG",@progbits,_ZN7Manager17display_team_infoEv,comdat
	.align 2
	.weak	_ZN7Manager17display_team_infoEv
	.type	_ZN7Manager17display_team_infoEv, @function
_ZN7Manager17display_team_infoEv:
.LFB1534:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8Employee12display_infoEv
	leaq	.LC5(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	movq	-8(%rbp), %rax
	addq	$96, %rax
	movq	%rax, %rdi
	call	_ZN8Employee12display_infoEv
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	movq	-8(%rbp), %rax
	addq	$192, %rax
	movq	%rax, %rdi
	call	_ZN8Employee12display_infoEv
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1534:
	.size	_ZN7Manager17display_team_infoEv, .-_ZN7Manager17display_team_infoEv
	.section	.text._ZN10TechnicianC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee,"axG",@progbits,_ZN10TechnicianC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee,comdat
	.align 2
	.weak	_ZN10TechnicianC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee
	.type	_ZN10TechnicianC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee, @function
_ZN10TechnicianC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee:
.LFB1536:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1536
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$168, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -136(%rbp)
	movq	%rsi, -144(%rbp)
	movq	%rdx, -152(%rbp)
	movq	%rcx, -160(%rbp)
	movq	%r8, -168(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-136(%rbp), %rbx
	movq	-160(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB17:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE17:
	movq	-152(%rbp), %rdx
	leaq	-96(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB18:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE18:
	movq	-144(%rbp), %rdx
	leaq	-128(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB19:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE19:
	leaq	-64(%rbp), %rcx
	leaq	-96(%rbp), %rdx
	leaq	-128(%rbp), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB20:
	call	_ZN8EmployeeC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
.LEHE20:
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-136(%rbp), %rax
	movq	-168(%rbp), %rdx
	movq	%rdx, 96(%rax)
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L49
	jmp	.L53
.L52:
	endbr64
	movq	%rax, %rbx
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L47
.L51:
	endbr64
	movq	%rax, %rbx
.L47:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L48
.L50:
	endbr64
	movq	%rax, %rbx
.L48:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB21:
	call	_Unwind_Resume@PLT
.LEHE21:
.L53:
	call	__stack_chk_fail@PLT
.L49:
	addq	$168, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1536:
	.section	.gcc_except_table._ZN10TechnicianC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee,"aG",@progbits,_ZN10TechnicianC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee,comdat
.LLSDA1536:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1536-.LLSDACSB1536
.LLSDACSB1536:
	.uleb128 .LEHB17-.LFB1536
	.uleb128 .LEHE17-.LEHB17
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB18-.LFB1536
	.uleb128 .LEHE18-.LEHB18
	.uleb128 .L50-.LFB1536
	.uleb128 0
	.uleb128 .LEHB19-.LFB1536
	.uleb128 .LEHE19-.LEHB19
	.uleb128 .L51-.LFB1536
	.uleb128 0
	.uleb128 .LEHB20-.LFB1536
	.uleb128 .LEHE20-.LEHB20
	.uleb128 .L52-.LFB1536
	.uleb128 0
	.uleb128 .LEHB21-.LFB1536
	.uleb128 .LEHE21-.LEHB21
	.uleb128 0
	.uleb128 0
.LLSDACSE1536:
	.section	.text._ZN10TechnicianC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee,"axG",@progbits,_ZN10TechnicianC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee,comdat
	.size	_ZN10TechnicianC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee, .-_ZN10TechnicianC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee
	.weak	_ZN10TechnicianC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee
	.set	_ZN10TechnicianC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee,_ZN10TechnicianC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee
	.section	.text._ZN7ManagerD2Ev,"axG",@progbits,_ZN7ManagerD5Ev,comdat
	.align 2
	.weak	_ZN7ManagerD2Ev
	.type	_ZN7ManagerD2Ev, @function
_ZN7ManagerD2Ev:
.LFB1541:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$192, %rax
	movq	%rax, %rdi
	call	_ZN8EmployeeD1Ev
	movq	-8(%rbp), %rax
	addq	$96, %rax
	movq	%rax, %rdi
	call	_ZN8EmployeeD1Ev
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8EmployeeD2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1541:
	.size	_ZN7ManagerD2Ev, .-_ZN7ManagerD2Ev
	.weak	_ZN7ManagerD1Ev
	.set	_ZN7ManagerD1Ev,_ZN7ManagerD2Ev
	.section	.text._ZN10TechnicianD2Ev,"axG",@progbits,_ZN10TechnicianD5Ev,comdat
	.align 2
	.weak	_ZN10TechnicianD2Ev
	.type	_ZN10TechnicianD2Ev, @function
_ZN10TechnicianD2Ev:
.LFB1544:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8EmployeeD2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1544:
	.size	_ZN10TechnicianD2Ev, .-_ZN10TechnicianD2Ev
	.weak	_ZN10TechnicianD1Ev
	.set	_ZN10TechnicianD1Ev,_ZN10TechnicianD2Ev
	.section	.text._ZN8EmployeeC2ERKS_,"axG",@progbits,_ZN8EmployeeC5ERKS_,comdat
	.align 2
	.weak	_ZN8EmployeeC2ERKS_
	.type	_ZN8EmployeeC2ERKS_, @function
_ZN8EmployeeC2ERKS_:
.LFB1547:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1547
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB22:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE22:
	movq	-24(%rbp), %rax
	addq	$32, %rax
	movq	-32(%rbp), %rdx
	addq	$32, %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB23:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE23:
	movq	-24(%rbp), %rax
	addq	$64, %rax
	movq	-32(%rbp), %rdx
	addq	$64, %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB24:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE24:
	jmp	.L61
.L60:
	endbr64
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	addq	$32, %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L58
.L59:
	endbr64
	movq	%rax, %rbx
.L58:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB25:
	call	_Unwind_Resume@PLT
.LEHE25:
.L61:
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1547:
	.section	.gcc_except_table._ZN8EmployeeC2ERKS_,"aG",@progbits,_ZN8EmployeeC5ERKS_,comdat
.LLSDA1547:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1547-.LLSDACSB1547
.LLSDACSB1547:
	.uleb128 .LEHB22-.LFB1547
	.uleb128 .LEHE22-.LEHB22
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB23-.LFB1547
	.uleb128 .LEHE23-.LEHB23
	.uleb128 .L59-.LFB1547
	.uleb128 0
	.uleb128 .LEHB24-.LFB1547
	.uleb128 .LEHE24-.LEHB24
	.uleb128 .L60-.LFB1547
	.uleb128 0
	.uleb128 .LEHB25-.LFB1547
	.uleb128 .LEHE25-.LEHB25
	.uleb128 0
	.uleb128 0
.LLSDACSE1547:
	.section	.text._ZN8EmployeeC2ERKS_,"axG",@progbits,_ZN8EmployeeC5ERKS_,comdat
	.size	_ZN8EmployeeC2ERKS_, .-_ZN8EmployeeC2ERKS_
	.weak	_ZN8EmployeeC1ERKS_
	.set	_ZN8EmployeeC1ERKS_,_ZN8EmployeeC2ERKS_
	.section	.rodata
.LC6:
	.string	"Management"
.LC7:
	.string	"M001"
.LC8:
	.string	"John Doe"
.LC9:
	.string	"IT"
.LC10:
	.string	"T001"
.LC11:
	.string	"Alice Smith"
.LC12:
	.string	"T002"
.LC13:
	.string	"Bob Johnson"
.LC14:
	.string	"HR"
.LC15:
	.string	"M002"
.LC16:
	.string	"Jane Smith"
.LC17:
	.string	"T003"
.LC18:
	.string	"Carol Williams"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1539:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1539
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$1128, %rsp
	.cfi_offset 3, -24
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1121(%rbp), %rdx
	leaq	-320(%rbp), %rax
	leaq	.LC6(%rip), %rsi
	movq	%rax, %rdi
.LEHB26:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE26:
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1122(%rbp), %rdx
	leaq	-736(%rbp), %rax
	leaq	.LC7(%rip), %rsi
	movq	%rax, %rdi
.LEHB27:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE27:
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1123(%rbp), %rdx
	leaq	-848(%rbp), %rax
	leaq	.LC8(%rip), %rsi
	movq	%rax, %rdi
.LEHB28:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE28:
	leaq	-320(%rbp), %rcx
	leaq	-736(%rbp), %rdx
	leaq	-848(%rbp), %rsi
	leaq	-624(%rbp), %rax
	movq	%rax, %rdi
.LEHB29:
	call	_ZN7ManagerC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
.LEHE29:
	leaq	-848(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-736(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-320(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1121(%rbp), %rdx
	leaq	-320(%rbp), %rax
	leaq	.LC9(%rip), %rsi
	movq	%rax, %rdi
.LEHB30:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE30:
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1122(%rbp), %rdx
	leaq	-736(%rbp), %rax
	leaq	.LC10(%rip), %rsi
	movq	%rax, %rdi
.LEHB31:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE31:
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1123(%rbp), %rdx
	leaq	-848(%rbp), %rax
	leaq	.LC11(%rip), %rsi
	movq	%rax, %rdi
.LEHB32:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE32:
	leaq	-624(%rbp), %rdi
	leaq	-320(%rbp), %rcx
	leaq	-736(%rbp), %rdx
	leaq	-848(%rbp), %rsi
	leaq	-960(%rbp), %rax
	movq	%rdi, %r8
	movq	%rax, %rdi
.LEHB33:
	call	_ZN10TechnicianC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee
.LEHE33:
	leaq	-848(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-736(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-320(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1121(%rbp), %rdx
	leaq	-320(%rbp), %rax
	leaq	.LC9(%rip), %rsi
	movq	%rax, %rdi
.LEHB34:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE34:
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1122(%rbp), %rdx
	leaq	-736(%rbp), %rax
	leaq	.LC12(%rip), %rsi
	movq	%rax, %rdi
.LEHB35:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE35:
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1123(%rbp), %rdx
	leaq	-1056(%rbp), %rax
	leaq	.LC13(%rip), %rsi
	movq	%rax, %rdi
.LEHB36:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE36:
	leaq	-624(%rbp), %rdi
	leaq	-320(%rbp), %rcx
	leaq	-736(%rbp), %rdx
	leaq	-1056(%rbp), %rsi
	leaq	-848(%rbp), %rax
	movq	%rdi, %r8
	movq	%rax, %rdi
.LEHB37:
	call	_ZN10TechnicianC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee
.LEHE37:
	leaq	-1056(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-736(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-320(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1121(%rbp), %rdx
	leaq	-736(%rbp), %rax
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
.LEHB38:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE38:
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1122(%rbp), %rdx
	leaq	-1056(%rbp), %rax
	leaq	.LC15(%rip), %rsi
	movq	%rax, %rdi
.LEHB39:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE39:
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1123(%rbp), %rdx
	leaq	-1088(%rbp), %rax
	leaq	.LC16(%rip), %rsi
	movq	%rax, %rdi
.LEHB40:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE40:
	leaq	-736(%rbp), %rcx
	leaq	-1056(%rbp), %rdx
	leaq	-1088(%rbp), %rsi
	leaq	-320(%rbp), %rax
	movq	%rax, %rdi
.LEHB41:
	call	_ZN7ManagerC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
.LEHE41:
	leaq	-1088(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-1056(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-736(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1121(%rbp), %rdx
	leaq	-1056(%rbp), %rax
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
.LEHB42:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE42:
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1122(%rbp), %rdx
	leaq	-1088(%rbp), %rax
	leaq	.LC17(%rip), %rsi
	movq	%rax, %rdi
.LEHB43:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE43:
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-1123(%rbp), %rdx
	leaq	-1120(%rbp), %rax
	leaq	.LC18(%rip), %rsi
	movq	%rax, %rdi
.LEHB44:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE44:
	leaq	-320(%rbp), %rdi
	leaq	-1056(%rbp), %rcx
	leaq	-1088(%rbp), %rdx
	leaq	-1120(%rbp), %rsi
	leaq	-736(%rbp), %rax
	movq	%rdi, %r8
	movq	%rax, %rdi
.LEHB45:
	call	_ZN10TechnicianC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_P8Employee
.LEHE45:
	leaq	-1120(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-1088(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-1056(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-960(%rbp), %rdx
	leaq	-1056(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB46:
	call	_ZN8EmployeeC1ERKS_
.LEHE46:
	leaq	-1056(%rbp), %rdx
	leaq	-624(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB47:
	call	_ZN7Manager14add_technicianE8Employee
.LEHE47:
	leaq	-1056(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8EmployeeD1Ev
	leaq	-848(%rbp), %rdx
	leaq	-1056(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB48:
	call	_ZN8EmployeeC1ERKS_
.LEHE48:
	leaq	-1056(%rbp), %rdx
	leaq	-624(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB49:
	call	_ZN7Manager14add_technicianE8Employee
.LEHE49:
	leaq	-1056(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8EmployeeD1Ev
	leaq	-736(%rbp), %rdx
	leaq	-1056(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB50:
	call	_ZN8EmployeeC1ERKS_
.LEHE50:
	leaq	-1056(%rbp), %rdx
	leaq	-320(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB51:
	call	_ZN7Manager14add_technicianE8Employee
.LEHE51:
	leaq	-1056(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8EmployeeD1Ev
	leaq	-624(%rbp), %rax
	movq	%rax, %rdi
.LEHB52:
	call	_ZN7Manager17display_team_infoEv
	leaq	-320(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7Manager17display_team_infoEv
.LEHE52:
	movl	$0, %ebx
	leaq	-736(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN10TechnicianD1Ev
	leaq	-320(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7ManagerD1Ev
	leaq	-848(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN10TechnicianD1Ev
	leaq	-960(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN10TechnicianD1Ev
	leaq	-624(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7ManagerD1Ev
	movl	%ebx, %eax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L92
	jmp	.L117
.L96:
	endbr64
	movq	%rax, %rbx
	leaq	-848(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L65
.L95:
	endbr64
	movq	%rax, %rbx
.L65:
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-736(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L66
.L94:
	endbr64
	movq	%rax, %rbx
.L66:
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-320(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L67
.L93:
	endbr64
	movq	%rax, %rbx
.L67:
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB53:
	call	_Unwind_Resume@PLT
.L100:
	endbr64
	movq	%rax, %rbx
	leaq	-848(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L69
.L99:
	endbr64
	movq	%rax, %rbx
.L69:
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-736(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L70
.L98:
	endbr64
	movq	%rax, %rbx
.L70:
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-320(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L71
.L97:
	endbr64
	movq	%rax, %rbx
.L71:
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	jmp	.L72
.L104:
	endbr64
	movq	%rax, %rbx
	leaq	-1056(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L74
.L103:
	endbr64
	movq	%rax, %rbx
.L74:
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-736(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L75
.L102:
	endbr64
	movq	%rax, %rbx
.L75:
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-320(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L76
.L101:
	endbr64
	movq	%rax, %rbx
.L76:
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	jmp	.L77
.L108:
	endbr64
	movq	%rax, %rbx
	leaq	-1088(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L79
.L107:
	endbr64
	movq	%rax, %rbx
.L79:
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-1056(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L80
.L106:
	endbr64
	movq	%rax, %rbx
.L80:
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-736(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L81
.L105:
	endbr64
	movq	%rax, %rbx
.L81:
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	jmp	.L82
.L112:
	endbr64
	movq	%rax, %rbx
	leaq	-1120(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L84
.L111:
	endbr64
	movq	%rax, %rbx
.L84:
	leaq	-1123(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-1088(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L85
.L110:
	endbr64
	movq	%rax, %rbx
.L85:
	leaq	-1122(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-1056(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L86
.L109:
	endbr64
	movq	%rax, %rbx
.L86:
	leaq	-1121(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	jmp	.L87
.L114:
	endbr64
	movq	%rax, %rbx
	leaq	-1056(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8EmployeeD1Ev
	jmp	.L89
.L115:
	endbr64
	movq	%rax, %rbx
	leaq	-1056(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8EmployeeD1Ev
	jmp	.L89
.L116:
	endbr64
	movq	%rax, %rbx
	leaq	-1056(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8EmployeeD1Ev
	jmp	.L89
.L113:
	endbr64
	movq	%rax, %rbx
.L89:
	leaq	-736(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN10TechnicianD1Ev
.L87:
	leaq	-320(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7ManagerD1Ev
.L82:
	leaq	-848(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN10TechnicianD1Ev
.L77:
	leaq	-960(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN10TechnicianD1Ev
.L72:
	leaq	-624(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7ManagerD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE53:
.L117:
	call	__stack_chk_fail@PLT
.L92:
	addq	$1128, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1539:
	.section	.gcc_except_table,"a",@progbits
.LLSDA1539:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1539-.LLSDACSB1539
.LLSDACSB1539:
	.uleb128 .LEHB26-.LFB1539
	.uleb128 .LEHE26-.LEHB26
	.uleb128 .L93-.LFB1539
	.uleb128 0
	.uleb128 .LEHB27-.LFB1539
	.uleb128 .LEHE27-.LEHB27
	.uleb128 .L94-.LFB1539
	.uleb128 0
	.uleb128 .LEHB28-.LFB1539
	.uleb128 .LEHE28-.LEHB28
	.uleb128 .L95-.LFB1539
	.uleb128 0
	.uleb128 .LEHB29-.LFB1539
	.uleb128 .LEHE29-.LEHB29
	.uleb128 .L96-.LFB1539
	.uleb128 0
	.uleb128 .LEHB30-.LFB1539
	.uleb128 .LEHE30-.LEHB30
	.uleb128 .L97-.LFB1539
	.uleb128 0
	.uleb128 .LEHB31-.LFB1539
	.uleb128 .LEHE31-.LEHB31
	.uleb128 .L98-.LFB1539
	.uleb128 0
	.uleb128 .LEHB32-.LFB1539
	.uleb128 .LEHE32-.LEHB32
	.uleb128 .L99-.LFB1539
	.uleb128 0
	.uleb128 .LEHB33-.LFB1539
	.uleb128 .LEHE33-.LEHB33
	.uleb128 .L100-.LFB1539
	.uleb128 0
	.uleb128 .LEHB34-.LFB1539
	.uleb128 .LEHE34-.LEHB34
	.uleb128 .L101-.LFB1539
	.uleb128 0
	.uleb128 .LEHB35-.LFB1539
	.uleb128 .LEHE35-.LEHB35
	.uleb128 .L102-.LFB1539
	.uleb128 0
	.uleb128 .LEHB36-.LFB1539
	.uleb128 .LEHE36-.LEHB36
	.uleb128 .L103-.LFB1539
	.uleb128 0
	.uleb128 .LEHB37-.LFB1539
	.uleb128 .LEHE37-.LEHB37
	.uleb128 .L104-.LFB1539
	.uleb128 0
	.uleb128 .LEHB38-.LFB1539
	.uleb128 .LEHE38-.LEHB38
	.uleb128 .L105-.LFB1539
	.uleb128 0
	.uleb128 .LEHB39-.LFB1539
	.uleb128 .LEHE39-.LEHB39
	.uleb128 .L106-.LFB1539
	.uleb128 0
	.uleb128 .LEHB40-.LFB1539
	.uleb128 .LEHE40-.LEHB40
	.uleb128 .L107-.LFB1539
	.uleb128 0
	.uleb128 .LEHB41-.LFB1539
	.uleb128 .LEHE41-.LEHB41
	.uleb128 .L108-.LFB1539
	.uleb128 0
	.uleb128 .LEHB42-.LFB1539
	.uleb128 .LEHE42-.LEHB42
	.uleb128 .L109-.LFB1539
	.uleb128 0
	.uleb128 .LEHB43-.LFB1539
	.uleb128 .LEHE43-.LEHB43
	.uleb128 .L110-.LFB1539
	.uleb128 0
	.uleb128 .LEHB44-.LFB1539
	.uleb128 .LEHE44-.LEHB44
	.uleb128 .L111-.LFB1539
	.uleb128 0
	.uleb128 .LEHB45-.LFB1539
	.uleb128 .LEHE45-.LEHB45
	.uleb128 .L112-.LFB1539
	.uleb128 0
	.uleb128 .LEHB46-.LFB1539
	.uleb128 .LEHE46-.LEHB46
	.uleb128 .L113-.LFB1539
	.uleb128 0
	.uleb128 .LEHB47-.LFB1539
	.uleb128 .LEHE47-.LEHB47
	.uleb128 .L114-.LFB1539
	.uleb128 0
	.uleb128 .LEHB48-.LFB1539
	.uleb128 .LEHE48-.LEHB48
	.uleb128 .L113-.LFB1539
	.uleb128 0
	.uleb128 .LEHB49-.LFB1539
	.uleb128 .LEHE49-.LEHB49
	.uleb128 .L115-.LFB1539
	.uleb128 0
	.uleb128 .LEHB50-.LFB1539
	.uleb128 .LEHE50-.LEHB50
	.uleb128 .L113-.LFB1539
	.uleb128 0
	.uleb128 .LEHB51-.LFB1539
	.uleb128 .LEHE51-.LEHB51
	.uleb128 .L116-.LFB1539
	.uleb128 0
	.uleb128 .LEHB52-.LFB1539
	.uleb128 .LEHE52-.LEHB52
	.uleb128 .L113-.LFB1539
	.uleb128 0
	.uleb128 .LEHB53-.LFB1539
	.uleb128 .LEHE53-.LEHB53
	.uleb128 0
	.uleb128 0
.LLSDACSE1539:
	.text
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2050:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L120
	cmpl	$65535, -8(%rbp)
	jne	.L120
	leaq	_ZStL8__ioinit(%rip), %rdi
	call	_ZNSt8ios_base4InitC1Ev@PLT
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZStL8__ioinit(%rip), %rsi
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	__cxa_atexit@PLT
.L120:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2050:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB2051:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2051:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.hidden	__dso_handle
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
