STR		#3 		$3FFF 	; switch from rom bank to audio bank
STR		#0 		$4001 	; switch to oscillator 0
STR		#2 		$4002 	; switch to waveform register
STR		#%11	$4003 	; set to noise
STR		#3 		$4002 	; switch to pulse width register
STR		#$80	$4003 	; set to 50%

:LOOP
STR		#7		$4002	; switch to volume register
STR		#$40	$4003	; set volume to 64
STR		#4 		$4002 	; switch to note register
STR		#13		$4003	; set note to 13 (C1)
JSR		:250MS
STR		#7		$4002	; switch to volume register
STR		#$0		$4003	; set volume to 0
JSR		:250MS
JSR		:250MS
JMP :LOOP


QUIT

:250MS
JSR		:50MS
JSR		:50MS
JSR		:50MS
JSR		:50MS
JSR		:50MS
RET

:50MS
JSR		:5MS
JSR		:5MS
JSR		:5MS
JSR		:5MS
JSR		:5MS
JSR		:5MS
JSR		:5MS
JSR		:5MS
JSR		:5MS
JSR		:5MS
RET

:5MS
JSR		:MS
JSR		:MS
JSR		:MS
JSR		:MS
JSR		:MS
RET

:MS
LOD		#249	R3		; 2

:TLOOP

NOP						; 1
NOP						; 1
NOP						; 1
NOP						; 1
DEC		R3				; 1
BRAN	Z		:TLOOP	; 3/1

RET						; 3
