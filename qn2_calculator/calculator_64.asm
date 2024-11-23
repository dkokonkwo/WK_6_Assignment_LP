section .data
    msg db "Enter first number: ", 0
    msg2 db "Enter second number: ", 0
    msg3 db "Choose operation (+, -, *, /): ", 0
    result_msg db "The result is: ", 0
    newline db 10, 0

section .bss
    num1 resb 16
    num2 resb 16
    op resb 1
    result resb 16

section .text
    global _start

_start:
    ; Get first number
    mov rax, 1
    mov rdi, 1
    mov rsi, msg
    mov rdx, 20
    syscall

    mov rax, 0
    mov rdi, 0
    mov rsi, num1
    mov rdx, 16
    syscall

    ; Get second number
    mov rax, 1
    mov rdi, 1
    mov rsi, msg2
    mov rdx, 20
    syscall

    mov rax, 0
    mov rdi, 0
    mov rsi, num2
    mov rdx, 16
    syscall

    ; Get operation
    mov rax, 1
    mov rdi, 1
    mov rsi, msg3
    mov rdx, 30
    syscall

    mov rax, 0
    mov rdi, 0
    mov rsi, op
    mov rdx, 1
    syscall

    ; Convert strings to integers
    call atoi
    mov rbx, rax
    call atoi2
    mov rcx, rax

    ; Perform the operation
    cmp byte [op], '+'
    je add
    cmp byte [op], '-'
    je sub
    cmp byte [op], '*'
    je mul
    cmp byte [op], '/'
    je div

add:
    add rbx, rcx
    mov rax, rbx
    jmp print_result
sub:
    sub rbx, rcx
    mov rax, rbx
    jmp print_result
mul:
    imul rbx, rcx
    mov rax, rbx
    jmp print_result
div:
    xor rdx, rdx
    mov rax, rbx
    div rcx
    jmp print_result

print_result:
    call itoa
    mov rsi, result

    mov rax, 1
    mov rdi, 1
    mov rsi, result_msg
    mov rdx, 14
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, result
    mov rdx, 16
    syscall

    ; Print newline
    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall

    ; Exit
    mov rax, 60
    xor rdi, rdi
    syscall

atoi:
    mov rax, 0
    xor rbx, rbx ; Clearing rbx before accumulation
    mov rsi, num1
atoi_loop:
    lodsb
    sub al, '0'
    cmp al, 0
    jl atoi_done
    imul rax, rax, 10
    add rax, rbx
    jmp atoi_loop
atoi_done:
    ret

atoi2:
    mov rax, 0
    mov rsi, num2
atoi2_loop:
    lodsb
    sub al, '0'
    cmp al, 0
    jl atoi2_done
    imul rax, rax, 10
    add rax, rbx
    jmp atoi2_loop
atoi2_done:
    ret

itoa:
    mov rsi, result + 16
    mov byte [rsi], 0
itoa_loop:
    dec rsi
    xor rdx, rdx
    div rcx
    add dl, '0'
    mov [rsi], dl
    test rax, rax
    jnz itoa_loop
    ret
