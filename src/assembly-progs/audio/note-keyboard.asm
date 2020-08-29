; WIP

STR		#3 		$1FFF 	; switch to audio bank
STR		#0 		$2002 	; switch to oscillator 0
STR		#2 		$2003 	; switch to waveform register
STR		#%00	$2004 	; set to pulse
STR		#3 		$2003 	; switch to pulse width register
STR		#$80	$2004 	; set to 50% (128)
STR		#1 		$2003 	; switch to lowpass register
STR		#100	$2004 	; set to 100
STR		#4 		$2003 	; switch to note register
STR		#49		$2004	; set note to 49 (C4)
STR		#3 		$1FFF 	; switch to audio bank
STR		#7		$2003	; switch to volume register

:LOOP
STR		#1 		$1FFF 	; switch to keyboard bank
LOD		$2024	R0		; 1 if Z is pressed 0 if not
CMP		R0		#1		; Check if R0 is 1
JSR		:C				; If it is play C

LOD		$201D	R0		; 1 if S is pressed 0 if not
CMP		R0		#1		; Check if R0 is 1
JSR		:C#				; If it is play C#

LOD		$2022	R0		; 1 if X is pressed 0 if not
CMP		R0		#1		; Check if R0 is 1
JSR		:D				; If it is play D

BRA		Z		:ON		; if 1 jump to volume on
BRAN	Z		:OFF	; if 0 jump to volume off

:ON
STR		#3 		$1FFF 	; switch to audio bank
STR		#$40	$2004	; set volume to 64
JMP		:LOOP

:OFF
STR		#3 		$1FFF 	; switch to audio bank
STR		#0		$2004	; set volume to 64
JMP		:LOOP

:C

:C#

:D

:D#

:E

:F

:F#

:G

:G#

:A

:A#

:B
