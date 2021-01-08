STR		#3 		$DFFF 	; switch to audio bank
STR		#0 		$E002 	; switch to oscillator 0
STR		#2 		$E003 	; switch to waveform register
STR		#%00	$E004 	; set to pulse
STR		#3 		$E003 	; switch to pulse width register
STR		#128	$E004 	; set to 50% (128)
STR		#4 		$E003 	; switch to note register
STR		#49		$E004	; set note to 49 (C4)
STR		#3 		$DFFF 	; switch to audio bank
STR		#7		$E003	; switch to volume register

STR		#3 		$DFFF 	; switch to audio bank
STR		#$40	$E004	; set volume to 64

:LOOP
JMP		:LOOP
