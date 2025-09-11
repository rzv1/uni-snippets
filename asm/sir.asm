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
    s db 1,5,2,8,4
    l equ $ - s
    d times l - 1 db 0 ;alocam l-1 octeti pentru d

; our code starts here
segment code use32 class=code
    start:
        ; Se da un sir de octeti s de lungime l. Sa se construiasca sirul g de lungime l-1 a.i. el lui d reprezinta catul dintre fiecare 
        ;    doua el consecutive si si si+1 din s.
        ; s: 1,5,2,8,4
        ; g: 0,2,0,2
        ; esi - index pentru sursa , edi - index pentru destinatie
        mov ecx, l - 1
        mov esi, 0
        jecxz sfarsit
        repeta:
        mov al, [s + esi]
        mov bl, [s + esi + 1]
        mov ah, 0
        div bl ; al = ax / bl
        mov [d + esi], al
        inc esi
        loop repeta
        sfarsit:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
