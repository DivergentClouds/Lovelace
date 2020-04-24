; Harriet Audio Test

jmp		:copy			; jump to copy routine (no need to return)

str		#3 		$3FFF 	; switch from rom bank to audio bank
str		#0 		$4001 	; switch to oscillator 0
str		#2 		$4002 	; switch to waveform register
str		#0 		$4003 	; set to pulse
str		#4 		$4002 	; switch to note register
str		#$40	$4003	; set note to 64 (C6)
str		#7		$4002	; switch to volume register
str		#$20	$4003	; set volume to 32

jmp		$223			; loop forever

:copy					; copy audio code from rom into global memory

str		#$40	$00		; store rom source page location in $0002 in memory
str		#$02	$02		; store audio destination page location in $0000 in memory

lod		#3		r0		; load 2 into r0

:loop
str		r0		$1		; store r0 as least significant byte for rom source page
str		r0		$3		; store r0 as least significant byte for audio destination page

lodi	$0		r1		; indirect load from address pointed to by $0000
stri	r1		$2		; indirect store from address pointed to by $0003
inc		r0				; increment r0

cmp		r0		#$26	; compare desired number of bits copied + 3 with r1
bran	Z		:loop	; if not equal branch to :loop

jmp		$203			; jump to audio code
