#include"Producer.h"
#include<set>
#include<vector>
#include<stack>
#ifndef SEMAANALYZER_H_INCLUDED
#define SEMAANALYZER_H_INCLUDED
class SemaAnalyzer
{
public:
    SemaAnalyzer();
    ~SemaAnalyzer();
    /***General 方法***/
    int getNterIndex(char);
    int getTerIndex(char a);
    bool isTerSym(char wait);
    bool isNTerSym(char wait);
    bool ifCanbeVoid(char target);

    /***LL(1)分析算法的方法***/
    set<char> getFirstSet(char target);
    set<char> getFollowSet(char target);
    set<char> getSelectSet(Producer p);
    set<char> getCanVoid();
    void showFirstSet();
    void setFirstOnly(set<char> a,int b);
    void setFirst();
    void setFollowOnly(set<char> a,int b);
    void setFollow();
    void showSelectSet();
    void setSelect();
    void showFollowSet();
    void showProducer();
    void setKnowTable();
    void showKnowTable();
    int LL1Ana(string idenString);
    string TokentransForm();


    /***递归下降分析算法的方法***/
    void recurZ(string idenString);
    int recurE(string idenString,int curIndex);
    int recurT(string idenString,int curIndex);
    int recurR(string idenString,int curIndex);
    int recurF(string idenString,int curIndex);
    int recurU(string idenString,int curIndex);


private:
    int proNum;                     //产生式的数量
    vector<Producer> produce_;
    char startSym_;
    char endSym_;
    char voidSym_;
    vector<char> terSym_;
    vector<char> nterSym_;
    set<char> firstSet_[50];
    set<char> followSet_[50];
    set<char> selectSet_[50];
    int  **knowTable_;         //产生式知识表
    stack<char> semaStack_;
};
#endif // SEMAANALYZER_H_INCLUDED
