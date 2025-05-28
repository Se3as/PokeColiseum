section .bss
    ; Reserve space for the health of each Pokemon
    healthPokemon1 resb 4
    healthPokemon2 resb 4

    ; Reserve space for the damage received
    damageReceived resb 4

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
    ; Main battle loop
    call print_CurrentHealthPokemon1
    call print_Newline
    call print_CurrentHealthPokemon2
    call print_Newline




initialize_pokemon_health:
    call print_GetMaxHealthPokemon1
    call read_input
    mov r8, rax ; Store the max health of Pokemon 1 in r8
    call print_Newline
    call clear_buffer
    call print_GetMaxHealthPokemon2
    call read_input
    mov r9, rax ; Store the max health of Pokemon 2 in r9
    call print_Newline
    call clear_buffer
    ret

section .data
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
    len_newline equ $ - newline

section .text
    global _start

; Función genérica para imprimir (64 bits)
; Parámetros: rsi = mensaje, rdx = longitud
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

_start:
    call print_maxHealthPokemon1
    call print_newline
    
    call print_maxHealthPokemon2
    call print_newline
    
    call print_currentHealthPokemon1
    call print_newline
    
    call print_currentHealthPokemon2
    call print_newline
    
    call print_damageReceived
    call print_newline

    ; End program
    mov rax, 60         ; sys_exit
    xor rdi, rdi        ; Exit code 0
    syscall

print_int:
    mov rax, r10        ; Value to print
    lea rsi, [buffer+19] ; Pointer at the end of the buffer
    mov byte [rsi], 10   ; Newline character
    mov rbx, 10          ; Decimal conversion base
    
    ; Case of 0
    test rax, rax
    jnz .convert_loop
    dec rsi
    mov byte [rsi], '0'
    jmp .print
    
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

read_input:
    mov rax, 0             ; syscall read  
    mov rdi, 0             ; stdin
    mov rsi, buffer        ; rsi points to the buffer
    mov rdx, 4             ; read 4 bytes
    syscall
    
    mov rsi, buffer
    call atoi

    ; Store the result in rax

atoi:
    xor rax, rax
    movzx rdx, byte [rsi]
    sub rdx, '0'
    imul rax, 10
    add rax, rdx
    
    movzx rdx, byte [rsi+1]
    sub rdx, '0'
    imul rax, 10
    add rax, rdx
    
    movzx rdx, byte [rsi+2]
    sub rdx, '0'
    imul rax, 10
    add rax, rdx
    ret


clear_buffer:
    ; Clear the buffer
    lea rdi, [buffer]
    mov rcx, 5
    xor al, al
    rep stosb
    ret
