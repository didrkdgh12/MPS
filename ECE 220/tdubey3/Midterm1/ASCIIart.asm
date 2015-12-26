;Load ASCII art character, stored at memory address x5000 (IMAGEADDR)
;The first two numbers are the width (number of columns) and the height (number of rows) in the ASCII art image
;The memory addresses starting at x5002 are ASCII characters. The first N characters are the first row of the image, the second N characters are the second row of the image, etc.
;each row should end with a newline character

.ORIG x3000
;YOUR CODE GOES HERE
	AND R0, R0, #0 ; System Reserved (Print)
	AND R1, R1, #0 ; X Coord (N)
	AND R2, R2, #0 ; Y Coord (M)
	AND R3, R3, #0 ; Current Char
	AND R4, R4, #0
	AND R5, R5, #0
	AND R6, R6, #0 ; Value of current Address
	AND R7, R7, #0 ; System Reserved
	
	LD R6, IMAGEADDR ; Load R6 with starting addr
	LDR R1, R6, #0	 ; Load X Coord
	ST R1, IMGX
	ADD R6, R6, #1
	LDR R2, R6, #0	 ; Load Y Coord
	ST R2, IMGY
LOOPN
	ADD R2, R2, #-1
	BRn DONE
	AND R1, R1, #0;
	LD R1, IMGX
LOOPM
	ADD R6, R6, #1
	AND R0, R0, #0
	LDR R0, R6, #0
	OUT
	ADD R1, R1, #-1
	BRnz LOOPSET
	BRnzp LOOPM
LOOPSET
	AND R0, R0, #0
	ADD R2, R2, #0
	BRz DONE
	LD R0, NLINE
	OUT
	BRnzp LOOPN
	

DONE
	HALT


IMAGEADDR	.FILL x5000 ; address of image
IMGX		.BLKW #1 ;X OF IMAGE
IMGY		.BLKW #1 ;Y OF IMAGE
NLINE 		.FILL x000A ; NEW LINE CHAR
.END
