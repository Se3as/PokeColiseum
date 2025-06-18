section .data
effectiveness_table: 
    dd 100, 100, 100,   ; Normal
    dd 100,  50,  50,   ; Fuego
    dd 100, 200,  50,   ; Agua

section .text
    global get_effectiveness
;rdi: tipo_atacante (int)
;rsi: tipo_defensor (int)
;eax: multiplicador de efectividad (50, 100, 200)
get_effectiveness:
    mov     rax, rdi
    imul    rax, 3
    add     rax, rsi
    mov     eax, [effectiveness_table + rax*4]
    ret