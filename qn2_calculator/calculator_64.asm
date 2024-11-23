section .data
    prompt_num1 db "Enter the first number: ", 0
    prompt_num2 db "Enter the second number: ", 0
    prompt_op db "Enter the operation (+,-,*,/): ", 0
    result_msg db "The result is: ", 0
    error_msg db "Error: Division by zero!", 0
    invalid_op_msg db "Error: Invalid operation!", 0
    newline db 0xA, 0

section .bss
    num1 resb 20
    num2 resb 20
    operation resb 2
    result resb 20

section .text
    global _start

_start:
    ; Prompt for the first number
    mov rsi, prompt_num1
    call print_string
    mov rsi, num1
    call read_input
    call str_to_int
    test rax, rax
    jz invalid_input
    mov r8, rax         ; Store the first number

    ; Prompt for the second number
    mov rsi, prompt_num2
    call print_string
    mov rsi, num2
    call read_input
    call str_to_int
    test rax, rax
    jz invalid_input
    mov r9, rax         ; Store the second number

    ; Prompt for the operation
    mov rsi, prompt_op
    call print_string
    mov rsi, operation
    call read_input
    mov al, byte [operation]
    cmp al, '+'
    je add_numbers
    cmp al, '-'
    je sub_numbers
    cmp al, '*'
    je mul_numbers
    cmp al, '/'
    je div_numbers
    jmp invalid_operation

add_numbers:
    mov rax, r8
    add rax, r9
    jmp print_result

sub_numbers:
    mov rax, r8
    sub rax, r9
    jmp print_result

mul_numbers:
    mov rax, r8
    imul rax, r9
    jmp print_result

div_numbers:
    cmp r9, 0
    je division_error
    xor rdx, rdx        ; Clear remainder
    mov rax, r8
    div r9
    jmp print_result

division_error:
    mov rsi, error_msg
    call print_string
    jmp exit

invalid_operation:
    mov rsi, invalid_op_msg
    call print_string
    jmp exit

invalid_input:
    mov rsi, error_msg
    call print_string
    jmp exit

print_result:
    mov rsi, result_msg
    call print_string
    mov rsi, result
    call int_to_str
    mov rdx, rax        ; String length
    mov rsi, result
    call print_string
    jmp exit

exit:
    mov rax, 60         ; Exit system call
    xor rdi, rdi        ; Exit code 0
    syscall

; Helper Functions

print_string:
    mov rax, 1          ; Syscall: write
    mov rdi, 1          ; File descriptor: stdout
    mov rdx, rsi        ; Pointer to string
    call string_length
    syscall
    ret

read_input:
    mov rax, 0          ; Syscall: read
    mov rdi, 0          ; File descriptor: stdin
    mov rdx, 20         ; Max bytes to read
    syscall
    mov rbx, rsi        ; Start of buffer
.replace_newline:
    mov al, byte [rbx]
    cmp al, 0xA
    je .terminate
    cmp al, 0
    je .done
    inc rbx
    jmp .replace_newline
.terminate:
    mov byte [rbx], 0
.done:
    ret

str_to_int:
    xor rax, rax
    xor rbx, rbx
.convert_loop:
    lodsb
    cmp al, 0
    je .done
    cmp al, '0'
    jl .error
    cmp al, '9'
    jg .error
    sub al, '0'
    imul rax, rax, 10
    add rax, rbx
    jmp .convert_loop
.done:
    ret
.error:
    xor rax, rax
    ret

int_to_str:
    xor rcx, rcx
    mov rdi, rsi
    add rdi, 19
    mov byte [rdi], 0
.convert:
    xor rdx, rdx
    div rbx
    add dl, '0'
    dec rdi
    mov [rdi], dl
    inc rcx
    test rax, rax
    jnz .convert
    mov rax, rcx
    ret

string_length:
    xor rax, rax
    xor rbx, rbx
.count_loop:
    cmp byte [rsi + rbx], 0
    je .done
    inc rbx
    jmp .count_loop
.done:
    mov rax, rbx
    ret
