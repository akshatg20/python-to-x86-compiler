	.file	"test9.cpp"
	.text
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.text._ZN17ShiftReduceParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE,"axG",@progbits,_ZN17ShiftReduceParserC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE,comdat
	.align 2
	.weak	_ZN17ShiftReduceParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.type	_ZN17ShiftReduceParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, @function
_ZN17ShiftReduceParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE:
.LFB1523:
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
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1523:
	.size	_ZN17ShiftReduceParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, .-_ZN17ShiftReduceParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.weak	_ZN17ShiftReduceParserC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.set	_ZN17ShiftReduceParserC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE,_ZN17ShiftReduceParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.section	.text._ZN17ShiftReduceParserD2Ev,"axG",@progbits,_ZN17ShiftReduceParserD5Ev,comdat
	.align 2
	.weak	_ZN17ShiftReduceParserD2Ev
	.type	_ZN17ShiftReduceParserD2Ev, @function
_ZN17ShiftReduceParserD2Ev:
.LFB1527:
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
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1527:
	.size	_ZN17ShiftReduceParserD2Ev, .-_ZN17ShiftReduceParserD2Ev
	.weak	_ZN17ShiftReduceParserD1Ev
	.set	_ZN17ShiftReduceParserD1Ev,_ZN17ShiftReduceParserD2Ev
	.section	.text._ZN9CLRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_,"axG",@progbits,_ZN9CLRParserC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_,comdat
	.align 2
	.weak	_ZN9CLRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_
	.type	_ZN9CLRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_, @function
