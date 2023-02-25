#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
  TK_PUNCT, // 操作符如： + -
  TK_NUM,   // 数字
  TK_EOF,   // 文件终止符，即文件的最后
} TokenKind;

// 终结符结构体
typedef struct Token Token;
struct Token {
  TokenKind Kind; // 种类
  Token *Next;    // 指向下一终结符
  int Val;        // 值
  char *Loc;      // 在解析的字符串内的位置
  int Len;        // 长度
};

// 输出错误信息
static void error(char *Fmt, ...) {
    va_list VA;
    va_start(VA, Fmt);
    vfprintf(stderr, Fmt, VA);
    fprintf(stderr, "\n");
    va_end(VA);
    exit(1);
}

// 生成新的Token
static Token *newToken(TokenKind Kind, char *Start, char *End) {
    // 分配1个Token的内存空间
    Token *Tok = calloc(1, sizeof(Token));
    Tok->Kind = Kind;
    Tok->Loc = Start;
    Tok->Len = End - Start;
    return Tok;
}

// 终结符解析
static Token *tokenize(char *P) {
    Token Head = {};
    Token *Cur = &Head;

    while (*P) {
        if (isspace(*P)) {
            ++P;
            continue;
        }
        // 解析数字
        if (isdigit(*P)) {
            Cur->Next = newToken(TK_NUM, P, P);
            Cur = Cur->Next;
            const char *OldPtr = P;
            Cur->Val = strtoul(P, &P, 10);
            Cur->Len = P - OldPtr; //calculate length!
            continue;
        }
        // 解析操作符
        if (*P == '+' || *P == '-') {
            Cur->Next = newToken(TK_PUNCT, P, P + 1);
            Cur = Cur->Next;
            ++P;
            continue;
        }
        // 处理无法识别的字符
        error("invalid token: %c", *P);
    }
    // 解析结束，增加一个EOF，表示终止符。
    Cur->Next = newToken(TK_EOF, P, P);
    // Head无内容，所以直接返回Next
    return Head.Next;
}

// 返回TK_NUM的值
static int getNumber(Token *Tok) {
    if (Tok->Kind != TK_NUM)
        error("expect a number");
    return Tok->Val;
}

// 判断Tok的值是否等于指定值
static bool equal(Token *Tok, char *Str) {
    // 比较字符串LHS（左部），RHS（右部）的前N位，S2的长度应大于等于N.
    // 比较按照字典序，LHS<RHS回负值，LHS=RHS返回0，LHS>RHS返回正值
    // 同时确保，此处的Op位数=N
    return memcmp(Tok->Loc, Str, Tok->Len) == 0 && Str[Tok->Len] == '\0';
}

// 跳过指定的Str
static Token *skip(Token *Tok, char *Str) {
    if (!equal(Tok, Str))
        error("expect '%s'", Str);
    return Tok->Next;
}


int main(int argc, char **argv){
    if (argc != 2) {
      error("%s: invalid number of arguments", argv[0]);
    }

    Token *Tok = tokenize(argv[1]);

    // 声明一个全局main段，同时也是程序入口段
    printf("  .globl main\n");
    // main段标签
    printf("main:\n");

    // strtol为“string to long”，
    // 参数为：被转换的str，str除去数字后的剩余部分，进制
    // li为addi别名指令，加载一个立即数到寄存器中
    printf("  li a0, %d\n", getNumber(Tok));
    Tok = Tok->Next;

    while (Tok->Kind != TK_EOF) {
        if (equal(Tok, "+")) {
            Tok = Tok->Next;
            printf("  addi a0, a0, %d\n", getNumber(Tok));
            Tok = Tok->Next;
            continue;
        }
        // 不是+，则判断-
        // 没有subi指令，但是addi支持有符号数，所以直接对num取反
        Tok = skip(Tok, "-");
        printf("  addi a0, a0, -%d\n", getNumber(Tok));
        Tok = Tok->Next;

    }

    // ret为jalr x0, x1, 0别名指令，用于返回子程序
    printf("  ret\n");

    return 0;
}