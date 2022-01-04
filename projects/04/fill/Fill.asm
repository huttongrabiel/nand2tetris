// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

// Pseudo Code
//
// if key == 0 just listen
// if key > 0 start blackenLoop
//  (LOOP)
//    write 1 into each bit in each word
//    if key == 0
//      write a 0 into each bit in each word

@KBD
D=M

@SCREEN
D=A
@addr
M=D

@8192
D=A
@n
M=D

@i
M=0

@SCREEN
D=A
@addr1
M=D

@j
M=0

(STARTLOOP)
  @SCREEN
  D=A
  @addr
  M=D // reset addr to start of memory map

  @i
  M=0 // reset i to 0

  @KBD
  D=M
  @LOOP
  D;JGT // jump if KBD is greater than 0

  @SCREEN
  D=A
  @addr1
  M=D // reset addr1 to start of memory map

  @j
  M=0 // reset j to 0
  
  @KBD
  D=M
  @LOOP1
  D;JEQ // jump if KBD is 0

  @STARTLOOP
  0;JMP // otherwise stay in this loop

(LOOP) // turns each bit in every word to 1
  @i
  D=M
  @n
  D=D-M
  @STARTLOOP
  D;JEQ // if i == n, goto end

  @addr
  A=M
  M=-1

  @i
  M=M+1 // i++

  @addr
  M=M+1 // increment addr by 1, draws one solid horizontal line

  @KBD
  D=M
  @STARTLOOP
  D;JEQ // jump to startloop which is treated as a hub

  @LOOP
  0;JMP

(LOOP1)
  @j
  D=M
  @n
  D=D-M
  @STARTLOOP
  D;JEQ

  @addr1
  A=M
  M=0

  @j
  M=M+1

  @addr1
  M=M+1

  @KBD
  D=M
  @STARTLOOP
  D;JGT // jump to startloop which is treated as a hub

  @LOOP1
  0;JMP

(END)
  @END
  0;JMP
