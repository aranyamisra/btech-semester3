ORG 0000H             ; Set the program's starting address to 0000H
    LJMP MAIN         ; Jump to MAIN to begin program execution

ORG 0030H             ; Place the main program at memory address 0030H


; ================= MAIN PROGRAM =================

MAIN:
    MOV SP, #60H      ; Initialize stack pointer to 60H

    ; Initialize party vote counters to zero
    ; Each RAM address stores votes for one party
    ; 30H = Party 1, 31H = Party 2, ..., 38H = Party 9

    MOV 30H, #00H     ; Set Party 1's vote count to zero
    MOV 31H, #00H     ; Set Party 2's vote count to zero
    MOV 32H, #00H     ; Set Party 3's vote count to zero
    MOV 33H, #00H     ; Set Party 4's vote count to zero
    MOV 34H, #00H     ; Set Party 5's vote count to zero
    MOV 35H, #00H     ; Set Party 6's vote count to zero
    MOV 36H, #00H     ; Set Party 7's vote count to zero
    MOV 37H, #00H     ; Set Party 8's vote count to zero
    MOV 38H, #00H     ; Set Party 9's vote count to zero

    MOV P0, #0FFH     ; Set all Port 0 pins HIGH initially
    MOV P1, #0FFH     ; Turn OFF all seven-segment display segments
    SETB P3.3         ; Set display-select bit P3.3 HIGH
    SETB P3.4         ; Set display-select bit P3.4 HIGH


; ================= KEYPAD SCANNING =================

SCAN:
    MOV R0, #00H      ; Reset R0 to store the detected keypad position
    CLR F0            ; Clear flag F0 to indicate no key is detected

    SETB P0.3         ; Set row line P0.3 HIGH
    CLR P0.0          ; Make row line P0.0 LOW to scan the first row
    ACALL COLSCAN     ; Check the three keypad column inputs
    JB F0, CONVERT    ; If a key is detected, jump to CONVERT

    SETB P0.0         ; Set the previous row HIGH
    CLR P0.1          ; Make row line P0.1 LOW to scan the second row
    ACALL COLSCAN     ; Check the three keypad column inputs
    JB F0, CONVERT    ; If a key is detected, jump to CONVERT

    SETB P0.1         ; Set the previous row HIGH
    CLR P0.2          ; Make row line P0.2 LOW to scan the third row
    ACALL COLSCAN     ; Check the three keypad column inputs
    JB F0, CONVERT    ; If a key is detected, jump to CONVERT

    SETB P0.2         ; Set the previous row HIGH
    CLR P0.3          ; Make row line P0.3 LOW to scan the fourth row
    ACALL COLSCAN     ; Check the three keypad column inputs
    JB F0, CONVERT    ; If a key is detected, jump to CONVERT

    LJMP SCAN         ; If no key is detected, restart keypad scanning


; ================= COLUMN SCANNING =================

COLSCAN:
    JNB P0.4, GOTKEY  ; If column 1 is LOW, a key is pressed
    INC R0            ; Otherwise, increment R0 to check the next position

    JNB P0.5, GOTKEY  ; If column 2 is LOW, a key is pressed
    INC R0            ; Otherwise, increment R0 again

    JNB P0.6, GOTKEY  ; If column 3 is LOW, a key is pressed
    INC R0            ; Advance the position counter if no key is found

    RET               ; Return to SCAN if no column contains a pressed key

GOTKEY:
    SETB F0           ; Set F0 to indicate that a key was detected
    RET               ; Return to SCAN, which will then jump to CONVERT


; ========== CONVERT KEYPAD POSITION TO KEY VALUE ==========
; R0 contains the detected keypad position
; A will contain the corresponding key value:
; 01H-09H = Parties 1-9
; 0AH = * (ends voting)
; 0BH = # (ignored)
; 00H = 0 (ignored)

CONVERT:
    MOV A, R0         ; Copy the detected keypad position into A

    CJNE A, #00H, C1  ; If position is not 0, jump to C1
    MOV A, #0BH       ; Position 0 corresponds to the # key
    LJMP KEY_READY    ; Continue to process the converted key

C1:
    CJNE A, #01H, C2  ; If position is not 1, jump to C2
    MOV A, #00H       ; Position 1 corresponds to key 0
    LJMP KEY_READY    ; Continue to process the converted key

C2:
    CJNE A, #02H, C3  ; If position is not 2, jump to C3
    MOV A, #0AH       ; Position 2 corresponds to the * key
    LJMP KEY_READY    ; Continue to process the converted key

C3:
    CJNE A, #03H, C4  ; If position is not 3, jump to C4
    MOV A, #09H       ; Position 3 corresponds to Party 9
    LJMP KEY_READY    ; Continue to process the converted key

