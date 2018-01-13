	section		.text

	global		x86_function

x86_function:

	push		rbp
	mov		rbp, rsp

	sub		rsp, 8

;------------------------------------------------------------------------------
;	save registers

	push		r12
	push		r13
	push		r14
	push		r15
	push		rbx

;------------------------------------------------------------------------------

;	rdi - resultImagePtr
;	rsi - image2Ptr
;	edx - mouseX
;	ecx - mouseY
;	r8d - width
;	r9d - height
	%idefine sinusRatio [rbp + 16]

;	r10d - actual X
;	r11d - actual Y
;	r12d - (mouseX - actual X)^2 
;	r13d - (mouseY - actual Y)^2
;	r14d - distance^2
;	r15d - colour from Im1
;	ebx  - colour from Im2


;	xmm1 - 1.0
;	xmm2 - 2.0
;	xmm3 - 1 + sinus
;	xmm6 - 1 - sinus
;	xmm4 - distance
;	xmm5 - sinus
;	xmm7 - colour from Im1
;	xmm8 - colour from Im2
; 	xmm9 - sinusRatio

;------------------------------------------------------------------------------
	finit

	mov		r11d, 1		; actual Y update

	cvtsi2sd	xmm1, r11d 	; xmm1 - 1.0
	movsd		xmm2, xmm1
	addsd		xmm2, xmm1 	; xmm2 - 2.0


nextLine:

	mov		r10d, 1		; actual X update - nextLine

nextColumn:

; make distance

	neg		r10d
	neg		r11d

	lea		r12d, [edx + r10d]
	lea		r13d, [ecx + r11d]

	imul		r12d, r12d
	imul		r13d, r13d

	lea		r14d, [r12d + r13d]

	neg		r10d
	neg		r11d

	; now we have distance^2

	

	cvtsi2sd	xmm4, r14d	; xmm13 = (double)r8d
	sqrtsd		xmm4, xmm4
	
	; now we have distance - argument to sinus

; make sinus

	
	mov 		rax, sinusRatio
	cvtsi2sd	xmm9, eax

	divsd 		xmm4, xmm9


	movq		qword [rbp - 8], xmm4
	fld		qword [rbp - 8]
	fsin
	fstp		qword [rbp - 8]
	movq		xmm5, qword [rbp - 8]

	; now i have sinus in xmm5


	movsd 		xmm3, xmm1
	movsd		xmm6, xmm1

	addsd 		xmm3, xmm5
	subsd 		xmm6, xmm5


; red
	; get byte from picture

	mov 		al, [rdi]
	mov 		ah, [rsi]

	; extend byto to 32 bits

	movzx		r15d, al
	movzx 		ebx, ah

	cvtsi2sd	xmm7, r15d
	cvtsi2sd	xmm8, ebx

	mulsd 		xmm7, xmm3
	mulsd 		xmm8, xmm6

	addsd 		xmm7, xmm8

	divsd 		xmm7, xmm2

	cvtsd2si	rax, xmm7

	; send al
	mov		[rdi], al
	inc		rdi
	inc		rsi

; green
		; get byte from picture

	mov 		al, [rdi]
	mov 		ah, [rsi]

	; extend byto to 32 bits

	movzx		r15d, al
	movzx 		ebx, ah

	cvtsi2sd	xmm7, r15d
	cvtsi2sd	xmm8, ebx

	mulsd 		xmm7, xmm3
	mulsd 		xmm8, xmm6

	addsd 		xmm7, xmm8

	divsd 		xmm7, xmm2

	cvtsd2si	rax, xmm7
	
	
	; send al
	mov		[rdi], al
	inc		rdi
	inc		rsi

; blue
		; get byte from picture

	mov 		al, [rdi]
	mov 		ah, [rsi]

	; extend byto to 32 bits

	movzx		r15d, al
	movzx 		ebx, ah

	cvtsi2sd	xmm7, r15d
	cvtsi2sd	xmm8, ebx

	mulsd 		xmm7, xmm3
	mulsd 		xmm8, xmm6

	addsd 		xmm7, xmm8

	divsd 		xmm7, xmm2

	cvtsd2si	rax, xmm7
	
	; send al
	mov		[rdi], al
	inc		rdi
	inc		rsi

; alpha
	
	; do smth
	inc 		rdi
	inc		rsi

; next pixel

	inc		r10d		; next pixel
	cmp		r10d, r8d
	jbe		nextColumn

	inc		r11d
	cmp		r11d, r9d
	jbe		nextLine

end:
;------------------------------------------------------------------------------
;	save registers

	pop		rbx
	pop		r15
	pop		r14
	pop		r13
	pop		r12

;------------------------------------------------------------------------------

	mov 		rsp, rbp
	pop 		rbp
	
	ret