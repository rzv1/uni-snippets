bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 1221h
    b db 20h
    c db 20h
    d db 10h
    op dw 2
    op1 db 2
    e dd 12211221h
    x dq 1221122113311331h

; our code starts here
segment code use32 class=code
    start: ; (a*2+b/2+e)/(c-d)+x/a
        mov eax, 0
        mov ax, word[op]
        mul word[a] ; dx:ax = a * 2
        push dx
        push ax
        mov al, [b]
        mov ah, 0 ; ax = b
        div byte[op1] ; al = b/2 , ah = b%2
        mov bl, al
        pop ax
        pop dx
        add al, bl
        add ax, [e]
        add dx, [e+2] ;dx:ax = a*2+b/2+e
        mov bl, [c]
        sub bl, [d]
        mov bh, 0
        div bx ; ax = (a*2+b/2+e)/(c-d)
        mov bx, ax ; bx = ax
        mov eax, dword[x]
        mov edx, dword[x+4]
        mov ecx, 0
        mov cx, [a] ; ecx = a
        div ecx ; eax = x/a
        add ax, bx ; eax = (a*2+b/2+e)/(c-d)+x/a
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
