#ifndef TOKEN_H
#define TOKEN_H
#include<string>
using namespace std;
class Token
{
public:
    Token();
    Token(int code,string name);
    void setUp(int a,string b);
    string getWord();
    int getType();
private:
    int code;
    string word;
};
#endif
