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
    /***General ����***/
    int getNterIndex(char);
    int getTerIndex(char a);
    bool isTerSym(char wait);
    bool isNTerSym(char wait);
    bool ifCanbeVoid(char target);

    /***LL(1)�����㷨�ķ���***/
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


    /***�ݹ��½������㷨�ķ���***/
    void recurZ(string idenString);
    int recurE(string idenString,int curIndex);
    int recurT(string idenString,int curIndex);
    int recurR(string idenString,int curIndex);
    int recurF(string idenString,int curIndex);
    int recurU(string idenString,int curIndex);


private:
    int proNum;                     //����ʽ������
    vector<Producer> produce_;
    char startSym_;
    char endSym_;
    char voidSym_;
    vector<char> terSym_;
    vector<char> nterSym_;
    set<char> firstSet_[50];
    set<char> followSet_[50];
    set<char> selectSet_[50];
    int  **knowTable_;         //����ʽ֪ʶ��
    stack<char> semaStack_;
};
#endif // SEMAANALYZER_H_INCLUDED
