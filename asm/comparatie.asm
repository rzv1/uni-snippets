bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db 25h, 5h, 2h, 24h
    l equ $ - s
    l_squared equ l * l
    d times l db 0
    zero db 0

; our code starts here
segment code use32 class=code
    start:
        mov esi, s
        mov edi, d
        mov ecx, l_squared
        CLD
        
        JECXZ sfarsit
        main:
        STOSB
        push esi
        comparison:
            mov bl, [s + esi]
            cmp al, bl
            JGE no_swap
            mov dl, al
            mov al, bl
            mov bl, dl
            no_swap:
            inc esi
            cmp zero,   [s + esi]
        JE comparison
        pop esi
        loop main
        sfarsit:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
