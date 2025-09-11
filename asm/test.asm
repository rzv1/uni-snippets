bits 32                ; Cod pentru arhitectura pe 32 de biți

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit            ; specificăm că exit există, chiar dacă nu o definim aici
import exit msvcrt.dll ; exit este o funcție din msvcrt.dll

; segment de date (variabilele necesare)
segment data use32 class=data
    s db 5, 25, 55, 127 ; Sirul sursă
    l equ $ - s         ; Lungimea sirului sursă (nr. de elemente)
    d times l db 0      ; Sirul destinație (inițializat cu 0)

; segmentul de cod
segment code use32 class=code
    start:
        ; Inițializări de bază pentru cod
        mov esi, s          ; Pointer pentru sirul sursă
        mov edi, d          ; Pointer pentru sirul destinație
        mov ecx, l          ; Numărul de elemente din sirul sursă
        cld                 ; Resetăm flag-ul de direcție pentru LODSB și STOSB

    main_loop:
        JECXZ sfarsit       ; Dacă ECX este 0, ieșim

        LODSB               ; Încărcăm următorul element din s în AL
        mov edx, eax        ; Mutăm valoarea din AL în EDX pentru a număra biții
        xor bl, bl          ; Resetăm BL pentru a număra biții de 1

    count_bits_loop:
        test dl, 1          ; Verificăm ultimul bit al lui DL
        jz no_increment     ; Dacă este 0, sărim peste incrementare
        inc bl              ; Dacă este 1, incrementăm contorul

    no_increment:
        shr dl, 1           ; Shiftăm DL la dreapta pentru a verifica următorul bit
        jnz count_bits_loop ; Repetăm până când DL devine 0

        mov al, bl          ; Mutăm numărul de biți de 1 în AL
        stosb               ; Stocăm valoarea lui AL în sirul destinație
        loop main_loop      ; Repetăm pentru fiecare element din sirul sursă

    sfarsit:
        ; exit(0)
        push dword 0        ; Parametru pentru exit
        call [exit]         ; Apelăm exit pentru a termina programul