C4:
    CJNE A, #04H, C5  ; If position is not 4, jump to C5
    MOV A, #08H       ; Position 4 corresponds to Party 8
    LJMP KEY_READY    ; Continue to process the converted key

C5:
    CJNE A, #05H, C6  ; If position is not 5, jump to C6
    MOV A, #07H       ; Position 5 corresponds to Party 7
    LJMP KEY_READY    ; Continue to process the converted key

C6:
    CJNE A, #06H, C7  ; If position is not 6, jump to C7
    MOV A, #06H       ; Position 6 corresponds to Party 6
    LJMP KEY_READY    ; Continue to process the converted key

C7:
    CJNE A, #07H, C8  ; If position is not 7, jump to C8
    MOV A, #05H       ; Position 7 corresponds to Party 5
    LJMP KEY_READY    ; Continue to process the converted key

C8:
    CJNE A, #08H, C9  ; If position is not 8, jump to C9
    MOV A, #04H       ; Position 8 corresponds to Party 4
    LJMP KEY_READY    ; Continue to process the converted key

C9:
    CJNE A, #09H, C10 ; If position is not 9, jump to C10
    MOV A, #03H       ; Position 9 corresponds to Party 3
    LJMP KEY_READY    ; Continue to process the converted key

C10:
    CJNE A, #0AH, C11 ; If position is not 10, jump to C11
    MOV A, #02H       ; Position 10 corresponds to Party 2
    LJMP KEY_READY    ; Continue to process the converted key

C11:
    MOV A, #01H       ; Remaining position 11 corresponds to Party 1


; ================= PROCESS THE DETECTED KEY =================

KEY_READY:
    ; Check whether the selected key is *

    CJNE A, #0AH, NOT_END ; If A is not 0AH, continue to NOT_END
    LJMP RESULTS          ; If A is 0AH (*), end voting and show results

NOT_END:
    ; Ignore # and 0; accept only party numbers 1-9

    JNC WAIT_RELEASE  ; If carry is clear, the key value is above 09H
                      ; This ignores # (0BH)
    JZ WAIT_RELEASE   ; If A is zero, ignore key 0

    MOV R3, A         ; Save the selected party number in R3

    ; Convert the party number into its vote-counter RAM address
    ; Party 1: 01H + 2FH = 30H
    ; Party 9: 09H + 2FH = 38H

    ADD A, #2FH       ; Add 2FH to get the party's RAM address
    MOV R1, A         ; Store the address in R1
    INC @R1           ; Increment the vote count at the address in R1

    ; Display the selected party number on display position 3

    MOV A, R3         ; Restore the party number into A
    ACALL SEGMENT     ; Convert the party number into a segment pattern
    SETB P3.3         ; Select display position 3 (P3.3 HIGH)
    SETB P3.4         ; Select display position 3 (P3.4 HIGH)
    MOV P1, A          ; Send the segment pattern to Port 1
    ACALL LONG_DELAY  ; Keep the party number displayed briefly
    MOV P1, #0FFH     ; Turn OFF the display segments


; ================= WAIT FOR KEYPAD RELEASE =================

WAIT_RELEASE:
    MOV P0, #0FFH     ; Set all keypad row lines HIGH initially

RELEASE_LOOP:
    MOV P0, #0FEH     ; Make P0.0 LOW and keep the other row bits HIGH
    JNB P0.4, RELEASE_LOOP ; If column 1 is LOW, keep waiting
    JNB P0.5, RELEASE_LOOP ; If column 2 is LOW, keep waiting
    JNB P0.6, RELEASE_LOOP ; If column 3 is LOW, keep waiting

    MOV P0, #0FDH     ; Make P0.1 LOW to check the second row
    JNB P0.4, RELEASE_LOOP ; If column 1 is LOW, keep waiting
    JNB P0.5, RELEASE_LOOP ; If column 2 is LOW, keep waiting
    JNB P0.6, RELEASE_LOOP ; If column 3 is LOW, keep waiting

    MOV P0, #0FBH     ; Make P0.2 LOW to check the third row
    JNB P0.4, RELEASE_LOOP ; If column 1 is LOW, keep waiting
    JNB P0.5, RELEASE_LOOP ; If column 2 is LOW, keep waiting
    JNB P0.6, RELEASE_LOOP ; If column 3 is LOW, keep waiting

    MOV P0, #0F7H     ; Make P0.3 LOW to check the fourth row
    JNB P0.4, RELEASE_LOOP ; If column 1 is LOW, keep waiting
    JNB P0.5, RELEASE_LOOP ; If column 2 is LOW, keep waiting
    JNB P0.6, RELEASE_LOOP ; If column 3 is LOW, keep waiting

    MOV P0, #0FFH     ; Restore all Port 0 row lines HIGH
    LJMP SCAN         ; Start scanning again after the key is released


