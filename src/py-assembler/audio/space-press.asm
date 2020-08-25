STR		#3 		$9FFF 	; switch to audio bank
STR		#0 		$A002 	; switch to oscillator 0
STR		#2 		$A003 	; switch to waveform register
STR		#%00	$A004 	; set to pulse
STR		#3 		$A003 	; switch to pulse width register
STR		#$A0	$A004 	; set to 50% (128)
STR		#1 		$A003 	; switch to lowpass register
STR		#100	$A004 	; set to 100
STR		#4 		$A003 	; switch to note register
STR		#49		$A004	; set note to 49 (C4)
STR		#3 		$9FFF 	; switch to audio bank
STR		#7		$A003	; switch to volume register

:LOOP
STR		#1 		$9FFF 	; switch to keyboard bank
LOD		$A00A	R0		; 1 if spacebar is pressed 0 if not
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:ON		; if 1 jump to volume on
BRAN	Z		:OFF	; if 0 jump to volume off

:ON
STR		#3 		$9FFF 	; switch to audio bank
STR		#$40	$A004	; set volume to 64
JMP		:LOOP

:OFF
STR		#3 		$9FFF 	; switch to audio bank
STR		#0		$A004	; set volume to 0
JMP		:LOOP
