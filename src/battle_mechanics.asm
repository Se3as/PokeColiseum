section .text
global calculate_combat_damage

calculate_combat_damage:
    ; rdi --> tiene la vida actual del pokemon 
    ; rsi --> tiene el damage del movimiento usado
    ; eax --> salida con el hp restante después del ataque 

    mov rax, rdi  ; hp
    mov rcx, rsi  ; damage
    
    cmp rcx, rax
    jge .pokemon_fainted
    sub rax, rcx
    ret

.pokemon_fainted:
    xor eax, eax    ; <-- si pokemon queda debilitado vida = 0
    ret