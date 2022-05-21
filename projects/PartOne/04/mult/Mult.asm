// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

// R2 = R0 * R1
// All that means in that we loop the addition
// by the amount that is the number we want to multiply by
// so leaving R0 alone, we can take the value of R1 and add
// R0 to itself R1 times, this is done with a loop and a product
// variable (product is really a sum in this case but it works
// Pseudo Code
//
//   r0 = 4
//   r1 = 6 // 4*6 = 24
//   product = 0
//   i = 0
//
//   for (i = 0; i < r1; i++) {
//     product += r0;
//   }

@R2
M=0 // product = 0
@i 
M=0

@R1
D=M // saving the value of M into the D register
@n
M=D

(LOOP)
  @i
  D=M
  @n
  D=D-M
  @END
  D;JEQ // if i-r1=0 goto END

  @R0
  D=M
  @R2
  M=M+D // product += r0

  @i
  M=M+1 // i++

  @LOOP
  0;JMP // loop again

(END)
  @END
  0;JMP // infinite loop to terminate program, beat it nop sled
