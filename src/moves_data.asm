section .data
moves:
    dd 0, 0, 70,  ; Slash, type: normal, 70 damage
    dd 1, 1, 40,   ; Ember, type: fire, 40 damage      
    dd 2, 1, 90,   ; Flamethrower, type: fire, 90 damage
    dd 4, 2, 110,  ; Hydro Pump, type: water, 110 damage
    dd 6, 2, 40,   ; Water Gun, type: water, 40 damage
    
    entries_count equ ($ - moves) / 12  ; Calculates the number of entries automatically
; moves: id, type, damage
; Normal 0, fuego 1, agua 2

section .text
global getMoveDamage
global getMoveType
getMoveDamage:
    ; Input: edi = int id (32-bit)
    lea rsi, [rel moves]       ; rsi instead of rbx (no need to preserve)
    xor eax, eax                 ; eax = loop index (i = 0)


.loop:
    cmp eax, entries_count       ; Compares with the calculated number of entries
    jge .not_found

    ; Calculates offset (eax * 12)
    mov edx, eax
    imul edx, edx, 12

    cmp edi, [rsi + rdx]         ; Compares the searched ID
    je .found

    inc eax
    jmp .loop


.found:
    mov eax, [rsi + rdx + 8]     ; Returns the damage
    ret


.not_found:
    mov eax, -1                  ; Returns -1 if not found
    ret


getMoveType:
    ; Input: edi = int id (32-bit)
    lea rsi, [rel pokedex]       ; rsi instead of rbx (no need to preserve)
    xor eax, eax                 ; eax = loop index (i = 0)


.loop_type:
    cmp eax, entries_count       ; compares with the calculated number of entries
    jge .not_found_type

    ; Calcula offset (eax * 12)
    mov edx, eax
    imul edx, edx, 12

    cmp edi, [rsi + rdx]         ; compares the searched ID
    je .found_type

    inc eax
    jmp .loop_type


.found_type:
    mov eax, [rsi + rdx + 4]     ; returns the type
    ret


.not_found_type:
    mov eax, -1                  ; returns -1 if not found
    ret


section .note.GNU-stack noalloc noexec nowrite progbits
