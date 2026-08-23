bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 12h
    b dw 1231h
    c dd 34543543h
    d dq 1111111111111111h

; our code starts here
segment code use32 class=code
    start:
        ; a-b-(c-d)+d
        mov ebx, 0
        mov bl, byte[a]
        cbw
        sub bx, word[b] ; bx = a - b
        
        mov eax, dword[c] ; eax = c
        mov edx, 0 ; edx:eax = c
        sub eax, dword[d]
        sbb edx, dword[d+4] ; edx:eax = c-d
        add eax, dword[d]
        adc edx, dword[d+4] ; edx:eax = c-d+d
        mov ecx, 0 ; ecx:ebx = a-b
        sub ecx, edx
        sbb ebx, eax ; ecx:rbx = a-b-(c-d)+d
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