_ZN9CLRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_:
.LFB1532:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1532
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%rdx, -88(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-72(%rbp), %rbx
	movq	-88(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB0:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE0:
	leaq	-64(%rbp), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB1:
	call	_ZN17ShiftReduceParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE1:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-72(%rbp), %rax
	leaq	32(%rax), %rdx
	movq	-80(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
.LEHB2:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE2:
	jmp	.L9
.L7:
	endbr64
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB3:
	call	_Unwind_Resume@PLT
.L8:
	endbr64
	movq	%rax, %rbx
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN17ShiftReduceParserD2Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE3:
.L9:
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L6
	call	__stack_chk_fail@PLT
.L6:
	addq	$88, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1532:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZN9CLRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_,"aG",@progbits,_ZN9CLRParserC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_,comdat
.LLSDA1532:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1532-.LLSDACSB1532
.LLSDACSB1532:
	.uleb128 .LEHB0-.LFB1532
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1532
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L7-.LFB1532
	.uleb128 0
	.uleb128 .LEHB2-.LFB1532
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L8-.LFB1532
	.uleb128 0
	.uleb128 .LEHB3-.LFB1532
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSE1532:
	.section	.text._ZN9CLRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_,"axG",@progbits,_ZN9CLRParserC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_,comdat
	.size	_ZN9CLRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_, .-_ZN9CLRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_
	.weak	_ZN9CLRParserC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_
	.set	_ZN9CLRParserC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_,_ZN9CLRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_
	.section	.text._ZN9CLRParserD2Ev,"axG",@progbits,_ZN9CLRParserD5Ev,comdat
	.align 2
	.weak	_ZN9CLRParserD2Ev
	.type	_ZN9CLRParserD2Ev, @function
_ZN9CLRParserD2Ev:
.LFB1536:
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
	addq	$32, %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN17ShiftReduceParserD2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1536:
	.size	_ZN9CLRParserD2Ev, .-_ZN9CLRParserD2Ev
	.weak	_ZN9CLRParserD1Ev
	.set	_ZN9CLRParserD1Ev,_ZN9CLRParserD2Ev
	.section	.text._ZN10LALRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,"axG",@progbits,_ZN10LALRParserC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,comdat
	.align 2
	.weak	_ZN10LALRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
	.type	_ZN10LALRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_, @function
_ZN10LALRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_:
.LFB1538:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1538
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$120, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -104(%rbp)
	movq	%rsi, -112(%rbp)
	movq	%rdx, -120(%rbp)
	movq	%rcx, -128(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-104(%rbp), %rbx
	movq	-128(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB4:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE4:
	movq	-120(%rbp), %rdx
	leaq	-96(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB5:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE5:
	leaq	-64(%rbp), %rdx
	leaq	-96(%rbp), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
.LEHB6:
	call	_ZN9CLRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_
.LEHE6:
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	-104(%rbp), %rax
	leaq	64(%rax), %rdx
	movq	-112(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
.LEHB7:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@PLT
.LEHE7:
	jmp	.L19
.L17:
	endbr64
	movq	%rax, %rbx
	leaq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L13
.L16:
	endbr64
	movq	%rax, %rbx
.L13:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB8:
	call	_Unwind_Resume@PLT
.L18:
	endbr64
	movq	%rax, %rbx
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN9CLRParserD2Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE8:
.L19:
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L15
	call	__stack_chk_fail@PLT
.L15:
	addq	$120, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1538:
	.section	.gcc_except_table._ZN10LALRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,"aG",@progbits,_ZN10LALRParserC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,comdat
.LLSDA1538:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1538-.LLSDACSB1538
.LLSDACSB1538:
	.uleb128 .LEHB4-.LFB1538
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB5-.LFB1538
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L16-.LFB1538
	.uleb128 0
	.uleb128 .LEHB6-.LFB1538
	.uleb128 .LEHE6-.LEHB6
	.uleb128 .L17-.LFB1538
	.uleb128 0
	.uleb128 .LEHB7-.LFB1538
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L18-.LFB1538
	.uleb128 0
	.uleb128 .LEHB8-.LFB1538
	.uleb128 .LEHE8-.LEHB8
	.uleb128 0
	.uleb128 0
.LLSDACSE1538:
	.section	.text._ZN10LALRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,"axG",@progbits,_ZN10LALRParserC5ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,comdat
	.size	_ZN10LALRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_, .-_ZN10LALRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
	.weak	_ZN10LALRParserC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
	.set	_ZN10LALRParserC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_,_ZN10LALRParserC2ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
	.section	.rodata
.LC0:
	.string	"SLR name:"
.LC1:
	.string	"CLR name:"
.LC2:
	.string	"LALR name:"
	.section	.text._ZN10LALRParser10print_nameEv,"axG",@progbits,_ZN10LALRParser10print_nameEv,comdat
	.align 2
	.weak	_ZN10LALRParser10print_nameEv
	.type	_ZN10LALRParser10print_nameEv, @function
_ZN10LALRParser10print_nameEv:
.LFB1540:
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
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rdi
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
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	movq	-8(%rbp), %rax
	addq	$32, %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rdi
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
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	movq	-8(%rbp), %rax
	addq	$64, %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rdi
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
.LFE1540:
	.size	_ZN10LALRParser10print_nameEv, .-_ZN10LALRParser10print_nameEv
	.section	.text._ZN10LALRParserD2Ev,"axG",@progbits,_ZN10LALRParserD5Ev,comdat
	.align 2
	.weak	_ZN10LALRParserD2Ev
	.type	_ZN10LALRParserD2Ev, @function
_ZN10LALRParserD2Ev:
.LFB1543:
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
	movq	%rax, %rdi
	call	_ZN9CLRParserD2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1543:
	.size	_ZN10LALRParserD2Ev, .-_ZN10LALRParserD2Ev
	.weak	_ZN10LALRParserD1Ev
	.set	_ZN10LALRParserD1Ev,_ZN10LALRParserD2Ev
	.section	.rodata
.LC3:
	.string	"Shift-Reduce"
.LC4:
	.string	"CLR"
.LC5:
	.string	"LALR"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1541:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1541
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$232, %rsp
	.cfi_offset 3, -24
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-225(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-225(%rbp), %rdx
	leaq	-160(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
.LEHB9:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE9:
	leaq	-226(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-226(%rbp), %rdx
	leaq	-192(%rbp), %rax
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
.LEHB10:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE10:
	leaq	-227(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-227(%rbp), %rdx
	leaq	-224(%rbp), %rax
	leaq	.LC5(%rip), %rsi
	movq	%rax, %rdi
.LEHB11:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_@PLT
.LEHE11:
	leaq	-160(%rbp), %rcx
	leaq	-192(%rbp), %rdx
	leaq	-224(%rbp), %rsi
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
.LEHB12:
	call	_ZN10LALRParserC1ENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_S5_
.LEHE12:
	leaq	-224(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-227(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-192(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-226(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	leaq	-225(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
.LEHB13:
	call	_ZN10LALRParser10print_nameEv
.LEHE13:
	movl	$0, %ebx
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN10LALRParserD1Ev
	movl	%ebx, %eax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L29
	jmp	.L35
.L33:
	endbr64
	movq	%rax, %rbx
	leaq	-224(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L25
.L32:
	endbr64
	movq	%rax, %rbx
.L25:
	leaq	-227(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-192(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L26
.L31:
	endbr64
	movq	%rax, %rbx
.L26:
	leaq	-226(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	leaq	-160(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	jmp	.L27
.L30:
	endbr64
	movq	%rax, %rbx
.L27:
	leaq	-225(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB14:
	call	_Unwind_Resume@PLT
.L34:
	endbr64
	movq	%rax, %rbx
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN10LALRParserD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE14:
.L35:
	call	__stack_chk_fail@PLT
.L29:
	addq	$232, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1541:
	.section	.gcc_except_table,"a",@progbits
.LLSDA1541:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1541-.LLSDACSB1541
.LLSDACSB1541:
	.uleb128 .LEHB9-.LFB1541
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L30-.LFB1541
	.uleb128 0
	.uleb128 .LEHB10-.LFB1541
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L31-.LFB1541
	.uleb128 0
	.uleb128 .LEHB11-.LFB1541
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L32-.LFB1541
	.uleb128 0
	.uleb128 .LEHB12-.LFB1541
	.uleb128 .LEHE12-.LEHB12
	.uleb128 .L33-.LFB1541
	.uleb128 0
	.uleb128 .LEHB13-.LFB1541
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L34-.LFB1541
	.uleb128 0
	.uleb128 .LEHB14-.LFB1541
	.uleb128 .LEHE14-.LEHB14
	.uleb128 0
	.uleb128 0
.LLSDACSE1541:
	.text
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2037:
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
	jne	.L38
	cmpl	$65535, -8(%rbp)
	jne	.L38
	leaq	_ZStL8__ioinit(%rip), %rdi
	call	_ZNSt8ios_base4InitC1Ev@PLT
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZStL8__ioinit(%rip), %rsi
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	__cxa_atexit@PLT
.L38:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2037:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB2038:
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
.LFE2038:
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
