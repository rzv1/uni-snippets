bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf             ; tell nasm that exit exists even if we won't be defining it
import printf msvcrt.dll
import scanf msvcrt.dll
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 0
    b dw 0
    v db 17
    rezultat dd 0
    message db "%hd * %hd = %d", 0
    format db "%hd", 0

; our code starts here
segment code use32 class=code
    start:
        mov eax, v
        lea ebx, [v]
        mov eax, [23]
        push dword a
        push dword format
        call [scanf] ;scanf("%s", a)
        add esp, 4 * 2
        push dword b
        push dword format
        call [scanf]
        add esp, 4 * 2
        mov ax, [a]
        imul word[b] ; dx:ax = a*b
        shl edx, 16
        or eax, edx ; eax = a*b
        add [rezultat], eax
        push dword [rezultat]
        mov eax, 0
        mov ax, [b]
        push eax
        mov ax, [a]
        push eax
        push dword message
        call [printf]
        add esp, 4 * 4
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
