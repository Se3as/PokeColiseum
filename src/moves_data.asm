section .data

;types
normal:  db "NORMAL", 0
fire:    db "FIRE", 0
ice:     db "ICE", 0
water:   db "WATER", 0
dragon:  db "DRAGON", 0

;actual moves
slash:         db "SLASH", 0
ember:         db "EMBER", 0
flamethrower:  db "FLAMETHROWER", 0
icefang:       db "ICE FANG", 0
hydropump:     db "HYDRO PUMP", 0
dragonbreath:  db "DRAGON BREATH", 0
watergun:      db "WATER GUN", 0

moves:
    
    dd 0, 3, 40
    dq water
    dq watergun  

    dd 1, 6, 65
    dq ice
    dq icefang 

    dd 2, 3, 110
    dq water
    dq hydropump 

    dd 3, 1, 70
    dq normal
    dq slash 

    dd 4, 2, 40
    dq fire
    dq ember  

    dd 5, 2, 90
    dq fire
    dq flamethrower  

    dd 6, 15, 60
    dq dragon
    dq dragonbreath ;

    
    
moves_count equ ($ - moves) / 28
; moves: id, typeid, damage, type, name
; Normal 1, fuego 2, agua 3, dragon 15  <-- segun la wiki estan numerados de esa forma cada tipo

section .note.GNU-stack note


section .text
global get_move_damage
global get_move_name
global get_move_type
global get_move_type_id


get_move_damage:  ;<-- recibe un id de movimiento y terona el damage que hace
    cmp rdi, moves_count
    jae .not_a_move_damage

    mov rax, rdi
    imul rax, 28
    mov eax, [moves + rax + 8]
    ret


.not_a_move_damage:
    xor eax, eax
    ret


get_move_type:
    cmp rdi, moves_count
    jae .not_a_move_type

    mov rax, rdi
    imul rax, 28
    mov rax, [moves + rax + 12]  
    ret

.not_a_move_type:
    xor eax, eax
    ret

get_move_name:
    cmp rdi, moves_count
    jae .not_a_move_name

    mov rax, rdi
    imul rax, 28
    mov rax, [moves + rax + 20]
    ret

.not_a_move_name:
    xor eax, eax
    ret

get_move_type_id:
    cmp rdi, moves_count
    jae .not_a_move_type_id

    mov rax, rdi
    imul rax, 28
    mov rax, [moves + rax + 4]  
    ret

.not_a_move_type_id:
    xor eax, eax
    ret