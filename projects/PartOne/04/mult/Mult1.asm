// RAM[2] = RAM[0] * RAM[1]

// for (int i = 0; i < RAM[1]; i++) {
//      RAM[2] = RAM[2] + RAM[0];
// }

// Solved May 21, 2022 second time solution is much better than first time

(loop)
    @R1
    D=M
    @end
    D; JEQ
    @R0
    D=M
    @R2
    M=M+D
    @R1
    M=M-1
    @loop
    0; JMP

(end)
    0; JMP    