; ========== VOTING ENDED: DISPLAY PARTY RESULTS ==========
; Display sequence:
; Position 3 = party number
; Position 2 = hundreds digit of vote count
; Position 1 = tens digit of vote count
; Position 0 = ones digit of vote count

RESULTS:
    ACALL BLANK_ALL   ; Turn OFF all four display positions
    ACALL LONG_DELAY ; Wait briefly before displaying results

    MOV R1, #30H      ; Point R1 to Party 1's vote counter
    MOV R2, #01H      ; Initialize the party number to 1

PARTY_LOOP:
    MOV 39H, R2       ; Store the current party number at RAM address 39H
    MOV A, @R1        ; Load the current party's vote count into A
    ACALL TO_HTO      ; Split the vote count into hundreds, tens and ones
    ACALL SHOW_SEQ    ; Display party number, then H, T and O digits
    ACALL LONG_DELAY  ; Add a pause between consecutive parties

    INC R1            ; Move to the next party's vote-counter address
    INC R2            ; Increment the party number
    CJNE R2, #0AH, PARTY_LOOP ; Repeat until all 9 parties are displayed


; ========== FIND THE WINNING PARTY ==========
; If two parties tie, the lower-numbered party wins the tie-break

    MOV R1, #30H      ; Point R1 to Party 1's vote counter
    MOV R2, #01H      ; Start checking from Party 1
    MOV R3, #00H      ; R3 stores the highest vote count found so far
    MOV R4, #01H      ; R4 stores the winning party number

WIN_LOOP:
    MOV A, @R1        ; Load the current party's vote count into A
    CLR C             ; Clear carry before subtraction
    SUBB A, R3        ; Subtract the highest count from the current count
                      ; Carry is set if the current count is smaller
    JC NEXT_WIN       ; If current count is smaller, keep the old winner
    JZ NEXT_WIN       ; If counts are equal, keep the earlier party
                      ; This preserves the lower party number in a tie

    MOV A, @R1        ; Reload the current party's vote count
    MOV R3, A         ; Update the highest vote count
    MOV A, R2         ; Load the current party number
    MOV R4, A         ; Update the winning party number

NEXT_WIN:
    INC R1            ; Move to the next party's vote-counter address
    INC R2            ; Increment the party number
    CJNE R2, #0AH, WIN_LOOP ; Continue until all 9 parties are checked


; ========== DISPLAY THE WINNER AND VOTE COUNT FOREVER ==========

WIN_DISPLAY:
    MOV 39H, R4       ; Store the winning party number at RAM address 39H
    MOV A, R3         ; Load the winning party's vote count
    ACALL TO_HTO      ; Split the winning vote count into H, T and O
    ACALL SHOW_SEQ    ; Display the winner and the three vote-count digits
    ACALL BLANK_ALL   ; Turn OFF all four display positions
    ACALL LONG_DELAY  ; Wait before displaying the winner again
    ACALL LONG_DELAY  ; Add another delay
    ACALL LONG_DELAY  ; Add another delay
    SJMP WIN_DISPLAY  ; Repeat the winner display forever


; ========== CONVERT VOTE COUNT INTO HUNDREDS, TENS, ONES ==========
; Input: A = vote count (0-255)
; Output: 3AH = hundreds, 3BH = tens, 3CH = ones

TO_HTO:
    MOV B, #100       ; Load 100 into B to divide by 100
    DIV AB            ; A = quotient (hundreds), B = remainder
    MOV 3AH, A        ; Store the hundreds digit at RAM address 3AH

    MOV A, B          ; Move the remainder into A
    MOV B, #10        ; Load 10 into B to divide the remainder
    DIV AB            ; A = tens digit, B = ones digit
    MOV 3BH, A        ; Store the tens digit at RAM address 3BH
    MOV 3CH, B        ; Store the ones digit at RAM address 3CH
    RET               ; Return to the calling routine


; ========== DISPLAY FOUR DIGITS ONE AT A TIME ==========
; 39H = party number
; 3AH = hundreds digit
; 3BH = tens digit
; 3CH = ones digit

