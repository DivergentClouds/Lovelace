STR		#3 		$DFFF 	; switch to audio bank
STR		#0 		$E002 	; switch to oscillator 0
STR		#2 		$E003 	; switch to waveform register
STR		#%00	$E004 	; set to pulse
STR		#3 		$E003 	; switch to pulse width register
STR		#80		$E004 	; set to 50% (128)
STR		#1 		$E003 	; switch to lowpass register
STR		#100	$E004 	; set to 100
STR		#4 		$E003 	; switch to note register
STR		#49		$E004	; set note to 49 (C4)
STR		#3 		$DFFF 	; switch to audio bank
STR		#7		$E003	; switch to volume register
LOD		#$E0	ACC

:LOOP
STR		#1 		$DFFF 	; switch to keyboard bank
LOD		$E00A	R0		; 1 if spacebar is pressed 0 if not
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:ON		; if 1 jump to volume on
BRAN	Z		:OFF	; if 0 jump to volume off

:ON
STR		#3 		$DFFF 	; switch to audio bank
STR		#3 		$E003 	; switch to pulse width register
ADD		#1
STR		ACC		$E004
STR		#7		$E003	; switch to volume register
STR		#$40	$E004	; set volume to 64
JMP		:LOOP

:OFF
STR		#3 		$DFFF 	; switch to audio bank
STR		#0		$E004	; set volume to 0
JMP		:LOOP
