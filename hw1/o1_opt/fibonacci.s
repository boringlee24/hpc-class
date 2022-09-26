	.file	"fibonacci.c"
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
	.globl	fib
	.type	fib, @function
fib:
.LFB21:
	.cfi_startproc
	movl	%edi, %eax
	cmpl	$1, %edi
	jle	.L10
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movl	%edi, %ebx
	leal	-1(%rdi), %edi
	call	fib
	movl	%eax, %ebp
	leal	-2(%rbx), %edi
	call	fib
	addl	%ebp, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 8
.L10:
	rep ret
	.cfi_endproc
.LFE21:
	.size	fib, .-fib
	.globl	return_function
	.type	return_function, @function
return_function:
.LFB22:
	.cfi_startproc
	movl	%edi, %eax
	ret
	.cfi_endproc
.LFE22:
	.size	return_function, .-return_function
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"Time for Fibo = %4.2f milliseconds\n"
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
	movl	$40, %edi
	call	fib
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
