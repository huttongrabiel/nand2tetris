// Fill the screen with black (-1) pixels when any key is pressed (@KBD != 0)
// And fill the screen with white (0) pixels when no key is pressed

// Solved May 21, 2022 (much quicker this time and less than half the amount of code :^))

@pixel
M=0

(KEY_EVENT_LOOP)
    @SCREEN
    D=M
    @count
    M=D

    @KBD
    D=M
    @KEY_EVENT
    D; JNE
    @NO_KEY_EVENT
    D; JEQ

    (POST_EVENT_HANDLE)
        @KBD
        D=A
        @count
        A=M
        @KEY_EVENT_LOOP
        D-A; JEQ
        @pixel
        D=M
        @count
        M=D
        @count
        A=A+1
        @POST_EVENT_HANDLE
        0; JMP

(KEY_EVENT)
    @pixel
    M=-1
    @POST_EVENT_HANDLE
    0; JMP

(NO_KEY_EVENT)
    @pixel
    M=0
    @POST_EVENT_HANDLE
    0; JMP