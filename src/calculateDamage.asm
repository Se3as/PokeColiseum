section .text
    global calculateDamage

calculateDamage:
    ; entrada: edi = health, esi = damage
    push rbp
    mov rbp, rsp

    mov eax, edi        ; eax = health
    sub eax, esi        ; eax -= damage
    cmp eax, 0
    jge .done

    xor eax, eax        ; si el resultado es negativo, devuelve 0
.done:
    pop rbp
    ret

section .note.GNU-stack noalloc noexec nowrite progbits