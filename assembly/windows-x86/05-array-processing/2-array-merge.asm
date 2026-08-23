bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se dau sirurile de octeti s1 si s2 de lungime l1 si l2. 
    ; Se cere sa se construiasca sirul de lungime l1+l2
    s1 db 1,2,3,4
    l1 equ $-s1
    s2 db 5,6,7,8
    l2 equ $-s2
    ld equ l1 + l2
    d times ld db 0 ; d times (l1+l2) db 0
    
; our code starts here
segment code use32 class=code
    start:
        cld                     ; DF = 0 (parcurgere de la stanga la dreapta)
        mov edi, d              ; EDI pointeaza la sirul destinatie

        mov esi, s1             ; ESI pointeaza la sirul sursa 1
        mov ecx, l1             ; ECX = lungimea primului sir
        jecxz skip_s1           ; Protectie daca l1 == 0
        rep movsb               ; Copiaza octet cu octet din [ESI] in [EDI]
    skip_s1:

        mov esi, s2             ; ESI pointeaza la sirul sursa 2
        mov ecx, l2             ; ECX = lungimea celui de-al doilea sir
        jecxz skip_s2           ; Protectie daca l2 == 0
        rep movsb               ; Continua copierea in d
    skip_s2:

        ; exit(0)
        push    dword 0        
        call    [exit]
