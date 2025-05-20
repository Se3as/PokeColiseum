section .data
    currentHealth db 'Salud actual: ', 0
    damageReceived db 'Danio recibido: ', 0
    newline db 10, 0

section .text
    global main
    extern printf

main:
    ; Inicializar valores
    mov rcx, 5
    call initValues
    call ciclo

ciclo:
    cmp rcx, 0
    je fin
    dec rcx

    ; Imprimir "Salud actual: "
    mov rdi, currentHealth
    xor rax, rax
    call printf

    call printNumb
    call attack
    jmp ciclo

initValues:
    mov rax, 100
    mov rbx, 129
    ret

attack:
    push rcx
    push rax

    ; Obtener valor "aleatorio" usando la hora del sistema
    mov rax, 201       ; syscall gettimeofday
    xor rdi, rdi       ; timeval *tv = NULL (no lo necesitamos)
    xor rsi, rsi       ; timezone *tz = NULL
    syscall

    ; Usar los nanosegundos (rdx) para obtener un valor "aleatorio"
    mov rax, rdx
    xor rdx, rdx
    mov rcx, 10
    div rcx            ; RDX = RAX % RCX (0-9)
    mov rax, rdx       ; RAX = valor entre 0-9

    sub rbx, rax       ; Reducir salud

    pop rax
    pop rcx
    ret

printNumb:
    push rax
    push rcx
    push rbx

    ; Convertir e imprimir el número de 3 dígitos en RBX
    mov rax, rbx
    mov rcx, 100
    xor rdx, rdx
    div rcx            ; RAX = centenas, RDX = resto
    add al, '0'
    mov rdi, rax       ; Guardar centena temporalmente

    ; Imprimir centena
    push rdx           ; Guardar resto
    mov rsi, rdi
    mov rdi, digitFormat
    xor rax, rax
    call printf
    pop rdx            ; Recuperar resto

    mov rax, rdx
    mov rcx, 10
    xor rdx, rdx
    div rcx            ; RAX = decenas, RDX = unidades
    add al, '0'
    mov rdi, rax       ; Guardar decena temporalmente

    ; Imprimir decena
    push rdx           ; Guardar unidades
    mov rsi, rdi
    mov rdi, digitFormat
    xor rax, rax
    call printf
    pop rdx            ; Recuperar unidades

    ; Imprimir unidad
    add dl, '0'
    mov rsi, rdx
    mov rdi, digitFormat
    xor rax, rax
    call printf

    ; Imprimir nueva línea
    mov rdi, newline
    xor rax, rax
    call printf

    pop rbx
    pop rcx
    pop rax
    ret

fin:
    ; Salir del programa
    mov rax, 60        ; syscall exit
    xor rdi, rdi       ; status 0
    syscall

section .data
    digitFormat db "%c", 0