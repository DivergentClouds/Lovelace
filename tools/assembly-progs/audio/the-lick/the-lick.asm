ADR BANK_SELECTOR $DFFF
ADR OSC_SELECTOR $E002
ADR AUDIO_REG_SELECTOR $E003
ADR AUDIO_REG_VALUE $E004
ADR CLOCK_CALLBACK_MSB $FFFE
ADR CLOCK_CALLBACK_LSB $FFFF

SET   I                                  ; prevent interrupts while working in another bank
STR   #4           BANK_SELECTOR         ; switch to clock bank
STR   >:CALLBACK   CLOCK_CALLBACK_MSB    ; store location of lick-clock-callback for the clock callback
STR   <:CALLBACK   CLOCK_CALLBACK_MSB
CLR   I                                  ; reenable interrupts

STR   #3    BANK_SELECTOR                ; switch to audio bank
STR   #0    OSC_SELECTOR                 ; switch to oscillator 0
STR   #2    AUDIO_REG_SELECTOR           ; switch to waveform register
STR   #%00  AUDIO_REG_VALUE              ; set to pulse
STR   #3    AUDIO_REG_SELECTOR           ; switch to pulse width register
STR   #80   AUDIO_REG_VALUE              ; set to 50% (128)
STR   #7    AUDIO_REG_SELECTOR           ; switch to volume register
STR   #$40  AUDIO_REG_VALUE              ; set volume to 25%
STR   #4    AUDIO_REG_SELECTOR           ; switch to note register

STR   #49   $00                          ; set note to 49 (C4)

LOD   #0    R1                           ; initalize R1
LOD   #0    R2                           ; initalize R2
LOD   #0    R3                           ; initalize R3

:LOOP
LOD   $00   R0		                     ; load current note into R0
STR   R0    AUDIO_REG_VALUE              ; set note to value in R0
JMP :LOOP


:CALLBACK
LOD   $00   ACC                         ; load current pitch
INC   ACC                               ; make pitch rise
STR   ACC   $00                         ; store current pitch
RET
