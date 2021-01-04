SET I	        ; Disable interrupts while ROM is running
STR #4 $DFFE    ; Store number of used banks (4) at $DFFE, for use by interrupt handler
CLR I           ; Reenable interrupts
JMP $200        ; Go to start of user code
