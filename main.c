#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    if (argc != 2) {
      fprintf(stderr, "%s: invalid number of arguments\n", argv[0]);
      return 1;
    }

    char *P = argv[1];

    // 声明一个全局main段，同时也是程序入口段
    printf("  .globl main\n");
    // main段标签
    printf("main:\n");

    // strtol为“string to long”，
    // 参数为：被转换的str，str除去数字后的剩余部分，进制
    // li为addi别名指令，加载一个立即数到寄存器中
    printf("  li a0, %ld\n", strtol(P, &P, 10));

    while (*P) {
        if (*P == '+') {
            ++P;
            // addi rd, rs1, imm 表示 rd = rs1 + imm
            printf("  addi a0, a0, %ld\n", strtol(P, &P, 10));
            continue;
        }
        if (*P == '-') {
            ++P;
            // addi中imm为有符号立即数，所以减法表示为 rd = rs1 + (-imm)
            printf("  addi a0, a0, -%ld\n", strtol(P, &P, 10));
            continue;
        }
        // 如果存在未解析的字符，则报错
        fprintf(stderr, "unexpected character: '%c'\n", *P);
        return 1;
    }

    // ret为jalr x0, x1, 0别名指令，用于返回子程序
    printf("  ret\n");

    return 0;
}