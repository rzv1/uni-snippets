bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 10h
    b db 12h
    c db 15h
    d db 20h
    e dw 10h
    f dw 7h
    g dw 15h
    h dw 12h
    op db 3

; our code starts here
segment code use32 class=code
    start:
        ; (a-c)*3+b*b 
        mov al, byte[a]
        sub al, byte[c] ; al = a-c
        mul byte[op] ; ax = (a-c)*3
        mov bx, ax ; bx = (a-c)*3
        mov al, byte[b] ;al = b
        mul byte[b] ;ax = b*b
        add ax, bx ; ax = (a-c)*3+b*b
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
