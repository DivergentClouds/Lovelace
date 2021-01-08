STR		#3 		$DFFF 	; switch to audio bank
STR		#0 		$E002 	; switch to oscillator 0
STR		#2 		$E003 	; switch to waveform register
STR		#%00	$E004 	; set to pulse
STR		#3 		$E003 	; switch to pulse width register
STR		#80		$E004 	; set to 50% (128)

:LOOP
STR		#1 		$DFFF	; switch to keyboard bank

LOD		$E024	R0		; 1 if Z is pressed
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:C		; if 1 jump to volume on

LOD		$E01D	R0		; 1 if S is pressed
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:C#		; if 1 jump to volume on

LOD		$E022	R0		; 1 if X is pressed
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:D		; if 1 jump to volume on

LOD		$E00E	R0		; 1 if D is pressed
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:D#		; if 1 jump to volume on

LOD		$E00D	R0		; 1 if C is pressed
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:E		; if 1 jump to volume on

LOD		$E020	R0		; 1 if V is pressed
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:F		; if 1 jump to volume on

LOD		$E011	R0		; 1 if G is pressed
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:F#		; if 1 jump to volume on

LOD		$E00C	R0		; 1 if B is pressed
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:G		; if 1 jump to volume on

LOD		$E012	R0		; 1 if H is pressed
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:G#		; if 1 jump to volume on

LOD		$E018	R0		; 1 if N is pressed
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:A		; if 1 jump to volume on

LOD		$E014	R0		; 1 if J is pressed
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:A#		; if 1 jump to volume on

LOD		$E017	R0		; 1 if M is pressed
CMP		R0		#1		; Check if R0 is 1
BRA		Z		:B		; if 1 jump to volume on

; If no keys were pressed, turn volume off
STR		#3 		$DFFF	; switch to audio bank
STR		#7		$E003	; switch to volume register
STR		#0		$E004	; set volume to 0
JMP		:LOOP

:ON
STR		#3 		$DFFF	; switch to audio bank
STR		#7		$E003	; switch to volume register
STR		#$40	$E004	; set volume to 64
STR		#4 		$E003 	; switch to note register
RET

:C
JSR		:ON
STR		#49		$E004	; set note to 49
JMP		:LOOP

:C#
JSR		:ON
STR		#50		$E004	; set note to 50
JMP		:LOOP

:D
JSR		:ON
STR		#51		$E004	; set note to 51
JMP		:LOOP

:D#
JSR		:ON
STR		#52		$E004	; set note to 52
JMP		:LOOP

:E
JSR		:ON
STR		#53		$E004	; set note to 53
JMP		:LOOP

:F
JSR		:ON
STR		#54		$E004	; set note to 54
JMP		:LOOP

:F#
JSR		:ON
STR		#55		$E004	; set note to 55
JMP		:LOOP

:G
JSR		:ON
STR		#56		$E004	; set note to 56
JMP		:LOOP

:G#
JSR		:ON
STR		#57		$E004	; set note to 57
JMP		:LOOP

:A
JSR		:ON
STR		#58		$E004	; set note to 58
JMP		:LOOP

:A#
JSR		:ON
STR		#59		$E004	; set note to 59
JMP		:LOOP

:B
JSR		:ON
STR		#60		$E004	; set note to 60
JMP		:LOOP
