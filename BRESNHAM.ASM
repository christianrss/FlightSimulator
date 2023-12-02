	.MODEL large
	.CODE
	PUBLIC _linedraw
_linedraw PROC
	ARG			x1:WORD,y1:WORD,x2:WORD,y2:WORD,color:WORD,\
		scr_off:WORD,scr_seg:WORD
	LOCAL		y_unit:WORD,x_unit:WORD,xdiff:WORD,ydiff:WORD,\
		error_term:WORD=AUTO_SIZE

	push		bp
	mov			bp,sp
	sub			sp,AUTO_SIZE
	mov			ax,scr_seg		; Colocar segmento da tela em AX
	mov			es,ax
	mov			ax,y1			; Colocar y1 em AX
	mov			dx,320			; Multiplicar por 320
	mul			dx
	add			ax,x1			; E adicionar x1 para offset do pixel
	add			ax,scr_off		; Adiciona offset da tela
	mov			bx,ax			; Mover offset para BX
init_line:
	mov			dx,color		; Colocar cor do pixel em DX
	mov			error_term,0	; Inicializar termo de erro
	mov			ax,y2			; Determinar sinal de y2-y1
	sub			ax,y1
	jns			ypos			; Se positivo, saltar
	mov			y_unit,-320		; Se negativo, tratar inclinacao negativa
	neg			ax				; Obter valor absoluto de YDIFF
	mov 		ydiff,ax		; E armazenar na memoria
	jmp			next
ypos:
	mov			y_unit,320		; Tratar inclinacao positiva
	mov			ydiff,ax		; Armazenar YDIFF na memoria
next:
	mov 		ax,x2			; Determinar sinal de x2-x1
	sub			ax,x1
	jns			xpos			; Se positivo, saltar
	mov			x_unit,-1		; Se negativo, tratar inclinacao negativa
	neg			ax				; Obter valor absolute de XDIFF
	mov			xdiff,ax		; E armazenar na memoria
	jmp			next2
xpos:
	mov			x_unit,1		; Tratar inclinacao positiva
	mov			xdiff,ax		; Armazenar XDIFF na memoria
next2:
	cmp			ax,ydiff		; Comparar XDIFF (em AX) e YDIFF
	jc			yline			; Se XDIFF<YDIFF entao contar na dimensao Y
	jmp			xline			; Se negativo, contar na dimensao X
xline:
	; inclinacao menor que 1, incrementar na dimencao X
	mov cx,xdiff				; Colocar tamanho da reta em CX para contar
	inc	cx
xline1:
	mov es:[bx],dl				; Desenhar proximo ponto da reta
	add	bx,x_unit				; Apontar offset para proximo pixel na direcao X
	mov	ax,error_term			; Verificar necessidade de movimentacao na direcao Y
	add	ax,ydiff
	mov	error_term,ax
	sub	ax,xdiff
	jc	xline2					; Se negativo, continuar
	mov	error_term,ax
	add	bx,y_unit				; Se positivo, mover 1 pixel para cima ou para baixo
xline2:
	loop xline1					; Loop ate contador (em cx) completar
	jmp  linedone
yline:
	; Contar na dimensao Y
	mov cx,ydiff				; Colocar tamanho da reta em CX
	inc cx
yline1:
	mov	es:[bx],dl				; Desenhar proximo ponto da reta
	add	bx,y_unit				; Apontar offset para proximo pixel na direcao Y
	mov ax,error_term			; Verificar necessidade de movimentacao na direcao X
	add ax,xdiff
	mov error_term,ax
	sub ax,ydiff
	jc 	yline2					; Se negativo, continuar
	mov	error_term,ax
	add bx,x_unit
yline2:
	loop yline1					; Loop ate contador (em CX) completar
linedone:
	mov sp,bp					; Terminado!
	pop	bp
	ret
_linedraw	ENDP
END

