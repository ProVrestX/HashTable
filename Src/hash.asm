section .text
global GetHash

GetHash:
    sub rsp, 32
    vmovdqu [rsp], ymm0
    mov rax, 5381

    mov rcx, 4

CalcHash:
    mov rdx, rax
    shl rax, 5
    add rax, rdx
    pop rdx
    add rax, rdx
    loop CalcHash

    ret