#include <iostream>
#include <fstream>
#include<set>
#include"TokenAnalyzer.h"
#include"SemaAnalyzer.h"
using namespace std;
int main()
{
    /***词法分析演示***/
    /*string fileName="C:/Users/steven/Desktop/test.txt";
    TokenAnalyzer a;
    int catchError;
    catchError=a.automachine(fileName);
    if(catchError!=-1)
    {
        a.showResult();
        a.showID();
        a.showNum();
        a.showChar();
        a.showString();
        a.showPer();
    }*/

    /***展示LL1***/
    SemaAnalyzer b;
    string deal=b.TokentransForm();
    cout<<endl;
    cout<<endl;
    b.showProducer();
    b.setFirst();
    b.showFirstSet();
    b.setFollow();
    b.showFollowSet();
    cout<<endl;
    b.setSelect();
    b.showSelectSet();
    b.setKnowTable();
    b.showKnowTable();
    b.LL1Ana(deal);

    cout<<endl;
    cout<<endl;
    /***展示递归下降子程序***/
    b.recurZ(deal);


}
