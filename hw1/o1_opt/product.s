	.file	"product.c"
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
	jle	.L6
	movl	$0, %eax
.L5:
	addl	$1, %eax
	cmpl	%eax, %esi
	jne	.L5
	imull	%edi, %eax
	ret
.L6:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE21:
	.size	product, .-product
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"Time for Prod = %4.2f milliseconds\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB22:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$0, %eax
	call	CLOCK
	movsd	%xmm0, 8(%rsp)
	movl	$100000000, %eax
.L9:
	subl	$1, %eax
	jne	.L9
	movl	$0, %eax
	call	CLOCK
	subsd	8(%rsp), %xmm0
	movl	$.LC1, %edi
	movl	$1, %eax
	call	printf
	movl	$784662528, %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE22:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	2696277389
	.long	1051772663
	.ident	"GCC: (GNU) 6.4.0"
	.section	.note.GNU-stack,"",@progbits
