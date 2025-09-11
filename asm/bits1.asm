bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
     A db 10010100b
     B db 0
     C dd 0

; our code starts here
segment code use32 class=code
    start:
        ; Se da octetul A. Sa se obtina numarul intreg n reprezentat de bitii 2-4 ai lui A.
        ;Sa se obtina apoi in B octetul rezultat prin rotirea spre dreapta a lui A cu n pozitii. 
        ;Sa se obtina dublucuvantul C:

        ;bitii 8-15 ai lui C sunt 0
        ;bitii 16-23 ai lui C coincid cu bitii lui B
        ;bitii 24-31 ai lui C coincid cu bitii lui A
        ;bitii 0-7 ai lui C sunt 1
        
        mov cl, [A]
        and cl, 00011100b
        ror cl, 2 ; cl = n
        mov ah, [A]
        ror ah, cl
        mov [B], ah
        or dword[C], 0FFh
        mov eax, 0
        mov al, [B]
        shl eax, 16
        or [C], eax
        mov edx, 0
        mov dl, [A]
        shl edx, 24
        or [C], edx
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
