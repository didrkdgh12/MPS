;Assuming user will only enter ' ' 0-9 *+/-
; "I don't like it, I love it. Uh-Oh" - Kirby
; A Reverse polish notation calculator that implements a stack in LC3
;
;Uses a mostly modular design by implementing what can be done in seperate
;   subroutines so that debuggins is easier.
;Also prints the answer in hex
.ORIG x3000
	
;your code goes here

            AND R0, R0, #0
            AND R6, R6, #0
            AND R4, R4, #0
GET_NEXT_CH GETC
            OUT
            ADD R3, R0, #0
            NOT R3, R3
            ADD R3, R3, #1
            LD R1, NEW_LINE
            ADD R5, R1, R3
            BRz DONE
            LD R1, CAR_RET
            ADD R5, R1, R3
            BRz DONE
            LD R1, SPACE
            ADD R5, R1, R3
            BRz GET_NEXT_CH
            JSR EVALUATE
            
            BRnzp GET_NEXT_CH

DONE        JSR POP
            ADD R6, R0, #0
            JSR POP
            ADD R5, R5, #0
            BRz EXP_ERR
            ADD R3, R6, #0
            JSR PRINT_HEX
PRNDONE
            HALT

EXP_ERR     LEA R0, EXP_ERR_MSG
            PUTS
            AND R6, R6, #0
            HALT

SPACE       .FILL x0020
NEW_LINE    .FILL x000A
CAR_RET     .FILL x000D
EXP_ERR_MSG .STRINGZ "\nInvalid Expression"
EXP_X       .FILL x0078
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX                   ;prints answer in hex
    LD R0, EXP_X
    OUT

    AND R1, R1, #0          ; Current Word
    AND R2, R2, #0          ; Current Digit
    ADD R2, R2, #4          
BEGIN   
    AND R1, R1, #0
    AND R5, R5, #0 
    AND R0, R0, #0
    AND R4, R4, #0          ; Temp Bit Counter
    ADD R4, R4, #4
    ADD R2, R2, #0
    BRz DONE_PRINTING
    ADD R2, R2, #-1
BEGINNING
    ADD R3, R3, #0
    BRzp ZER
    BRnzp ONEE
ZER
    ADD R3, R3, R3          ; Left shift (2x)
    ADD R4, R4, #0
    BRz BEGIN               ; Restart bit counter
    ADD R4, R4, #-1
    BRnzp DONE_ADDING_2         ; Complete?
ONEE
    AND R5, R5, #0
    ADD R3, R3, R3          ; Left Shift
    
    
    ADD R5, R4, #-4         ; Check first
    BRz ADD_8
    ADD R5, R4, #-3         ; Check second
    BRz ADD_4               
    ADD R5, R4, #-2         ; Check third 
    BRz ADD_2              
    ADD R5, R4, #-1         ; Check fourth 
    BRz ADD_1
    BRnzp DONE_ADDING
ADD_8                       ; Add corresponding value
    ADD R1, R1, #8
    BRnzp DONE_ADDING
ADD_4
    ADD R1, R1, #4
    BRnzp DONE_ADDING

ADD_2
    ADD R1, R1, #2
    BRnzp DONE_ADDING

ADD_1
    ADD R1, R1, #1
    BRnzp DONE_ADDING

DONE_ADDING
    ADD R4, R4, #-1
DONE_ADDING_2
    
    ADD R4, R4, #0
    BRnz PRINT
    BRnzp BEGINNING

PRINT
    ADD R5, R1, #-9
    BRp PRINT_CHAR
    ADD R0, R0, #15 
    ADD R0, R0, #15
    ADD R0, R0, #15
    ADD R0, R0, #3
    ADD R0, R0, R1
    OUT
    BRnzp BEGIN


PRINT_CHAR
    AND R0, R0, #0
    ADD R0, R0, #15 
    ADD R0, R0, #15 
    ADD R0, R0, #15 
    ADD R0, R0, #15 
    ADD R0, R0, #-5
    ADD R0, R0, R1
    OUT
    BRnp BEGIN
