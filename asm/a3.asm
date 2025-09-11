bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 1000h
    b dw 4444h
    c dw 1021h
    d dw 1213h

; our code starts here
segment code use32 class=code
    start:
        ; (b+b) - c - (a+d)
        mov ax, word[b]
        add ax, word[b] ; ax = b + b
        mov dx, word[a]
        add dx, word[d] ; dx = a + d
        sub ax, word[c] ; ax = (b+b)-c
        sub ax, dx ; ax = (b+b)-c-(a+d)
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
