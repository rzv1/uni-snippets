bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 20h
    b db 10h
    c db 3h
    d dw 4h
    op db 2h

; our code starts here
segment code use32 class=code
    start: ; -a*a + 2*(b-1) - d
        mov al, byte[a]
        neg al
        mov ah, 0
        mul byte[a]
        mov bx, ax
        mov al, byte[b]
        dec al
        mov ah, 0
        mul byte[op]
        add ax, bx
        sub ax, word[d]
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
