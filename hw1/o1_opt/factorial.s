	.file	"factorial.c"
	.text
	.globl	CLOCK
	.type	CLOCK, @function
CLOCK:
.LFB20:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%rsp, %rsi
	movl	$1, %edi
	call	clock_gettime
	imulq	$1000, (%rsp), %rax
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	8(%rsp), %xmm1
	mulsd	.LC0(%rip), %xmm1
	addsd	%xmm1, %xmm0
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE20:
	.size	CLOCK, .-CLOCK
	.globl	product
	.type	product, @function
product:
.LFB21:
	.cfi_startproc
	testl	%esi, %esi
	je	.L6
	movl	%esi, %ecx
	movl	$0, %edx
.L5:
	addl	$1, %edx
	cmpl	%edx, %ecx
	jne	.L5
	movl	%esi, %eax
	imull	%edi, %eax
	ret
.L6:
	movl	%esi, %eax
	ret
	.cfi_endproc
.LFE21:
	.size	product, .-product
	.globl	factorial
	.type	factorial, @function
factorial:
.LFB22:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	%edi, %ebx
	testl	%edi, %edi
	je	.L9
	cmpl	$1, %edi
	je	.L9
	leal	-1(%rdi), %edi
	call	factorial
	testl	%eax, %eax
	je	.L11
	movl	%eax, %ecx
	movl	$0, %edx
.L10:
	addl	$1, %edx
	cmpl	%edx, %ecx
	jne	.L10
	imull	%eax, %ebx
.L9:
	movl	%ebx, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L11:
	.cfi_restore_state
	movl	%eax, %ebx
	jmp	.L9
	.cfi_endproc
.LFE22:
	.size	factorial, .-factorial
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"Time for Facto = %4.2f milliseconds\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movl	$0, %eax
	call	CLOCK
	movsd	%xmm0, 8(%rsp)
	movl	$14, %edi
	call	factorial
	movl	%eax, %ebx
	movl	$0, %eax
	call	CLOCK
	subsd	8(%rsp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	movl	%ebx, %eax
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	2696277389
	.long	1051772663
	.ident	"GCC: (GNU) 6.4.0"
	.section	.note.GNU-stack,"",@progbits
