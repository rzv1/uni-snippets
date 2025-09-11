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
    b dw 1212h
    c dd 33445686h
    d dq 1233212311231221h
; our code starts here
segment code use32 class=code
    start:
        ; (a-b)+(c-b-d)+d
        mov eax, 0
        mov eax, [c]
        sub ax, [b] ; eax = c - b
        mov edx, 0 ; edx:eax = c - b
        sub eax, dword[d]
        sbb edx, dword[d + 4] ; edx:eax = (c - b - d)
        mov bl, [a]
        mov bh, 0 ; bl -> bx
        sub bx, [b] ; bx = (a - b)
        add ax, bx ; edx:eax = (a-b) + (c-b-d)
        add eax, dword[d]
        adc edx, dword[d + 4] ; edx:eax = (a-b) + (c-b-d) + d
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
