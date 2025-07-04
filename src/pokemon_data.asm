section .data

; pokemon names
charmander: db "CHARMANDER", 0
totodile:   db "TOTODILE", 0

; ID, HP original, TIPO
pokedex_data: 
    dd 0, 146, 2
    dq charmander  ; ID charmander, hp: 146, tipo: 2(fuego), pokenombre

    dd 1, 157, 3  ; ID totodile, hp: 157, tipo: 2(agua), pokenombre
    dq totodile

pokedex_count: equ ($ - pokedex_data) / 20


pokemon_battle_state:
    times pokedex_count dd 999  ;<-- vida actual en batalla

section .note.GNU-stack note


section .text
global get_pokemon_original_hp
global get_pokemon_current_hp
global set_pokemon_hp
global get_pokemon_name
global get_pokemon_type


get_pokemon_original_hp:
    cmp rdi, pokedex_count
    jae .not_a_pokemon

    mov rax, rdi
    imul rax, 20
    mov eax, [pokedex_data + rax + 4]
    ret

.not_a_pokemon:
    mov eax, -1
    ret

get_pokemon_current_hp:
    cmp rdi, pokedex_count
    jae .not_a_pokemon_id


    mov eax, [pokemon_battle_state + rdi * 4]
    cmp eax, 999
    je .prepare_pokemon   ;<-- setea la vida del pokemon al iniciar la batalla

    mov eax, [pokemon_battle_state + rdi * 4]
    ret

.prepare_pokemon:
    mov rax, rdi
    imul rax, 20
    mov eax, [pokedex_data + rax + 4]
    mov [pokemon_battle_state + rdi * 4], eax
    ret

.not_a_pokemon_id:
    mov eax, -1
    ret


set_pokemon_hp: ; <-- recibe un (int id, int new_hp)
    cmp rdi, pokedex_count
    jae .not_a_pokemon_here

    mov [pokemon_battle_state + rdi * 4], esi  ;<-- guarda la vida que le meto
    ret


.not_a_pokemon_here:
    mov eax, -1
    ret

get_pokemon_name:
    get_pokemon_name:
    cmp rdi, pokedex_count
    jae .not_a_pokemon_name

    mov rax, rdi
    imul rax, 20       
    mov rax, [pokedex_data + rax + 12]
    ret

.not_a_pokemon_name:
    mov rax, 0
    ret

get_pokemon_type:
    cmp rdi, pokedex_count
    jae .not_a_pokemon_with_type

    mov rax, rdi
    imul rax, 20
    mov eax, [pokedex_data + rax + 8]
    ret

.not_a_pokemon_with_type:
    mov eax, -1
    ret