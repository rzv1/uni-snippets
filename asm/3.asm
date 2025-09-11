bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 1234h
    b db 12h
    e dd 43211234h
    x dq 1010101010101010h
    op db 8
    op1 db 2

; our code starts here
segment code use32 class=code
    start:
        ; x-b+8+(2*a-b)/(b*b)+e
        mov ecx, dword[x]
        mov ebx, dword[x+4] ; ebx:ecx
        sub cl, byte[b] ; 
        add cl, byte[op] ; ebx:ecx = x-b+8
        mov ax, word[a]
        mul byte[op1] ; eax = 2*a
        sub al, byte[b] ; eax = 2*a-b
        mov edx, eax ; edx = 2*a-b
        mov eax, 0
        mov al, byte[b]
        mul byte[b] ; eax = b * b
        push eax
        mov eax, edx
        pop edx
        div dx
        adc 
        
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
