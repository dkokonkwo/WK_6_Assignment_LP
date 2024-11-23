section .data
    prompt_num1 db "Enter the first number: ", 0
    prompt_num2 db "Enter the second number: ", 0
    prompt_op db "Enter the operation (+,-,*,/): ", 0
    result_msg db "The result is: ", 0
    error_msg db "Error: Division by zero!", 0
    newline db 0xA, 0

section .bss
    num1 resb 20
    num2 resb 20
    operation resb 2 ; 1 character + null terminator
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
    test rax, rax     ; checks if a valid number was entered
    jz invalid_input  ; jump if zero (invalid input)
    mov r8, rax       ; storing first value in r8

    ; Prompt for the second number
    mov rsi, prompt_num2
    call print_string
    mov rsi, num2
    call read_input
    call str_to_int
    test rax, rax
    jx invalid_input
    mov r9, rax        ; storing second value in r9

    ; Prommpt for the operation
    mov rsi, prompt_op
    call print_string
    mov rsi, operation
    call read_input
    mov al, byte [operation]  ; loading operation into al

    ; Perform operation
    cmp al, '+'
    je add_numbers
    cmp al, '-'
    je sub_numbers
    cmp al, '*'
    je mul_numbers
    cmp al, '/'
    je div_numbers

    ; Handle invalid operation
    jmp invalid_operation

invalid_input:
    mov rsi, error_msg
    call print_string
    jmp exit

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
    je division_error  ; checking for division by zero
    xor rdx, rdx   ; clears rdx for division
    mov rax, r8
    div r9
    jmp print_result

division_error:
    mov rsi, error_msg
    call print_string
    jmp exit

print_result:
    mov rsi, result_msg
    call print_string

    mov rsi, result
    call int_to_str
    mov rdx, rax    ;string length
    mov rsi, result
    call print_string
    jmp exit

invalid_operation:
    mov rsi, error_msg
    call print_string
    jmp exit

exit:
    mov rax, 60   ; System call for exit
    xor rdi, rdi  ; Exit status
    syscall

; ALL MY HELPER FUNCTIONS

; Print a string
print_string:
    mov rax, 1      ; System call for write
    mov rdi, 1      ; File descriptor (stdout)
    mov rdx, rsi    ; Pointer to string
    mov rsi, rdx    ; Length of the string
    syscall
    ret

; Read input
read_input:
    mov rax, 0    ; System call for read
    mov rdi, 0      ; File descriptor (stdin)
    mov rdx, 20     ; Max bytes to read
    syscall

    ; replacing newline characters with null terminator
    mov rbx, rsi    ; Start of the input buffer
.replace_newline:
    mov al, byte [rbx]  ; Load character
    cmp al, 0xA         ; checking if it's newline
    je .null_terminate
    cmp al, 0           ; End of string
    je .done
    inc rbx             ; move to next character
    jmp .replace_newline
.null_terminate:
    mov byte [rbx], 0   ; Replacing newline with null terminator
.done:
    ret

; Convert string to integer
str_to_int:
    xor rax, rax    ; Clear rax
    xor rbx, rbx    ; Clear rbx
.convert_loop:
    lodsb           ; Load byte from rsi
    cmp al, 0     ; Check for newline
    je .done
    cmp al, '0'     ; Valid digit
    jl .error
    cmp al, '9'
    jg .error
    sub al, '0'     ; Converting ASCII to integer
    imul rax, rax, 10   ; Multiply rax by 10
    add rax, rbx    ; Add current digit
    xor rbx, rbx    ; Clear rbx
    jmp .convert_loop
.done:
    ret
.error:
    xor rax, rax    ; Return 0 for invalid input
    ret

; Converting integer to string
int_to_str:
    xor rcx, rcx    ; Clear rcx (digit count)
    mov rdi, rsi    ; Store pointer to result
    add rdi, 19     ; Point to the end of the buffer
    mov byte [rdi], 0   ; Null-terminate the string
.convert_loop:
    xor rdx, rdx
    div rbx         ; Divide rax by 10
    add dl, '0'     ; Converting remainder to ASCII
    dec rdi
    mov [rdi], dl   ; Store ASCII digit
    inc rcx         ; Increment digit count
    test rax, rax   ; Check if quotient is zero
    jnz .convert_loop
    mov rax, rcx    ; Return string length
    ret
