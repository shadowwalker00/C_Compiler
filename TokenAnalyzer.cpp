#include "TokenAnalyzer.h"
#include <fstream>
#include<iostream>
using namespace std;
TokenAnalyzer::TokenAnalyzer()
{
    Token temp(4,"int");
    keyWord.insert(keyWord.end(),temp);
    temp.setUp(5,"main");
    keyWord.insert(keyWord.end(),temp);
    temp.setUp(6,"void");
    keyWord.insert(keyWord.end(),temp);
    temp.setUp(9,"char");
    keyWord.insert(keyWord.end(),temp);
    temp.setUp(28,"while");
    keyWord.insert(keyWord.end(),temp);
    temp.setUp(7,"if");
    keyWord.insert(keyWord.end(),temp);
    temp.setUp(8,"else");
    keyWord.insert(keyWord.end(),temp);
}
TokenAnalyzer::~TokenAnalyzer()
{
    //dtor
}
bool TokenAnalyzer::isLetter(char c)
{
    //判断字母
    if(((c<='z')&&(c>='a'))||((c<='Z')&&(c>='A')))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool TokenAnalyzer::isKeyword(string c)
{
    vector<Token>::iterator it;
    bool flag=false;
    for(it=keyWord.begin(); it!=keyWord.end(); it++)
    {
        if((*it).getWord()==c)
        {
            flag=true;
            break;
        }
    }
    return flag;
}
bool TokenAnalyzer::isID(string c)
{
    vector<Token>::iterator it;
    bool flag=false;
    for(it=identifier.begin(); it!=identifier.end(); it++)
    {
        if((*it).getWord()==c)
        {
            flag=true;
            break;
        }
    }
    return flag;
}
bool TokenAnalyzer::isDigit(char c)
{
    //判断是否为数字
    if(c>='0'&&c<='9')
    {
        return true;
    }
    else
    {
        return false;
    }
}
int TokenAnalyzer::automachine(string fileName)
{
    ifstream fp;
    fp.open("C:/Users/lenovo/Desktop/Compiler/test2.txt",ios::in);
    if(!fp)
    {
        cout<<"open error!"<<endl;
    }
    string dealing="";
    char ch;
    fp.get(ch);
    while(fp.eof()!=true)
    {
        dealing="";
        if(ch==' '||ch=='\t'||ch=='\n')
        {
            fp.get(ch);
            continue;
        }
        else if(isLetter(ch))
        {
            dealing=dealing+ch;
            fp.get(ch);
            while(isLetter(ch)||isDigit(ch))
            {
                //这个判断里面没有加入下划线
                dealing=dealing+ch;
                fp.get(ch);
            }
            Token temp;
            if(isKeyword(dealing))
            {
                vector<Token>::iterator it;
                int type;
                for(it=keyWord.begin(); it!=keyWord.end(); it++)
                {

                    if((*it).getWord()==dealing)
                    {
                        type=(*it).getType();
                        break;
                    }
                }
                temp.setUp(type,dealing);
                result.insert(result.end(),temp);
            }
            else
            {
                temp.setUp(0,dealing);
                if(isID(dealing)==false)
                {
                    Token temp1;
                    temp1.setUp(0,dealing);
                    identifier.insert(identifier.end(),temp1);
                }
                result.insert(result.end(),temp);
            }
            continue;
        }
        else if(isDigit(ch))                    //识别数字常量,这个位置应该改成用一个二维表来存储数字常量的翻译器
        {

            dealing=dealing+ch;
            fp.get(ch);
            while(isDigit(ch))
            {
                dealing=dealing+ch;
                fp.get(ch);
            }
            if(ch=='.')
            {
                dealing=dealing+'.';
                fp.get(ch);
                if(isDigit(ch))
                {
                    dealing=dealing+ch;
                    fp.get(ch);
                    while(isDigit(ch))
                    {
                        dealing=dealing+ch;
                        fp.get(ch);
                    }
                    if(ch=='e')
                    {
                        dealing=dealing+'e';
                        fp.get(ch);
                        if(isDigit(ch))
                        {
                            while(isDigit(ch))
                            {
                                dealing=dealing+ch;
                                fp.get(ch);
                            }
                        }
                        else if(ch=='+'||ch=='-')
                        {
                            dealing=dealing+ch;
                            fp.get(ch);
                            if(isDigit(ch))
                            {
                                dealing=dealing+ch;
                                fp.get(ch);
                                while(isDigit(ch))
                                {
                                    dealing=dealing+ch;
                                    fp.get(ch);
                                }
                            }
                        }
                    }
                }

            }
            else if(ch=='e')
            {
                dealing=dealing+'e';
                fp.get(ch);
                if(isDigit(ch))
                {
                    while(isDigit(ch))
                    {
                        dealing=dealing+ch;
                        fp.get(ch);
                    }
                }
                else if(ch=='+'||ch=='-')
                {
                    dealing=dealing+ch;
                    fp.get(ch);
                    if(isDigit(ch))
                    {
                        dealing=dealing+ch;
                        fp.get(ch);
                        while(isDigit(ch))
                        {
                            dealing=dealing+ch;
                            fp.get(ch);
                        }
                    }
                }
            }
            Token temp(3,dealing);
            result.insert(result.end(),temp);
            constNum.insert(constNum.end(),temp);
            continue;
        }
        else if(ch=='\'')
        {
            dealing=dealing+'\'';
            fp.get(ch);
            if(isLetter(ch))
            {
                dealing=dealing+ch;
                fp.get(ch);
            }
            Token temp(1,dealing);
            if(ch=='\'')
            {
                dealing=dealing+'\'';
                fp.get(ch);
                temp.setUp(1,dealing);
                letter.insert(letter.end(),temp);
                result.insert(result.end(),temp);
                continue;
            }
            else
            {
                cout<<"You are tying a non-char word at somewhere!!!"<<endl;
                return -1;;
            }
        }
        else if(ch=='\"')
        {
            dealing=dealing+'\"';
            fp.get(ch);
            while(isLetter(ch)||isDigit(ch))
            {
                dealing=dealing+ch;
                fp.get(ch);
            }
            Token temp(2,dealing);
            if(ch=='\"')
            {
                dealing=dealing+'\"';
                fp.get(ch);
                temp.setUp(2,dealing);
                str.insert(str.end(),temp);
                result.insert(result.end(),temp);
                continue;
            }
        }
        else if(ch=='>')
        {
            dealing=dealing+'>';
            fp.get(ch);
            Token temp;
            if(ch=='=')
            {
                dealing=dealing+'=';
                fp.get(ch);
                temp.setUp(10,dealing);
                result.insert(result.end(),temp);
            }
            else
            {
                temp.setUp(14,dealing);
                result.insert(result.end(),temp);
            }
            continue;
        }
        else if(ch=='<')
        {
            dealing=dealing+'<';
            fp.get(ch);
            if(ch=='=')
            {
                dealing=dealing+'=';
                fp.get(ch);
                Token temp;
                temp.setUp(11,dealing);
                result.insert(result.end(),temp);
            }
            else
            {
                Token temp;
                temp.setUp(15,dealing);
                result.insert(result.end(),temp);
            }
            continue;
        }
        else if(ch=='=')
        {
            dealing=dealing+'=';
            fp.get(ch);
            if(ch=='=')
            {
                dealing=dealing+'=';
                fp.get(ch);
                Token temp;
                temp.setUp(12,dealing);
                result.insert(result.end(),temp);
            }
            else
            {
                Token temp;
                temp.setUp(13,dealing);
                result.insert(result.end(),temp);
            }
            continue;
        }
        else if(ch=='+')
        {
            dealing=dealing+'+';
            fp.get(ch);
            Token temp;
            temp.setUp(16,dealing);
            result.insert(result.end(),temp);
            per.insert(per.end(),temp);
        }
        else if(ch=='-')
        {
            dealing=dealing+'-';
            fp.get(ch);
            Token temp;
            temp.setUp(17,dealing);
            result.insert(result.end(),temp);
            per.insert(per.end(),temp);
        }
        else if(ch=='*')
        {
            dealing=dealing+'*';
            fp.get(ch);
            Token temp;
            temp.setUp(18,dealing);
            result.insert(result.end(),temp);
            per.insert(per.end(),temp);
        }
        else if(ch=='/')
        {
            dealing=dealing+'/';
            fp.get(ch);
            Token temp;
            temp.setUp(19,dealing);
            result.insert(result.end(),temp);
            per.insert(per.end(),temp);
        }
        else if(ch=='{')
        {
            dealing=dealing+'{';
            fp.get(ch);
            Token temp;
            temp.setUp(20,dealing);
            result.insert(result.end(),temp);
            per.insert(per.end(),temp);
        }
        else if(ch=='}')
        {
            dealing=dealing+'}';
            fp.get(ch);
            Token temp;
            temp.setUp(21,dealing);
            result.insert(result.end(),temp);
            per.insert(per.end(),temp);
        }
        else if(ch==',')
        {
            dealing=dealing+',';
            fp.get(ch);
            Token temp;
            temp.setUp(22,dealing);
            result.insert(result.end(),temp);
            per.insert(per.end(),temp);
        }
        else if(ch==';')
        {
            dealing=dealing+';';
            fp.get(ch);
            Token temp;
            temp.setUp(23,dealing);
            result.insert(result.end(),temp);
            per.insert(per.end(),temp);
        }
        else if(ch=='(')
        {
            dealing=dealing+'(';
            fp.get(ch);
            Token temp;
            temp.setUp(24,dealing);
            result.insert(result.end(),temp);
            per.insert(per.end(),temp);
        }
        else if(ch==')')
        {
            dealing=dealing+')';
            fp.get(ch);
            Token temp;
            temp.setUp(25,dealing);
            result.insert(result.end(),temp);
            per.insert(per.end(),temp);
        }
        else if(ch=='[')
        {
            dealing=dealing+']';
            fp.get(ch);
            Token temp;
            temp.setUp(26,dealing);
            result.insert(result.end(),temp);
            per.insert(per.end(),temp);
        }
        else if(ch==']')
        {
            dealing=dealing+']';
            fp.get(ch);
            Token temp;
            temp.setUp(27,dealing);
            result.insert(result.end(),temp);
            per.insert(per.end(),temp);
        }
        else
        {
            continue;
        }
    }
}
void TokenAnalyzer::showResult()
{
    cout<<"Result Token Sequence:"<<endl;
    vector<Token>::iterator it;
    for(it=result.begin(); it!=result.end(); it++)
    {
        cout<<"<"<<(*it).getType()<<","<<(*it).getWord()<<">"<<endl;
    }
}
void TokenAnalyzer::showID()
{
    cout<<"ID Token Sequence:"<<endl;
    vector<Token>::iterator it;
    for(it=identifier.begin(); it!=identifier.end(); it++)
    {
        cout<<"<"<<(*it).getType()<<","<<(*it).getWord()<<">"<<endl;
    }
}
void TokenAnalyzer::showNum()
{
    cout<<"Num Token Sequence:"<<endl;
    vector<Token>::iterator it;
    for(it=constNum.begin(); it!=constNum.end(); it++)
    {
        cout<<"<"<<(*it).getType()<<","<<(*it).getWord()<<">"<<endl;
    }
}
void TokenAnalyzer::showChar()
{
    cout<<"Character Token Sequence:"<<endl;
    vector<Token>::iterator it;
    for(it=letter.begin(); it!=letter.end(); it++)
    {
        cout<<"<"<<(*it).getType()<<","<<(*it).getWord()<<">"<<endl;
    }
}
void TokenAnalyzer::showString()
{
    cout<<"String Token Sequence:"<<endl;
    vector<Token>::iterator it;
    for(it=str.begin(); it!=str.end(); it++)
    {
        cout<<"<"<<(*it).getType()<<","<<(*it).getWord()<<">"<<endl;
    }
}
void TokenAnalyzer::showPer()
{
    cout<<"Per Token Sequence:"<<endl;
    vector<Token>::iterator it;
    for(it=per.begin(); it!=per.end(); it++)
    {
        cout<<"<"<<(*it).getType()<<","<<(*it).getWord()<<">"<<endl;
    }
}
vector<Token> TokenAnalyzer::getConstNum()
{
    return constNum;
}
vector<Token> TokenAnalyzer::getIden()
{
    return identifier;
}
vector<Token> TokenAnalyzer::getPer()
{
    return per;
}
vector<Token> TokenAnalyzer::getResult()
{
    return result;
}
