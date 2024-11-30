section .data
    prompt1 db "Enter the first number: ", 0
    prompt2 db "Enter the second number: ", 0
    prompt3 db "Enter the operator (+, -, *, /): ", 0
    invalid_operator_msg db "Invalid operator", 0
    div_by_zero db "Division by zero error", 0
    result_msg db "Result: ", 0
    newline db 10, 0

section .bss
    num1 resb 10
    num2 resb 10
    operator resb 2
    result resb 20

section .text
    global _start

_start:
    ; Prompt for the first number
    mov rax, 1 ; sys_write
    mov rdi, 1 ; stdout
    mov rsi, prompt1
    mov rdx, 23 ; length of prompt1
    syscall

    ; Read the first number
    mov rax, 0 ; sys_read
    mov rdi, 0 ; stdin
    mov rsi, num1
    mov rdx, 10
    syscall

    ; Prompt for the second number
    mov rax, 1
    mov rdi, 1
    mov rsi, prompt2
    mov rdx, 24 ; length of prompt2
    syscall

    ; Read the second number
    mov rax, 0
    mov rdi, 0
    mov rsi, num2
    mov rdx, 10
    syscall

    ; Prompt for the operator
    mov rax, 1
    mov rdi, 1
    mov rsi, prompt3
    mov rdx, 31 ; length of prompt3
    syscall

    ; Read the operator
    mov rax, 0
    mov rdi, 0
    mov rsi, operator
    mov rdx, 2
    syscall

    ; Convert numbers to integers
    mov rdi, num1
    call atoi
    mov rbx, rax

    mov rdi, num2
    call atoi
    mov rcx, rax

    ; Check the operator and perform the operation
    cmp byte [operator], '+' 
    je add_numbers
    cmp byte [operator], '-' 
    je subtract_numbers
    cmp byte [operator], '*' 
    je multiply_numbers
    cmp byte [operator], '/' 
    je divide_numbers

    ; Invalid operator
    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 2
    syscall
    mov rax, 1
    mov rdi, 1
    mov rsi, invalid_operator_msg
    mov rdx, 14
    syscall
    jmp exit

add_numbers:
    add rbx, rcx
    jmp print_result

subtract_numbers:
    sub rbx, rcx
    jmp print_result

multiply_numbers:
    imul rbx, rcx
    jmp print_result

divide_numbers:
    cmp rcx, 0
    je division_by_zero
    xor rdx, rdx      ; Clear rdx for proper division
    mov rax, rbx      ; Dividend in rax
    idiv rcx          ; Divides rdx:rax by rcx
    mov rbx, rax      ; Move result back to rbx
    jmp print_result

division_by_zero:
    mov rax, 1
    mov rdi, 1
    mov rsi, div_by_zero
    mov rdx, 20
    syscall
    jmp exit


print_result:
    mov rax, 1
    mov rdi, 1
    mov rsi, result_msg
    mov rdx, 8
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, result
    mov rdx, 20 ; Adjust the buffer size as needed
    call itoa
    mov rcx, rax  ; Result length in rax after itoa
    syscall

    ; Exit the program
exit:
    mov rax, 60
    mov rdi, 0
    syscall

; Function to convert a string to an integer
atoi:
    xor rax, rax
.loop:
    movzx rdx, byte [rdi]
    sub rdx, '0'
    imul rax, 10
    add rax, rdx
    inc rdi
    cmp byte [rdi], 0
    jne .loop
    ret

; Function to convert an integer to a string
itoa:
    mov rdi, result + 19  ; Start from the end of the buffer
    mov byte [rdi], 0     ; Null-terminate
    dec rdi
.loop:
    xor rdx, rdx
    mov r10, 10
    idiv r10
    add dl, '0'
    mov byte [rdi], dl
    dec rdi
    test rax, rax
    jnz .loop
    inc rdi
    ret
