JSR		:MS				; 5
JSR		:MS				; 5 ; second one breaks this (log PC for debug)

NOP

:MS
LOD		#249	R3		; 2

:LOOP

NOP						; 1
NOP						; 1
NOP						; 1
NOP						; 1
DEC		R3				; 1
BRAN	Z		:LOOP	; 3/1

RET						; 3
