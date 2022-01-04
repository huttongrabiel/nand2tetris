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
// while(KBD != 0) {
//  screen = black
// }
// else {
//  screen = white;
// 
// to make screen black we need to change
// each bit in the memory map which means
// every single word must be changed
// we need to write every bit from
// 16384 to 24576 to either 1 or 0
// 
// if we save SCREEN to addr we can change the M
// value at addr which means n must be set to 8192

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

(STARTLOOP)

  @KBD
  D=M
  @LOOP
  D;JGT // jump if KBD is greater than 0
  @STARTLOOP
  0;JMP // otherwise stay in this loop

(LOOP)
  @i
  D=M
  @n
  D=D-M
  @END
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
  D;JEQ // jump to startloop if kbd is 0

  @LOOP
  0;JMP

(END)
  @END
  0;JMP
