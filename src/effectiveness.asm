section .data
    ; tabla de efectividad de tipos
    ; columnas: tipo del movimiento
    ; filas: tipo del oponente
    ; valores: 0 = poco efectivo, 1 = neutral, 2 = super efectivo

    effectiveness_chart:
        ;Nor Fue Agu Pla Ele Hie Luc Ven Tie Vol Psi Bic Roc Fan Dra Sin Ace Had
        dd 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1    ; NORMAL
        dd 1, 0, 0, 2, 1, 2, 1, 1, 1, 1, 1, 2, 0, 1, 0, 1, 2, 1    ; FUEGO
        dd 1, 2, 0, 0, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 0, 1, 1, 1    ; AGUA
        dd 1, 0, 2, 0, 1, 1, 1, 0, 2, 0, 1, 0, 2, 1, 0, 1, 0, 1    ; PLANTA
        dd 1, 1, 2, 0, 0, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0, 1, 1, 1    ; ELECTRICO
        dd 1, 0, 0, 2, 1, 0, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 0, 1    ; HIELO
        dd 2, 1, 1, 1, 1, 2, 1, 0, 1, 0, 0, 0, 2, 0, 1, 2, 2, 0    ; LUCHA
        dd 1, 1, 1, 2, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 2    ; VENENO
        dd 1, 2, 1, 0, 2, 1, 1, 2, 1, 0, 1, 0, 2, 1, 1, 1, 2, 1    ; TIERRA
        dd 1, 1, 1, 2, 0, 1, 2, 1, 1, 1, 1, 2, 0, 1, 1, 1, 0, 1    ; VOLADOR
        dd 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1    ; PSIQUICO
        dd 1, 0, 1, 2, 1, 1, 0, 0, 1, 0, 2, 1, 1, 0, 1, 2, 0, 0    ; BICHO
        dd 1, 2, 1, 1, 1, 2, 0, 1, 0, 2, 1, 2, 1, 1, 1, 1, 0, 1    ; ROCA
        dd 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0, 1, 1    ; FANTASMA
        dd 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0, 0    ; DRAGON
        dd 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 2, 1, 1, 2, 1, 0, 1, 0    ; SINIESTRO
        dd 1, 0, 0, 1, 0, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 0, 2    ; ACERO
        dd 1, 0, 1, 1, 1, 1, 2, 0, 1, 1, 1, 1, 1, 1, 2, 2, 0, 1    ; HADA

section .text
    global get_effectiveness

get_effectiveness:
    ;rdi: tipo_atacante (int)
    ;rsi: tipo_defensor (int)

    push rbx

    dec rdi
    dec rsi ; para que cuadren con la tabla

    mov rax, rdi
    imul rax, 18
    add rax, rsi
    imul rax, 4 ;offset para la tabla por el dd

    lea rbx, [rel effectiveness_chart] ;tabla
    add rax, rbx ;valor en la tabla

    mov eax, dword [rax]

    pop rbx
    ret