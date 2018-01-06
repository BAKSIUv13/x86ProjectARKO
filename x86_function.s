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

	; rdi - resultImagePtr which point byte

	mov		al, 0

	mov		byte [rdi], al
	inc		rdi

	mov		byte [rdi], al
	inc		rdi

	mov		byte [rdi], al
	inc		rdi

	inc		rdi
	inc		rdi
	inc		rdi
	inc		rdi
	inc		rdi
	

	mov		byte [rdi], al
	inc		rdi

	mov		byte [rdi], al
	inc		rdi

	mov		byte [rdi], al
	inc		rdi

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