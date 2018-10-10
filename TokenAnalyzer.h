#include<vector>
#include <fstream>
#include"Token.h"
#ifndef TOKENANALYZER_H
#define TOKENANALYZER_H
class TokenAnalyzer
{
    public:
        TokenAnalyzer();
        virtual ~TokenAnalyzer();
        void getToken(char cur);
        bool isLetter(char c);
        bool isKeyword(string c);
        bool isID(string c);
        bool isDigit(char c);
        int automachine(string name);
        void showResult();
        void showID();
        void showNum();
        void showChar();
        void showString();
        void showPer();
        vector<Token> getConstNum();
        vector<Token> getIden();
        vector<Token> getPer();
        vector<Token> getResult();

    private:
        vector<Token> result;
        vector<Token> identifier;
        vector<Token> keyWord;
        vector<Token> constNum;
        vector<Token> letter;
        vector<Token> str;
        vector<Token> per;
};
#endif // TOKENANALYZER_H
