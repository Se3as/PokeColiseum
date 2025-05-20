.model small
.stack 100h

.data
    currentHealth db 'Salud actual: $'
    damageReceived db 'Danio recibido: $'
.code
main:
    ; Inicializar el segmento de datos
    mov ax, @data
    mov ds, ax

    mov cx, 5
    call initValues
    call ciclo

ciclo:
    cmp cx,0
    je fin
    dec cx

    ; Imprimir el primer prompt: "Salud actual: "
    mov ah, 09h
    lea dx, currentHealth
    int 21h

    call printNumb
    call attack
    jg ciclo

initValues:
    mov ax, 100
    mov bx, 129
    ret
attack:
    push cx
    push ax
    mov cx, 10

    mov ah, 0        ; INT 1Ah -> CX:DX = tics desde medianoche
    int 1Ah

    mov ax, dx       ; AX = valor variable (tics bajo 16 bits)
    xor dx, dx
    div cx           ; AX = AX/CX, DX = AX mod CX
    mov ax, dx       ; AX = resto = valor aleatorio
    sub bx,ax

    pop ax
    pop cx
    ret

printNumb:
    push ax
    push cx
    push bx

    mov dx,0
    mov ax, bx
    mov cx, 100
    div cx
    mov cx,dx
    add al, '0'
    mov dl, al
    mov ah, 02h
    int 21h

    mov dx,0
    mov ax,cx
    mov cx, 10
    div cx
    mov cx,dx
    add al, '0'
    mov dl, al
    mov ah, 02h
    int 21h

    mov dx,0
    mov ax,cx
    add al, '0'
    mov dl, al
    mov ah, 02h
    int 21h

    mov ah, 02h
    mov dl, 0Dh
    int 21h

    mov ah, 02h
    mov dl, 0Ah
    int 21h

    pop bx
    pop cx
    pop ax
    ret




fin:
    mov ah, 4Ch
    int 21h
end main