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
    b dw 1234h
    c dd 12345678h
    d dq 123456781234h

; our code starts here
segment code use32 class=code
    start:
        ; (b+b) - c - (a+d)
        mov eax, 0
        mov ax, [b]
        add ax, [b] ; ax = b + b
        cwde ; eax = b + b
        sub eax, [c] ; eax = (b+b) - c
        mov edx, 0 ; edx:eax = (b+b) - c
        mov ebx, dword[d]
        mov ecx, dword[d + 4] ; ecx:ebx = d
        add bl, [a] ; ecx:ebx = a + d
        sub eax, ebx 
        sbb edx, ecx ; edx:eax = (b+b)-c-(a+d)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
