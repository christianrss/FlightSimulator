; ObjectWindows - (C) Copyright 1991 by Borland International

;=============================================================================
;
;	This file contains proprietary information of Borland International.
;	Copying or reproduction without prior written approval is prohibited.
;
;=============================================================================

ifdef   __SMALL__
                .model  small
LDATA           equ     0
endif

ifdef   __MEDIUM__
                .model  medium
LDATA           equ     0
endif

ifdef   __COMPACT__
                .model  compact
LDATA           equ     1
endif

ifdef   __LARGE__
                .model  large
LDATA           equ     1
endif

ifdef	_CLASSDLL
FARVTBL		equ	1
ptrSize         equ     4
else
FARVTBL		equ	0
ptrSize         equ     2
endif

if      LDATA
LES_            equ     <les>
ES_             equ     <es:>
else
LES_            equ     <mov>
ES_             equ     <   >
endif

		.code

;==============================================================================

		public	_Ddispatch

if 	FARVTBL
_Ddispatch	proc	resPtr:DWORD,vptr:DWORD,id:WORD
else
_Ddispatch	proc	resPtr:DWORD,vptr: WORD,id:WORD
endif

		push	bp
		mov	bp, sp

		push	si
		push	di

if	FARVTBL
		les	bx, vptr		
else
		mov	bx, vptr
		push	ds
		pop	es
endif		

		std

;
; This is the loop that searches for a matching ID.
;
search_loop:	mov	cx, ES_[bx-ptrSize-2]	; get # of entries
		jcxz	search_next
;
; The table is below the # of entries, 6 bytes per entry; count is in CX.
;
		mov	dx, cx			; save the count
;
; Search this table for a matching ID.
;
		mov	ax, id
		lea	di, [bx-ptrSize-4]	; point at first ID
		repne	scasw
		je	search_match
;
; No luck with this class; see if it has a base class.
;
search_next:

if	FARVTBL
		les	bx, es:[bx-4]		; get base class link
		mov	ax, es
		or	ax, bx
else
		mov	bx, [bx-2]		; get base class link
		or	bx, bx
endif
		jnz	search_loop		; continue if non-zero
;
; No match; return a NULL pointer.
;
		les	di, resPtr
		xor	ax, ax
		cld
		stosw
		stosw
		stosw
		stosw

		jmp	SHORT done
;
; Here if we have a match; ES:[DI] points just below the matching ID.
;
search_match:	shl	dx, 1			; DX = 2 * count
		sub	bx, dx
		shl	cx, 1			; CX = 2 * count remaining
		sub	dx, cx
		shl	dx, 1			; DX = 4 * index of match
		add	dx, 2 + ptrSize
		sub	bx, dx

		mov	cx, ES_[bx]		; get the fn address
		mov	dx, es:[bx+2]

		les	di, resPtr

		cld
		xor	ax, ax
		stosw
		stosw
		mov	ax, cx
		stosw
		mov	ax, dx
		stosw

done:		pop	di
		pop	si

		pop	bp
		ret

_Ddispatch	endp

;==============================================================================
		end
