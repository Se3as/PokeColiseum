section .bss
    ; Reserve space for the health of each Pokemon
    buffer resb 20  ; Buffer for input
    number resq 1 ; Reserve space for a number (64 bits)
    outbuffer resb 20 ; Output buffer for printing numbers
    r8 resq 1 ; Max health of Pokemon 1
    r9 resq 1 ; Max health of Pokemon 2
    r10 resq 1 ; Current health of Pokemon 1
    r11 resq 1 ; Current health of Pokemon 2
    r12 resq 1 ; Damage received by Pokemon 1
    r13 resq 1 ; Damage received by Pokemon 2

section .data
    ; Messages
    maxHealthPokemon1 db 'Digite la salud total del pokemon 1: ', 0
    len_maxHealthPokemon1 equ $ - maxHealthPokemon1
    maxHealthPokemon2 db 'Digite la salud total del pokemon 2: ', 0
    len_maxHealthPokemon2 equ $ - maxHealthPokemon2
    currentHealthPokemon1 db 'Salud actual del pokemon 1: ', 0
    len_currentHealthPokemon1 equ $ - currentHealthPokemon1
    currentHealthPokemon2 db 'Salud actual del pokemon 2: ', 0
    len_currentHealthPokemon2 equ $ - currentHealthPokemon2
    damageReceived db 'Damage recibido: ', 0
    len_damageReceived equ $ - damageReceived
    newline db 10, 0
    buffer times 5 db 0

section .text
    global main
main:
    call initialize_pokemon_health
    call battle_loop

 
battle_loop:
    ; Print damage received of Pokemon 1
    call print_damageReceived
    call read_int
    mov r12, rax ; Store the damage received by Pokemon 1 in r12
    call print_Newline
    ; Update health of Pokemon 1
    sub r10, r12
    cmp r10, 0
    jl pokemon1_fainted
    ; Print updated health of Pokemon 1
    call print_currentHealthPokemon1
    mov rax, r10
    call print_int
    call print_Newline
    call clear_buffer
    ; Update health of Pokemon 2
    call print_damageReceived
    call read_int
    mov r13, rax ; Store the damage received by Pokemon 2 in r13
    call print_Newline
    sub r11, r13
    cmp r11, 0
    jl pokemon2_fainted
    ; Print updated health of Pokemon 2
    call print_currentHealthPokemon2
    mov rax, r11
    call print_int
    call print_Newline
    call clear_buffer
    jmp battle_loop

initialize_pokemon_health:
    ; Initialize the health of both Pokemon
    call print_maxHealthPokemon1
    call read_int
    mov r10, rax ; Max health of Pokemon 1 (Charmander)
    call print_Newline

    call print_maxHealthPokemon2
    call read_int
    mov r11, rax ; Max health of Pokemon 2 (Totodile)
    call print_Newline
    ret


pokemon1_fainted:
    ; Pokemon 1 has fainted
    call print_currentHealthPokemon1
    mov rax, 0
    call print_int
    call print_Newline
    call clear_buffer
    call print_damageReceived
    mov rax, r12
    call print_int
    call print_Newline
    jmp end_battle
pokemon2_fainted:
    ; Pokemon 2 has fainted
    call print_currentHealthPokemon2
    mov rax, 0
    call print_int
    call print_Newline
    call clear_buffer
    call print_damageReceived
    mov rax, r13
    call print_int
    call print_Newline
end_battle:
    ; End battle
    call print_Newline
    call print_damageReceived
    mov rax, 0
    call print_int
    call print_Newline
    jmp end_program


printmessage:
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    syscall
    ret

; Funciones específicas para cada mensaje
print_maxHealthPokemon1:
    mov rsi, maxHealthPokemon1
    mov rdx, len_maxHealthPokemon1
    call printmessage
    ret

print_maxHealthPokemon2:
    mov rsi, maxHealthPokemon2
    mov rdx, len_maxHealthPokemon2
    call printmessage
    ret

print_currentHealthPokemon1:
    mov rsi, currentHealthPokemon1
    mov rdx, leprintn_currentHealthPokemon1
    call printmessage
    ret

print_currentHealthPokemon2:
    mov rsi, currentHealthPokemon2
    mov rdx, len_currentHealthPokemon2
    call printmessage
    ret

print_damageReceived:
    mov rsi, damageReceived
    mov rdx, len_damageReceived
    call printmessage
    ret

print_newline:
    mov rsi, newline
    mov rdx, len_newline
    call printmessage
    ret


.convert_loop:
    xor rdx, rdx        ; Clean RDX for division
    div rbx             ; RAX = Quotient , RDX = rest
    add dl, '0'         ; Convert to ASCII
    dec rsi             ; Move pointer
    mov [rsi], dl       ; Store ASCII character
    test rax, rax       ; ¿Cociente cero?
    jnz .convert_loop
    
.print:
    ; Calcular longitud (newline incluido)
    lea rdx, [buffer+20] ; Fin del buffer
    sub rdx, rsi         ; Longitud = fin - posición actual
    
    ; Llamada al sistema para escribir
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    syscall
    ret

clear_buffer:
    ; Clear the buffer
    lea rdi, [buffer]
    mov rcx, 5
    xor al, al
    rep stosb
    ret


read_int:
    ; syscall read
    mov rax, 0
    mov rdi, 0
    mov rsi, buffer
    mov rdx, 20
    syscall

    ; convertir ASCII → número
    xor rcx, rcx        ; resultado
    xor rbx, rbx        ; índice

.read_loop:
    mov al, [buffer + rbx]
    cmp al, 10          ; '\n'
    je .done
    sub al, '0'
    imul rcx, rcx, 10
    add rcx, rax
    inc rbx
    jmp .read_loop

.done:
    mov rax, rcx        ; devolver resultado en RAX
    ret

; ------------------------------------------
; print_int: imprime número en RAX
; ------------------------------------------
print_int:
    mov rcx, rax         ; copia de RAX para dividir
    mov rsi, outbuf + 19
    mov byte [rsi], 10   ; '\n'
    dec rsi

.convert_loop:
    xor rdx, rdx
    mov rbx, 10
    div rbx              ; RAX / 10 → RAX=cociente, RDX=resto
    add dl, '0'
    mov [rsi], dl
    dec rsi
    test rax, rax
    jnz .convert_loop

    inc rsi
    ; write syscall
    mov rax, 1
    mov rdi, 1
    mov rdx, outbuf + 20
    sub rdx, rsi
    mov rsi, rsi
    syscall
    ret


initialize_pokemon_health:
    ; Initialize the health of both Pokemon
    mov r10, 0        ; Max health of Pokemon 1 (Charmander)
    mov r11, 0        ; Max health of Pokemon 2 (Totodile)

    ret

_start:
    call initialize_pokemon_health
    call battle_loop

    ; Exit the program
    mov rax, 60       ; syscall: exit
    xor rdi, rdi      ; status: 0
    syscall