DONE_PRINTING
    BRnzp PRNDONE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

            ST R0, EVALUATE_R0
            ST R1, EVALUATE_R1
            ST R2, EVALUATE_R2
            ST R3, EVALUATE_R3
            ST R4, EVALUATE_R4
            ST R5, EVALUATE_R5
            ST R6, EVALUATE_R6
            ST R7, EVALUATE_R7
            
            LD R1, OP_ADD       ;Check for +
            ADD R5, R1, R3
            BRz PLUS_OP
            
            LD R1, OP_MIN       ;Check for -
            ADD R5, R1, R3
            BRz MIN_OP
            
            LD R1, OP_MUL       ;Check for *
            ADD R5, R1, R3
            BRz MUL_OP
            
            LD R1, OP_DIV       ;Check for /
            ADD R5, R1, R3
            BRz DIV_OP
            
            LD R1, OP_EXP       ;Check for ^
            ADD R5, R1, R3
            BRz EXP_OP
NL
            ADD R4, R4, #0
            ADD R4, R4, #10
            LD R1, NINE         ;Load hex 9
NCHK
            ADD R6, R1, R3
            BRnp NI
            ADD R0, R0, #-16
            ADD R0, R0, #-16
            ADD R0, R0, #-16
            JSR PUSH            ;Push result onto stack
            ADD R5, R5, #0
            BRp EXP_ERR         ;IF not number or operator, error
            JSR EV_DONE
NI
            ADD R1, R1, #-1
            ADD R4, R4, #-1
            BRn INP_ERRM
            BRnzp NCHK
EV_DONE
            LD R0, EVALUATE_R0  ;Load values back into registers
            LD R1, EVALUATE_R1
            LD R2, EVALUATE_R2
            LD R3, EVALUATE_R3
            LD R4, EVALUATE_R4
            LD R5, EVALUATE_R5
            LD R6, EVALUATE_R6
            LD R7, EVALUATE_R7
            RET

INP_ERRM
            LEA R0, INP_ERR
            PUTS
            HALT

ZERO        .FILL x0030
NINE        .FILL x0039
OP_ADD      .FILL x002B
OP_MIN      .FILL x002D
OP_MUL      .FILL x002A
OP_DIV      .FILL x002F
OP_EXP      .FILL x005E
EVALUATE_R0 .BLKW #1
EVALUATE_R1 .BLKW #1
EVALUATE_R2 .BLKW #1
EVALUATE_R3 .BLKW #1
EVALUATE_R4 .BLKW #1
EVALUATE_R5 .BLKW #1
EVALUATE_R6 .BLKW #1
EVALUATE_R7 .BLKW #1
INP_ERR     .STRINGZ "\nInvalid Input"

EXP_ERRX
    BRnzp EXP_ERR
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
    ADD R0, R3, R4
    RET

PLUS_OP                 ;Each action has it's own OP subroutine, this
    JSR STVAL           ;sets up the action, checks the stack, and
    JSR POP             ;pushes results back onto the stack. it is the
    ADD R5, R5, #0      ;same for all actions
    BRp EXP_ERRX
    ADD R3, R0, #0
    JSR POP
    ADD R5, R5, #0
    BRP EXP_ERRX
    ADD R4, R0, #0
    JSR PLUS
    JSR PUSH
    ADD R5, R5, #0
    BRp EXP_ERRX
    JSR RSTVAL


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
    NOT R3, R3
    ADD R3, R3, #1
    ADD R0, R4, R3
    RET

MIN_OP
    JSR STVAL
    JSR POP
    ADD R5, R5, #0
    BRp EXP_ERRX
    ADD R3, R0, #0
    JSR POP
    ADD R5, R5, #0
    BRP EXP_ERRX
    ADD R4, R0, #0
    JSR MIN
    JSR PUSH
    ADD R5, R5, #0
    BRp EXP_ERRX
    JSR RSTVAL
    RET

