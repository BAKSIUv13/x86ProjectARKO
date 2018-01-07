	section	.text

	global	x86_function

x86_function:

	push	rbp
	mov		rbp, rsp

;------------------------------------------------------------------------------
;	save registers

	push	r12
	push	r13
	push	r14
	push	r15
	push	rbx

;------------------------------------------------------------------------------

;	rdi - resultImagePtr
;	rsi - image2Ptr
;	edx - mouseX
;	ecx - mouseY
;	r8d - width
;	r9d - height
	%idefine sinusRatio [rbp + 16]

;	r10
;	r11
;	r12
;	r13
;	r14
;	r15


;------------------------------------------------------------------------------
	
	;

;------------------------------------------------------------------------------
;	save registers

	pop		rbx
	pop		r15
	pop		r14
	pop		r13
	pop		r12

;------------------------------------------------------------------------------

	mov 	rsp, rbp
	pop 	rbp
	
	ret