; $DFFE = number of peripherals + 1

PSH R0          ; push all registers onto the stack
PSH R1
PSH R2
PSH R3
PSH ACC

LOD $DFFE R0    ; load the number of peripherals + 1 into R0

LOD $DFFF R1    ; load the current bank number into R1

:LOOP

STR R0 $DFFF    ; switch to bank number in R0
LOD $E000 R2    ; 1 if peripheral is interrupting, 0 if not

CMP R2 #0       ; check if peripheral is interrupting
BRA Z :SKIP     ; if peripheral is not interrupting then branch to :SKIP

JSR $FF00       ; jump to peripheral's interrupt subroutine

STR #0 $E000    ; mark peripheral as not interrupting

:SKIP
DEC R0          ; go to the next peripheral
CMP R0 #1       ; check if the peripheral number is 1
BRAN Z :LOOP    ; if there are more peripherals branch back to :LOOP

STR R1 $DFFF    ; switch back to bank from before interrupt was called

POP ACC         ; pop all registers from the stack back into the correct place
POP R3
POP R2
POP R1
POP R0

RETI            ; return from interrupt