GET_NEXT_CHX
    BRnzp GET_NEXT_CH
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL
    AND R2, R2, #0
    ADD R3, R3, #0
    BRzp FMCHECK
    NOT R3, R3
    ADD R3, R3, #1
    ADD R2, R2, #1
FMCHECK
    ADD R4, R4, #0
    NOT R4, R4
    ADD R4, R4, #1
    ADD R2, R2, #-1
    AND R0, R0, #0
MULLOOP
    ADD R0, R0, R3
    ADD R4, R4, #-1
    BRp MULLOOP
    RET

MUL_OP
    JSR STVAL
    JSR POP
    ADD R5, R5, #0
    BRp EXP_ERRX
    ADD R3, R0, #0
    JSR POP
    ADD R5, R5, #0
    BRP EXP_ERRX
    ADD R4, R0, #0
    JSR MUL
    ADD R2, R2, #0
    BRz MCPSH
    NOT R0, R0
    ADD R0, R0, #1
MCPSH
    JSR PUSH
    ADD R5, R5, #0
    BRp EXP_ERRX
    JSR RSTVAL
    RET


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV
    AND R0, R0, #0
    NOT R3, R3
    ADD R3, R3, #1
    BRzp FDCHECK
    NOT R3, R3
    ADD R3, R3, #1
    ADD R2, R2, #1
FDCHECK
    ADD R4, R4, #0
    NOT R4, R4
    ADD R4, R4, #1
    ADD R2, R2, #-1
DIVLOOP
    ADD R4, R4, R3
    BRn DIV_DONE
    ADD R0, R0, #1
    BRnzp DIVLOOP
DIV_DONE    
    RET


DIV_OP
    JSR STVAL
    JSR POP
    ADD R5, R5, #0
    BRp EXP_ERRX
    ADD R3, R0, #0
    JSR POP
    ADD R5, R5, #0
    BRP EXP_ERRX
    ADD R4, R0, #0
    JSR DIV
    JSR PUSH
    ADD R2, R2, #0
    BRz DCPSH
    NOT R0, R0
    ADD R0, R0, #1
DCPSH
    ADD R5, R5, #0
    BRp EXP_ERRX
    JSR RSTVAL
    RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;
EXP_DONE
    JSR PUSH
    ADD R5,R5,#0
    BRp EXP_ERRX
    JSR RSTVAL
    RET
EXP ADD R3, R3, #0
    BRz NO
    AND R0, R0, #0
    AND R1, R1, #0
    ADD R3, R3, #-1
    ADD R1, R3, #0
    AND R3, R3, #0
    ADD R3, R4, #0
EXP_LOOP
    JSR MUL 
    AND R3, R3, #0
    ADD R3, R0, #0
    ADD R1, R1, #-1
    BRp EXP_LOOP
    BRnzp EXP_DONE 
NO
    AND R0,R0,#0
    ADD R0,R0,#1
    BRnzp EXP_DONE

EXP_OP
    JSR STVAL
    JSR POP
    ADD R5, R5, #0
    BRp EXP_ERRX
    ADD R3, R0, #0
    JSR POP
    ADD R5, R5, #0
    BRP EXP_ERRX
    ADD R4, R0, #0
    JSR EXP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input all registers
;output all registers
;Load all values
RSTVAL
    LD R0, T_R0
    LD R1, T_R1
    LD R2, T_R2
    LD R3, T_R3
    LD R4, T_R4
    LD R5, T_R5
    LD R6, T_R6
    LD R7, T_R7
    BRnzp GET_NEXT_CHX

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input all registers
;output all registers
;Store all values
STVAL
    ST R0, T_R0
    ST R1, T_R1
    ST R2, T_R2
    ST R3, T_R3
    ST R4, T_R4
    ST R5, T_R5
    ST R6, T_R6
    ST R7, T_R7
    RET

T_R1 .BLKW #1
T_R2 .BLKW #1
T_R3 .BLKW #1
T_R4 .BLKW #1
T_R5 .BLKW #1
T_R6 .BLKW #1
T_R7 .BLKW #1
T_R0 .BLKW #1

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET

POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
