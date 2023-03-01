#include "rvcc.h"

int main(int argc, char** argv) {
    if (argc != 2)
        error("%s: invalid number of arguments", argv[0]);

    // 生成终结符流
    Token* Tok = tokenize(argv[1]);

    // 解析终结符流
    Function* Prog = parse(Tok);

    // 生成代码
    codegen(Prog);

    return 0;
}