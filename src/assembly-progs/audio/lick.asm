STR		#3 		$9FFF 	; switch from rom bank to audio bank
STR		#0 		$A001 	; switch to oscillator 0
STR		#2 		$A002 	; switch to waveform register
STR		#%00	$A003 	; set to pulse
STR		#3 		$A002 	; switch to pulse width register
STR		#$A0	$A003 	; set to 50% (128)
STR		#7		$A002	; switch to volume register
STR		#$40	$A003	; set volume to 64
STR		#1 		$A002 	; switch to lowpass register
STR		#100	$A003 	; set to 100

STR		#4 		$A002 	; switch to note register
STR		#49		$A003	; set note to 49 (C4)
JSR :200MS

STR		#4 		$A002 	; switch to note register
STR		#51		$A003	; set note to 51 (D4)
JSR 	:200MS

STR		#4 		$A002 	; switch to note register
STR		#52		$A003	; set note to 52 (D#4)
JSR 	:200MS

STR		#4 		$A002 	; switch to note register
STR		#54		$A003	; set note to 54 (F4)
JSR		:200MS

STR		#4 		$A002 	; switch to note register
STR		#51		$A003	; set note to 51 (D4)
JSR :200MS
JSR :200MS

STR		#4 		$A002 	; switch to note register
STR		#47		$A003	; set note to 47 (A#4)
JSR :200MS

STR		#4 		$A002 	; switch to note register
STR		#49		$A003	; set note to 49 (C4)
JSR :200MS
JSR :200MS
JSR :200MS

QUIT

:200MS
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

:LOOP

NOP						; 1
NOP						; 1
NOP						; 1
NOP						; 1
DEC		R3				; 1
BRAN	Z		:LOOP	; 3/1

RET						; 3
