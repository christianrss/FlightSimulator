; SCREEN.ASM

	.MODEL large
	.CODE
	PUBLIC _cls,_setmode,_setpalettex;

SCREEN_WIDTH 	equ 320
SCREEN_HEIGHT 	equ 200

_setpalettex PROC
	ARG 	regs:DWORD
	push	bp
	mov		bp,sp
	les		dx,regs
	mov		ah,10h
	mov		al,12h
	mov		bx,0
	mov		cx,100h
	int 	10h
	pop		bp
	ret
_setpalettex ENDP

; setpalette (char far *color_regs, int firstreg, int numregs)
;	Atribui a registradores de cor VGA, comecando com FIRSTREG e
;		continuando por NUMEROS, os valroes de cor em COLOR_REGS
_setpalette PROC
	ARG 	regoff:WORD,regseg:WORD,firstreg:WORD,numregs:WORD
	push    bp			; Salvar BP
	mov		bp,sp		; Configurar ponteiro da pilha
	mov		dx,es
	push	dx
	mov		dx,regseg	; Apontar ES:SX para os registradores da paleta
	mov		es,dx
	mov		ah,10h		; Especificar a funcao 10h da BIOS
	mov		al,12h		; ... e subfuncao 12h
	mov		bx,0		; Comecar com o primeiro registro
	mov		cx,100h		; Ativar os (100h) registros
	mov		dx,regoff
	int		10h			; Chamar a BIOS do video
	pop		dx
	mov		es,dx
	pop		bp			; Restaurar BP
	ret
_setpalette ENDP

; cls(char far *screen_addr)
; 	Limpa a memoria de video ou o buffer de tela em
; 	SCREEN_ADDR com zeros

_cls PROC
	ARG 	scr_off:WORD, scr_seg:WORD
	push    bp								; Salvar BP
	mov		bp,sp							; Inicializar ponteiro da pilha
	push	di								; Salvar registrador DI
	mov		di,scr_seg
	mov     es,di                           ; Apontar ES:DI para a tela
	mov		di,scr_off
	mov		cx,SCREEN_WIDTH/2*SCREEN_HEIGHT ; Contar os pixels
	mov 	ax,0							; Armazenar valores zero...
	rep		stosw							; ... por toda a memoria de video
	pop 	di								; Restaurar DI
	pop		bp							   	; Restaurar BP
	ret
_cls ENDP

; setmode(int mode)
;   Ativa o adaptador VGA para o modo MODE da BIOS
_setmode PROC
ARG 	mode:WORD
push 	bp	; Salvar BP
mov 	bp,sp	; Inicializar ponteiro da pilha
mov 	ax,mode	; AL = modo de video
mov		ah,0	; AH = numero da funcao
int		10h	; Chamar interrupcao 10h
pop		bp	; Restaurar BP
ret
_setmode ENDP



END