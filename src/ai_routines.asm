section .text
    global ai_random_choice
    global ai_random_choice_1_to_4

; Returns a random number between 0-3
ai_random_choice:
    mov rax, 201    ; sys_time
    xor rdi, rdi
    syscall
    
    xor rdx, rdx
    mov rbx, 4
    div rbx
    
    mov eax, edx    ; Return value in eax
    ret

; Returns a random number between 1-4
ai_random_choice_1_to_4:
    call ai_random_choice
    add eax, 1      ; Convert 0-3 to 1-4
    ret

section .note.GNU-stack noalloc noexec nowrite progbits