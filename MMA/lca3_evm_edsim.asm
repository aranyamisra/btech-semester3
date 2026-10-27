ORG 0000H
    LJMP MAIN

ORG 0030H

 
; MAIN PROGRAM
 
MAIN:
    MOV SP, #60H

    ; Initialize party vote counters
    ; Party 1 = 30H ... Party 9 = 38H
    MOV 30H, #00H
    MOV 31H, #00H
    MOV 32H, #00H
    MOV 33H, #00H
    MOV 34H, #00H
    MOV 35H, #00H
    MOV 36H, #00H
    MOV 37H, #00H
    MOV 38H, #00H

    MOV P0, #0FFH
    MOV P1, #0FFH
    SETB P3.3
    SETB P3.4

 
; KEYPAD SCANNING
 
SCAN:
    MOV R0, #00H
    CLR F0

    SETB P0.3
    CLR P0.0
    ACALL COLSCAN
    JB F0, CONVERT

    SETB P0.0
    CLR P0.1
    ACALL COLSCAN
    JB F0, CONVERT

    SETB P0.1
    CLR P0.2
    ACALL COLSCAN
    JB F0, CONVERT

    SETB P0.2
    CLR P0.3
    ACALL COLSCAN
    JB F0, CONVERT

    LJMP SCAN

COLSCAN:
    JNB P0.4, GOTKEY
    INC R0
    JNB P0.5, GOTKEY
    INC R0
    JNB P0.6, GOTKEY
    INC R0
    RET

GOTKEY:
    SETB F0
    RET

 
; CONVERT KEYPAD POSITION TO KEY VALUE
; 1-9 = parties, 0AH = * (ends voting),
; 0BH = # (ignored), 0 = ignored
 
CONVERT:
    MOV A, R0

    CJNE A, #00H, C1
    MOV A, #0BH
    LJMP KEY_READY
C1:
    CJNE A, #01H, C2
    MOV A, #00H
    LJMP KEY_READY
C2:
    CJNE A, #02H, C3
    MOV A, #0AH
    LJMP KEY_READY
C3:
    CJNE A, #03H, C4
    MOV A, #09H
    LJMP KEY_READY
C4:
    CJNE A, #04H, C5
    MOV A, #08H
    LJMP KEY_READY
C5:
    CJNE A, #05H, C6
    MOV A, #07H
    LJMP KEY_READY
C6:
    CJNE A, #06H, C7
    MOV A, #06H
    LJMP KEY_READY
C7:
    CJNE A, #07H, C8
    MOV A, #05H
    LJMP KEY_READY
C8:
    CJNE A, #08H, C9
    MOV A, #04H
    LJMP KEY_READY
C9:
    CJNE A, #09H, C10
    MOV A, #03H
    LJMP KEY_READY
C10:
    CJNE A, #0AH, C11
    MOV A, #02H
    LJMP KEY_READY
C11:
    MOV A, #01H

 
; PROCESS KEY
 
KEY_READY:
    ; * (0AH) ends voting
    CJNE A, #0AH, NOT_END
    LJMP RESULTS

NOT_END:
    ; Ignore # (0BH) and key 0
    JNC WAIT_RELEASE
    JZ WAIT_RELEASE

    ; Save selected party
    MOV R3, A

    ; Party 1 -> 30H, Party 9 -> 38H
    ADD A, #2FH
    MOV R1, A
    INC @R1

    ; Show selected party on display 3 for about 0.1 s
    MOV A, R3
    ACALL SEGMENT
    SETB P3.3
    SETB P3.4
    MOV P1, A
    ACALL LONG_DELAY
    MOV P1, #0FFH

 
; WAIT FOR KEYPAD RELEASE
 
WAIT_RELEASE:
    MOV P0, #0FFH

RELEASE_LOOP:
    MOV P0, #0FEH
    JNB P0.4, RELEASE_LOOP
    JNB P0.5, RELEASE_LOOP
    JNB P0.6, RELEASE_LOOP

    MOV P0, #0FDH
    JNB P0.4, RELEASE_LOOP
    JNB P0.5, RELEASE_LOOP
    JNB P0.6, RELEASE_LOOP

    MOV P0, #0FBH
    JNB P0.4, RELEASE_LOOP
    JNB P0.5, RELEASE_LOOP
    JNB P0.6, RELEASE_LOOP

    MOV P0, #0F7H
    JNB P0.4, RELEASE_LOOP
    JNB P0.5, RELEASE_LOOP
    JNB P0.6, RELEASE_LOOP

    MOV P0, #0FFH
    LJMP SCAN

 
; VOTING ENDED: SHOW EACH PARTY IN TURN
; party number (display 3), then hundreds (2),
; tens (1), ones (0), one digit at a time
 
