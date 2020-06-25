STR		#3 		$7FFF 	; switch to audio bank
STR		#0 		$8002 	; switch to oscillator 0
STR		#2 		$8003 	; switch to waveform register
STR		#%00	$8004 	; set to pulse
STR		#3 		$8003 	; switch to pulse width register
STR		#$80	$8004 	; set to 50% (128)
STR		#1 		$8003 	; switch to lowpass register
STR		#100	$8004 	; set to 100
STR		#4 		$8003 	; switch to note register
STR		#49		$8004	; set note to 49 (C4)
STR		#3 		$7FFF 	; switch to audio bank
STR		#7		$8003	; switch to volume register

:LOOP
STR		#1 		$7FFF 	; switch to keyboard bank
LOD		$800A	R0		; 1 if spacebar is pressed 0 if not
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:ON		; if 1 jump to volume on
BRAN	Z		:OFF	; if 0 jump to volume off

:ON
STR		#3 		$7FFF 	; switch to audio bank
STR		#$40	$8004	; set volume to 64
JMP		:LOOP

:OFF
STR		#3 		$7FFF 	; switch to audio bank
STR		#0		$8004	; set volume to 0
JMP		:LOOP
