; $9FFE = number of peripherals + 1

PSH R0
PSH R1
PSH R2
PSH R3
PSH ACC

LOD $9FFE R0

:LOOP

STR R0 $9FFF
LOD $A000 R1

CMP R1 #0
BRA Z :SKIP

JSR $FF00

STR #0 $A000

:SKIP
DEC R0
CMP R0 #1
BRAN Z :LOOP

POP ACC
POP R3
POP R2
POP R1
POP R0

RETI
