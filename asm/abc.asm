bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fopen msvcrt.dll                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "pb4.txt", 0
    mod_acces db "r", 0
    descriptor dd -1
    len equ 100
    text times len db 0
    format db "Valoarea este: %u", 0
    
; our code starts here
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]  ; eax = descriptor fisier
        add esp, 4 * 2
        mov [descriptor], eax
        cmp eax, 0
        je final
        push dword [descriptor]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4 * 4
        mov ecx, eax
        mov esi, text
        xor ebx, ebx
        CLD
        repeta:
            lodsb
            test al, 1
            jz no_increment
            inc ebx
            no_increment:
            dec ecx
        jnz repeta
        push dword [descriptor]
        call [fclose]
        add esp, 4
        
        push dword ebx
        push dword format
        call [printf]
        add esp, 4 * 2
        ; exit(0)
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
