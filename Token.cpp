#include "Token.h"
Token::Token()
{
    //�޲ι���
}
Token::Token(int a,string b)
{
    code=a;
    word=b;
}
void Token::setUp(int a,string b)
{
    code=a;
    word=b;
}
int Token::getType()
{
    return code;
}
string Token::getWord()
{
    return word;
}
