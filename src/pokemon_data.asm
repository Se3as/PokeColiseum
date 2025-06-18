section .data
pokedex:
    dd 0, 146, 7     ; Charmander (id, health, type:fire)
    dd 1, 157, 2     ; Totodile (id, health, type:water)
entries_count equ ($ - pokedex) / 12  ; Calcula automáticamente el número de entradas

section .text
global getPokemonHealth
global getPokemonType

getPokemonHealth:
    ; Input: edi = int id (32-bit)
    lea rsi, [rel pokedex]       ; Usamos rsi en lugar de rbx (no necesita preservarse)
    xor eax, eax                 ; eax = loop index (i = 0)


.loop:
    cmp eax, entries_count       ; Compara con el número calculado de entradas
    jge .not_found

    ; Calcula offset (eax * 12)
    mov edx, eax
    imul edx, edx, 12

    cmp edi, [rsi + rdx]         ; Compara el ID buscado
    je .found

    inc eax
    jmp .loop


.found:
    mov eax, [rsi + rdx + 4]     ; Devuelve el health
    ret


.not_found:
    mov eax, -1                  ; Devuelve -1 si no se encuentra
    ret


getPokemonType:
    ; Input: edi = int id (32-bit)
    lea rsi, [rel pokedex]       ; Usamos rsi en lugar de rbx (no necesita preservarse)
    xor eax, eax                 ; eax = loop index (i = 0)


.loop_type:
    cmp eax, entries_count       ; Compara con el número calculado de entradas
    jge .not_found_type

    ; Calcula offset (eax * 12)
    mov edx, eax
    imul edx, edx, 12
    cmp edi, [rsi + rdx]         ; Compara el ID buscado
    je .found_type

    inc eax
    jmp .loop_type


.found_type:
    mov eax, [rsi + rdx + 8]     ; Devuelve el tipo
    ret

    
.not_found_type:
    mov eax, -1                  ; Devuelve -1 si no se encuentra
    ret


section .note.GNU-stack noalloc noexec nowrite progbits