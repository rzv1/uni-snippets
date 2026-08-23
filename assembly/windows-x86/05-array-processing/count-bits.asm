bits 32                ; Cod pentru arhitectura pe 32 de biti

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit            ; specificam ca exit exista, chiar daca nu o definim aici
import exit msvcrt.dll ; exit este o functie din msvcrt.dll

; segment de date (variabilele necesare)
segment data use32 class=data
    s db 5, 25, 55, 127 ; Sirul sursa
    l equ $ - s         ; Lungimea sirului sursa (nr. de elemente)
    d times l db 0      ; Sirul destinatie (initializat cu 0)

; segmentul de cod
segment code use32 class=code
    start:
        ; Initializari de baza pentru cod
        mov esi, s          ; Pointer pentru sirul sursa
        mov edi, d          ; Pointer pentru sirul destinatie
        mov ecx, l          ; Numarul de elemente din sirul sursa
        cld                 ; Resetam flag-ul de directie pentru LODSB si STOSB

    main_loop:
        JECXZ sfarsit       ; Daca ECX este 0, iesim

        LODSB               ; Incarcam urmatorul element din s in AL
        mov edx, eax        ; Mutam valoarea din AL in EDX pentru a numara bitii
        xor bl, bl          ; Resetam BL pentru a numara bitii de 1

    count_bits_loop:
        test dl, 1          ; Verificam ultimul bit al lui DL
        jz no_increment     ; Daca este 0, sarim peste incrementare
        inc bl              ; Daca este 1, incrementam contorul

    no_increment:
        shr dl, 1 ; Shiftam DL la dreapta pentru a verifica urmatorul bit
        jnz count_bits_loop ; Repetam pana cand DL devine 0

        mov al, bl ; Mutam numarul de biti de 1 in AL
        stosb ; Stocam valoarea lui AL in sirul destinatie
        loop main_loop ; Repetam pentru fiecare element din sirul sursa

    sfarsit:
        ; exit(0)
        push dword 0
        call [exit]