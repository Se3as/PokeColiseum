section .text
global ai_make_a_move
extern time
; si se agregan mas pokemon se puede mejorar con un numero random para que tenga una probabiliad de cambiar pokemon si la vida de su pokemon es menor al 20%

ai_make_a_move:
    xor eax, eax
    mov edi, 0             
    call time           
    
    mov ecx, eax           
    imul ecx, 0x8088405     ; <-- multiplicador para usar la semilla del tiempo del pc
    inc ecx
    mov eax, ecx
    shr eax, 24             ; <-- se usan los bitsmas significativos
    
    ; mi rango ira de 3 a 6 que son los movimientos disponibles para la maquina
    and eax, 0x3           
    add eax, 3              ; 3-6
    ret