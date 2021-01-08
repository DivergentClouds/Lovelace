SET   I              ; prevent interrupts while working in another bank
STR   #4    $DFFF    ; switch to clock bank
STR   #$03  $FFFE    ; store location of lick-clock-callback for the clock callback
STR   #$0   $FFFF
CLR   I              ; reenable interrupts

STR   #3    $DFFF    ; switch to audio bank
STR   #0    $E002    ; switch to oscillator 0
STR   #2    $E003    ; switch to waveform register
STR   #%00  $E004    ; set to pulse
STR   #3    $E003    ; switch to pulse width register
STR   #80   $E004    ; set to 50% (128)
STR   #7    $E003    ; switch to volume register
STR   #$40  $E004    ; set volume to 25%
STR   #4    $E003    ; switch to note register

STR   #49   $00      ; set note to 49 (C4)

LOD   #0    R1       ; initalize R1
LOD   #0    R2       ; initalize R2
LOD   #0    R3       ; initalize R3

:LOOP
LOD   $00   R0		 ; load current note into R0
STR   R0    $E004    ; set note to value in R0
JMP :LOOP
