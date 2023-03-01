# RISC-V Compiler
This project builds a C compiler transfer C to RISC-V assembler.
## Exercise Log
### [23.02.25]
- [001] Return particular value
    - Construct the RISC-V environment.
    - Learned how to write test shell script and some makefile.
    - Learned li `li为addi别名指令，加载一个立即数到寄存器中`, ret `ret为jalr x0, x1, 0别名指令，用于返回子程序`.
- [002] Add + -
    - Learned strtol `参数为：被转换的str，str除去数字后的剩余部分，进制`, addi `addi rd, rs1, imm 表示 rd = rs1 + imm`.
- [003] Add a Terminator parser
    - Parse strings by using a linked-list.
    - Wrap the Lexer.
- [004] Revise error handling
    - Learned the error handling.
- [005] Add * / ()
    - Split the program into lexer, parser and generator.
    - The parser uses many complicated pointers QAQ
    - sp 为栈指针，栈反向向下增长。
### [23.02.26]
- [006] Add unary - +
- [007] Add == != <= >=
    - Learned how to handle 2-length operators
    - Learned xor `xor a0, a0, a1 a0=a0^a1，异或指令`, `sltiu a0, a0, 1 等于0则置1`, `sltu a0, x0, a0 不等于0则置1`, seqz, snez, slt.
- [008] Split main.c
    - Learned how to manage a large project.
- [009] Add ; to split statement.
    - Use a linked-list to store statements.
### [23.03.01]
- [010] Support assign 1-char variable
    - Use `fp` to store the address of stack base.
    - Learned how to handle assign in assemblr.
- [010] Support assign multi-char variable
    - Add a function structure, an object struture representing variables.