RESULTS:
    ACALL BLANK_ALL
    ACALL LONG_DELAY

    MOV R1, #30H            ; counter pointer
    MOV R2, #01H            ; party number

PARTY_LOOP:
    MOV 39H, R2             ; party number
    MOV A, @R1              ; vote count
    ACALL TO_HTO            ; -> 3AH, 3BH, 3CH
    ACALL SHOW_SEQ          ; show party, H, T, O one after another
    ACALL LONG_DELAY        ; extra gap between parties

    INC R1
    INC R2
    CJNE R2, #0AH, PARTY_LOOP

 
; FIND WINNING PARTY (tie -> lower number)
 
    MOV R1, #30H
    MOV R2, #01H
    MOV R3, #00H            ; highest count so far
    MOV R4, #01H            ; winning party

WIN_LOOP:
    MOV A, @R1
    CLR C
    SUBB A, R3
    JC NEXT_WIN
    JZ NEXT_WIN

    MOV A, @R1
    MOV R3, A
    MOV A, R2
    MOV R4, A

NEXT_WIN:
    INC R1
    INC R2
    CJNE R2, #0AH, WIN_LOOP

 
; REPEAT WINNER + VOTE COUNT FOREVER
 
WIN_DISPLAY:
    MOV 39H, R4
    MOV A, R3
    ACALL TO_HTO
    ACALL SHOW_SEQ
    ACALL BLANK_ALL         ; pause, then repeat
    ACALL LONG_DELAY
    ACALL LONG_DELAY
    ACALL LONG_DELAY
    SJMP WIN_DISPLAY

 
; TO_HTO: split A (0-255) into
; 3AH = hundreds, 3BH = tens, 3CH = ones
 
TO_HTO:
    MOV B, #100
    DIV AB
    MOV 3AH, A
    MOV A, B
    MOV B, #10
    DIV AB
    MOV 3BH, A
    MOV 3CH, B
    RET

 
; SHOW_SEQ: show the 4 digits one at a time,
; each on its own display position, ~0.125 s each
; 39H = party, 3AH = H, 3BH = T, 3CH = O
; (the simulator can't draw multiplexed digits steadily)
 
SHOW_SEQ:
    ; Display 3: party number
    SETB P3.3
    SETB P3.4
    MOV A, 39H
    ACALL SEGMENT
    MOV P1, A
    ACALL HOLD
    MOV P1, #0FFH
    ACALL GAP

    ; Display 2: hundreds
    CLR P3.3
    SETB P3.4
    MOV A, 3AH
    ACALL SEGMENT
    MOV P1, A
    ACALL HOLD
    MOV P1, #0FFH
    ACALL GAP

    ; Display 1: tens
    SETB P3.3
    CLR P3.4
    MOV A, 3BH
    ACALL SEGMENT
    MOV P1, A
    ACALL HOLD
    MOV P1, #0FFH
    ACALL GAP

    ; Display 0: ones
    CLR P3.3
    CLR P3.4
    MOV A, 3CH
    ACALL SEGMENT
    MOV P1, A
    ACALL HOLD
    MOV P1, #0FFH
    ACALL GAP
    RET

; digit on-time: about 0.1 s
HOLD:
    ACALL LONG_DELAY
    RET

; short blank gap between digits: about 0.025 s
GAP:
    MOV R6, #50
GAP1:
    MOV R7, #250
GAP2:
    DJNZ R7, GAP2
    DJNZ R6, GAP1
    RET

 
; BLANK_ALL: turn off all 4 digits
 
BLANK_ALL:
    SETB P3.3
    SETB P3.4
    MOV P1, #0FFH
    CLR P3.3
    SETB P3.4
    MOV P1, #0FFH
    SETB P3.3
    CLR P3.4
    MOV P1, #0FFH
    CLR P3.3
    CLR P3.4
    MOV P1, #0FFH
    RET
; 7-SEGMENT DECIMAL LOOKUP
; Input: A = 0 to 9
; Output: A = active-low segment pattern
 
SEGMENT:
    MOV DPTR, #SEG_TABLE
    MOVC A, @A+DPTR
    RET

SEG_TABLE:
    DB 0C0H       ; 0
    DB 0F9H       ; 1
    DB 0A4H       ; 2
    DB 0B0H       ; 3
    DB 099H       ; 4
    DB 092H       ; 5
    DB 082H       ; 6
    DB 0F8H       ; 7
    DB 080H       ; 8
    DB 090H       ; 9

 
; LONG DELAY (~0.1 s at 12 MHz)
 
LONG_DELAY:
    MOV R6, #200
LD1:
    MOV R7, #250
LD2:
    DJNZ R7, LD2
    DJNZ R6, LD1
    RET

END