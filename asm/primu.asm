bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 10h
    b dw 9h
    c dd 31241232h
    d dq 123321231123h
; our code starts here
segment code use32 class=code
    start:
        ; (a-b)+(c-b-d)+d
        mov eax, 0
        mov al, byte[a] 
        mov ah, 0
        sub ax, word[b] ; ax = a - b
        mov dx, 0 ; ax -> dx:ax
        mov edx, 0 ; eax -> edx:eax
        add eax, dword[c]
        sub ax, word[b]
        sub eax, dword[d]
        sub edx, dword[d + 2]
        add eax, dword[d]
        add edx, dword[d + 2]
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