SHOW_SEQ:
    ; Display position 3: party number

    SETB P3.3         ; Set P3.3 HIGH
    SETB P3.4         ; Set P3.4 HIGH; select display position 3
    MOV A, 39H        ; Load the party number into A
    ACALL SEGMENT     ; Convert the number to a seven-segment pattern
    MOV P1, A         ; Output the segment pattern through Port 1
    ACALL HOLD        ; Keep the digit displayed for about 0.1 seconds
    MOV P1, #0FFH     ; Turn OFF the segments
    ACALL GAP         ; Leave a short blank gap between digits

    ; Display position 2: hundreds digit

    CLR P3.3          ; Set P3.3 LOW
    SETB P3.4         ; Set P3.4 HIGH; select display position 2
    MOV A, 3AH        ; Load the hundreds digit into A
    ACALL SEGMENT     ; Convert it to a seven-segment pattern
    MOV P1, A         ; Output the segment pattern
    ACALL HOLD        ; Keep the digit displayed briefly
    MOV P1, #0FFH     ; Turn OFF the segments
    ACALL GAP         ; Leave a short blank gap

    ; Display position 1: tens digit

    SETB P3.3         ; Set P3.3 HIGH
    CLR P3.4          ; Set P3.4 LOW; select display position 1
    MOV A, 3BH        ; Load the tens digit into A
    ACALL SEGMENT     ; Convert it to a seven-segment pattern
    MOV P1, A         ; Output the segment pattern
    ACALL HOLD        ; Keep the digit displayed briefly
    MOV P1, #0FFH     ; Turn OFF the segments
    ACALL GAP         ; Leave a short blank gap

    ; Display position 0: ones digit

    CLR P3.3          ; Set P3.3 LOW
    CLR P3.4          ; Set P3.4 LOW; select display position 0
    MOV A, 3CH        ; Load the ones digit into A
    ACALL SEGMENT     ; Convert it to a seven-segment pattern
    MOV P1, A         ; Output the segment pattern
    ACALL HOLD        ; Keep the digit displayed briefly
    MOV P1, #0FFH     ; Turn OFF the segments
    ACALL GAP         ; Leave a short blank gap
    RET               ; Return after displaying all four digits


; ========== HOLD A DIGIT ON THE DISPLAY ==========

HOLD:
    ACALL LONG_DELAY  ; Call the longer delay routine
    RET               ; Return after the delay


; ========== SHORT GAP BETWEEN DISPLAYED DIGITS ==========

GAP:
    MOV R6, #50       ; Initialize outer delay-loop counter
GAP1:
    MOV R7, #250      ; Initialize inner delay-loop counter
GAP2:
    DJNZ R7, GAP2     ; Decrement R7 and repeat until it reaches zero
    DJNZ R6, GAP1     ; Decrement R6 and repeat the inner loop
    RET               ; Return after completing the short delay


; ========== TURN OFF ALL FOUR DISPLAY POSITIONS ==========

BLANK_ALL:
    SETB P3.3         ; Select display position 3
    SETB P3.4         ; Complete selection of display position 3
    MOV P1, #0FFH     ; Turn OFF display position 3

    CLR P3.3          ; Select the LOW state for P3.3
    SETB P3.4         ; Select display position 2
    MOV P1, #0FFH     ; Turn OFF display position 2

    SETB P3.3         ; Set P3.3 HIGH
    CLR P3.4          ; Select display position 1
    MOV P1, #0FFH     ; Turn OFF display position 1

    CLR P3.3          ; Set P3.3 LOW
    CLR P3.4          ; Select display position 0
    MOV P1, #0FFH     ; Turn OFF display position 0

    RET               ; Return after blanking all four positions


; ========== SEVEN-SEGMENT LOOKUP TABLE ==========
; Input: A = digit from 0 to 9
; Output: A = active-LOW pattern for the seven-segment display
; Active-LOW means a segment turns ON when its output bit is 0

SEGMENT:
    MOV DPTR, #SEG_TABLE ; Point DPTR to the start of the lookup table
    MOVC A, @A+DPTR      ; Read the pattern at table address DPTR + A
    RET                  ; Return with the segment pattern in A

SEG_TABLE:
    DB 0C0H           ; Pattern for digit 0
    DB 0F9H           ; Pattern for digit 1
    DB 0A4H           ; Pattern for digit 2
    DB 0B0H           ; Pattern for digit 3
    DB 099H           ; Pattern for digit 4
    DB 092H           ; Pattern for digit 5
    DB 082H           ; Pattern for digit 6
    DB 0F8H           ; Pattern for digit 7
    DB 080H           ; Pattern for digit 8
    DB 090H           ; Pattern for digit 9


; ========== LONG DELAY ROUTINE ==========
; Intended to provide approximately 0.1 seconds of delay at 12 MHz

LONG_DELAY:
    MOV R6, #200      ; Initialize the outer delay-loop counter
LD1:
    MOV R7, #250      ; Initialize the inner delay-loop counter
LD2:
    DJNZ R7, LD2      ; Decrement R7 and repeat until it becomes zero
    DJNZ R6, LD1      ; Decrement R6 and repeat the inner loop
    RET               ; Return after the delay is complete

END                   ; Tell the assembler that the source code ends here