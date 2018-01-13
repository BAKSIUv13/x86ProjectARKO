	section	.text

	global	x86_function

x86_function:

	push	rbp
	mov	rbp, rsp

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

;	rbx - imagePtr
;	r10d - actual X
;	r11d - actual Y
;	r12d - (mouseX - actual X)^2 
;	r13d - (mouseY - actual Y)^2
;	r14d - distance^2
;	r15


;------------------------------------------------------------------------------
	mov	rbx, rdi	; rbx = imagePtr
	mov	r11d, 1		; actual Y update
	xor	rax, rax

nextLine:

	mov	r10d, 1		; actual X update - nextLine

nextColumn:

; make distance

	neg	r10d
	neg	r11d

	lea	r12d, [edx + r10d]
	lea	r13d, [ecx + r11d]

	imul	r12d, r12d
	imul	r13d, r13d

	lea	r14d, [r12d + r13d]

	neg	r10d
	neg	r11d

	; now we have distance^2

	

; make sinus

	; do smth

; red
	
	; do smth
	;mov	[rbx], al
	inc	rbx

; green
	
	; do smth
	;mov	[rbx], al
	inc	rbx

; blue
	
	; do smth
	;mov	[rbx], al
	inc	rbx


; alpha
	
	; do smth
	inc rbx

; next pixel

	inc	r10d		; next pixel
	cmp	r10d, r8d
	jbe	nextColumn

	inc	r11d
	cmp	r11d, r9d
	jbe	nextLine

end:
;------------------------------------------------------------------------------
;	save registers

	pop	rbx
	pop	r15
	pop	r14
	pop	r13
	pop	r12

;------------------------------------------------------------------------------

	mov 	rsp, rbp
	pop 	rbp
	
	ret