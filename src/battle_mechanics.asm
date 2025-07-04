section .data
    resist: dd 0.5
    weak:   dd 1.5

section .text
global calculate_combat_damage

calculate_combat_damage:
    ; rdi --> tiene la vida actual del pokemon 
    ; rsi --> tiene el damage del movimiento usado
    ; rdx --> efectividad 0 = x0.5, 1 = x1, 2 = x1.5
    ; eax --> salida con el hp restante después del ataque 

    cvtsi2ss xmm0, esi 

    cmp edx, 0
    je .not_very_effective ; si el movimiento es x0.5 efectivo

    cmp edx, 1
    je .apply_damage ; no hace nada especial porque no hay multiplicador

    cmp edx, 2
    je .super_effective

    jmp .result

.not_very_effective:
    movss xmm1, dword [resist]
    mulss xmm0, xmm1
    jmp .apply_damage

.super_effective:
    movss xmm1, dword [weak]
    mulss xmm0, xmm1
    jmp .apply_damage

.apply_damage:

    cvttss2si eax, xmm0

    cmp eax, edi 
    jge .pokemon_fainted

    mov ecx, edi 
    sub ecx, eax 
    mov eax, ecx 
    ret 

.pokemon_fainted:
    xor eax, eax
    ret

.result:
    mov eax, edi 
    ret