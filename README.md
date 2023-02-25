# RISC-V Compiler
This project builds a C compiler transfer C to RISC-V assembler.
## Exercise Log
### [23.02.25]
- [001] Return particular value
    - Construct the RISC-V environment.
    - Learned how to write test shell script and some makefile.
    - Learned li`li为addi别名指令，加载一个立即数到寄存器中`, ret`ret为jalr x0, x1, 0别名指令，用于返回子程序`.
- [002] Add + -
    - Learned strtol`参数为：被转换的str，str除去数字后的剩余部分，进制`, addi`addi rd, rs1, imm 表示 rd = rs1 + imm`.
- [003] Add a Terminator parser
    - Parse strings by using a linked-list.
    - Wrap the Lexer.
- [004] Revise error handling
    - Learned the error handling.