#include"SemaAnalyzer.h"
#include"TokenAnalyzer.h"
#include<iostream>
#include <algorithm>
#include<set>
using namespace std;
SemaAnalyzer::SemaAnalyzer()
{
    Producer temp('E',"TR");
    produce_.insert(produce_.end(),temp);
    temp.setProducer('R',"wTR");
    produce_.insert(produce_.end(),temp); //R=E1,w=w0
    temp.setProducer('R',"$");
    produce_.insert(produce_.end(),temp);   //$=3
    temp.setProducer('T',"FU");
    produce_.insert(produce_.end(),temp); //U=T1
    temp.setProducer('U',"vFU");
    produce_.insert(produce_.end(),temp); //v=w1
    temp.setProducer('U',"$");
    produce_.insert(produce_.end(),temp);
    temp.setProducer('F',"I");
    produce_.insert(produce_.end(),temp);
    temp.setProducer('F',"(E)");
    produce_.insert(produce_.end(),temp);
    proNum=produce_.size();
    nterSym_.insert(nterSym_.end(),'E');
    nterSym_.insert(nterSym_.end(),'R');
    nterSym_.insert(nterSym_.end(),'T');
    nterSym_.insert(nterSym_.end(),'U');
    nterSym_.insert(nterSym_.end(),'F');
    terSym_.insert(terSym_.end(),'w');
    terSym_.insert(terSym_.end(),'v');
    terSym_.insert(terSym_.end(),'(');
    terSym_.insert(terSym_.end(),')');
    terSym_.insert(terSym_.end(),'I');
    terSym_.insert(terSym_.end(),'#');
    startSym_='E';
    endSym_='#';
    voidSym_='$';
}
SemaAnalyzer::~SemaAnalyzer()
{
    for( int i=0; i<terSym_.size(); i++)
    {
        delete []knowTable_[i];
    }
    delete[]knowTable_;
}
set<char> SemaAnalyzer::getCanVoid()
{
    set<char> setVoid1,setVoid2;
    setVoid1.insert('$');
    while(setVoid2!=setVoid1)
    {
        setVoid2=setVoid1;
        vector<Producer>::iterator iter;
        for(iter=produce_.begin(); iter!=produce_.end(); iter++)
        {
            string tempString=iter->getRight();
            bool flag=true;
            for(int i=0; i<tempString.length(); i++)
            {
                if(setVoid1.find(tempString[i])==setVoid1.end())
                {
                    flag=false;
                    break;
                }
            }
            if(flag==true)
            {
                setVoid1.insert(iter->getLeft());
            }
        }
    }
    //setVoid1.erase('$');
    return setVoid1;
}
bool SemaAnalyzer::ifCanbeVoid(char target)
{
    set<char> beVoid=getCanVoid();
    set<char>::iterator it;
    bool flag=false;
    for(it=beVoid.begin(); it!=beVoid.end(); it++)
    {
        if(target==*it)
        {
            flag=true;
            break;
        }
    }
    return flag;
}
set<char> SemaAnalyzer::getFirstSet(char goal)
{
    set<char> first;
    if(goal=='$')
    {
        return first;
    }
    vector<Producer>::iterator it;
    for(it=produce_.begin(); it!=produce_.end(); it++)
    {
        if((*it).getLeft()==goal)
        {
            string temp=(*it).getRight();   //得到产生式右部
            if(isTerSym(temp[0])==true)
            {
                //产生式右部的首字母是终极符
                first.insert(temp[0]);
            }
            else
            {
                set<char> temp1;
                temp1=getFirstSet(temp[0]);
                first.insert(temp1.begin(),temp1.end());
            }
        }
    }
    return first;
}
set<char> SemaAnalyzer::getFollowSet(char target)
{
    //求非终极符A的follow集，寻找所有产生式B->Aβ
    set<char> tempFollow;
    set<char> tempVoid=getCanVoid();
    if(target==startSym_)
    {
        tempFollow.insert(endSym_);
    }
    vector<Producer>::iterator it;
    for(it=produce_.begin(); it!=produce_.end(); it++)
    {
        if(target==it->getLeft())
        {
            continue;
        }
        string tempString=it->getRight();
        if(tempString.find(target)>=0&&tempString.find(target)<tempString.size())
        {
            string subString=tempString.substr(tempString.find(target),tempString.size()-tempString.find(target));
            //在产生式中找到该非终极符
            if(tempString.find(target)!=tempString.size()-1)
            {
                if(isTerSym(subString[1]))
                {
                    //该非终极符后面的是1个终极符,肯定不为空
                    set<char> tempSet;
                    tempSet.insert(subString[1]);
                    tempFollow.insert(tempSet.begin(),tempSet.end());
                }
                else
                {
                    bool flag=true;
                    int notvoidIndex=0;
                    for(int i=1; i<subString.size(); i++)
                    {
                        flag=ifCanbeVoid(subString[i]);
                        if(flag==false)
                        {
                            break;
                        }
                        else
                        {
                            notvoidIndex++;
                        }
                    }
                    if(flag==false)
                    {
                        //不为空
                        set<char> tempSet;
                        tempSet=getFirstSet(subString[notvoidIndex]);
                        tempFollow.insert(tempSet.begin(),tempSet.end());
                    }
                    else
                    {
                        set<char> tempSet;
                        tempSet=getFollowSet(it->getLeft());
                        tempFollow.insert(tempSet.begin(),tempSet.end());
                        vector<Producer>::iterator itIn;
                        for(itIn=produce_.begin(); itIn!=produce_.end(); itIn++)
                        {
                            if(itIn->getLeft()==subString[1])
                            {
                                string tempStringIn;
                                tempStringIn=itIn->getRight();
                                bool flagIn=true;
                                int indexIn=0;
                                for(int i=0; i<tempStringIn.size(); i++)
                                {
                                    if(ifCanbeVoid(tempStringIn[i])==false)
                                    {
                                        flagIn=false;
                                        break;
                                    }
                                    else
                                    {
                                        indexIn++;
                                    }
                                }
                                if(flagIn==false)
                                {
                                    if(isTerSym(tempStringIn[indexIn])==true)
                                    {
                                        tempFollow.insert(tempStringIn[indexIn]);
                                    }
                                    else
                                    {
                                        set<char> tempSetIn=getFirstSet(tempStringIn[indexIn]);
                                        tempFollow.insert(tempSetIn.begin(),tempSetIn.end());
                                    }
                                }
                            }
                        }

                    }

                }
            }
            else if(tempString.find(target)==tempString.size()-1)
            {
                //β为空
                set<char> tempSet;
                tempSet=getFollowSet(it->getLeft());
                tempFollow.insert(tempSet.begin(),tempSet.end());
            }
        }
    }
    return tempFollow;
}
set<char> SemaAnalyzer::getSelectSet(Producer p)
{
    set<char> select;
    set<char> beVoid=getCanVoid();
    string tempString=p.getRight();
    bool flag=true;
    for(int i=0; i<tempString.length(); i++)
    {
        if(beVoid.find(tempString[i])==beVoid.end())
        {
            flag=false;
            break;
        }
    }
    if(flag==false)
    {
        //该产生式的右部推导不出空
        if(isTerSym(tempString[0])==true)
        {
            select.insert(tempString[0]);
        }
        else
        {
            select=getFirstSet(tempString[0]);
        }
        return select;
    }
    else
    {
        select=getFollowSet(p.getLeft());
        set<char> tempSet;
        if(isTerSym(tempString[0])==true)
        {
            tempSet.insert(tempString[0]);
        }
        else
        {
            tempSet=getFirstSet(tempString[0]);
        }
        select.insert(tempSet.begin(),tempSet.end());
        return select;
    }
}
int SemaAnalyzer::getNterIndex(char a)
{
    vector<char>::iterator it;
    int index=0;
    for(it=nterSym_.begin(); it!=nterSym_.end(); it++)
    {
        if((*it)==a)
        {
            break;
        }
        else
        {
            index++;
        }
    }
    return index;
}
int SemaAnalyzer::getTerIndex(char a)
{
    vector<char>::iterator it;
    int index=0;
    for(it=terSym_.begin(); it!=terSym_.end(); it++)
    {
        if((*it)==a)
        {
            break;
        }
        else
        {
            index++;
        }
    }
    return index;
}
bool SemaAnalyzer::isTerSym(char wait)
{
    bool flag=false;
    vector<char>::iterator it;
    for(it=terSym_.begin(); it!=terSym_.end(); it++)
    {
        if((*it)==wait)
        {
            flag=true;
            break;
        }
    }
    return flag;
}
bool SemaAnalyzer::isNTerSym(char wait)
{
    bool flag=false;
    vector<char>::iterator it;
    for(it=nterSym_.begin(); it!=nterSym_.end(); it++)
    {
        if((*it)==wait)
        {
            flag=true;
            break;
        }
    }
    return flag;
}
/**********First集合**********/
void SemaAnalyzer::setFirst()
{
    vector<char>::iterator it;
    for(it=nterSym_.begin(); it!=nterSym_.end(); it++)
    {
        set<char> temp=getFirstSet(*it);
        setFirstOnly(temp,getNterIndex(*it));
    }
}
void SemaAnalyzer::setFirstOnly(set<char> a,int b)
{
    firstSet_[b]=a;
}
void SemaAnalyzer::showFirstSet()
{
    vector<char>::iterator iter;
    for(iter=nterSym_.begin(); iter!=nterSym_.end(); iter++)
    {
        cout<<"FirstSet for"<<(*iter)<<":"<<endl;
        set<char>::iterator it;
        int i=getNterIndex(*iter);
        for(it=firstSet_[i].begin(); it!=firstSet_[i].end(); it++)
        {
            cout<<(*it)<<" ";
        }
        cout<<endl;
    }
}
/**********Follow集合**********/
void SemaAnalyzer::setFollow()
{
    vector<char>::iterator it;
    for(it=nterSym_.begin(); it!=nterSym_.end(); it++)
    {
        set<char> temp=getFollowSet(*it);
        setFollowOnly(temp,getNterIndex(*it));
    }
}
void SemaAnalyzer::setFollowOnly(set<char> a,int b)
{
    followSet_[b].insert(a.begin(),a.end());
}
void SemaAnalyzer::showFollowSet()
{
    vector<char>::iterator iter;
    for(iter=nterSym_.begin(); iter!=nterSym_.end(); iter++)
    {
        cout<<"FollowSet for"<<(*iter)<<":"<<endl;
        set<char>::iterator it;
        int i=getNterIndex(*iter);
        for(it=followSet_[i].begin(); it!=followSet_[i].end(); it++)
        {
            cout<<(*it)<<" ";
        }
        cout<<endl;
    }
}
/****select集合****/
void SemaAnalyzer::setSelect()
{
    vector<Producer>::iterator it;
    int i=0;
    for(it=produce_.begin(); it!=produce_.end(); it++)
    {
        set<char> temp;
        temp=getSelectSet(*it);
        selectSet_[i]=temp;
        i++;
    }
}
void SemaAnalyzer::showSelectSet()
{
    vector<Producer>::iterator iter;
    int i=0;
    for(iter=produce_.begin(); iter!=produce_.end(); iter++)
    {
        cout<<"SelectSet for"<<iter->getLeft()<<"->"<<iter->getRight()<<":"<<endl;
        set<char>::iterator it;
        for(it=selectSet_[i].begin(); it!=selectSet_[i].end(); it++)
        {
            cout<<(*it)<<" ";
        }
        i++;
        cout<<endl;
    }
}
void SemaAnalyzer::showProducer()
{
    cout<<"产生式"<<":"<<endl;
    vector<Producer>::iterator iter;
    for(iter=produce_.begin(); iter!=produce_.end(); iter++)
    {
        cout<<iter->getLeft()<<"->"<<iter->getRight()<<endl;
    }
}
void SemaAnalyzer::setKnowTable()
{
    knowTable_=new int*[nterSym_.size()];
    for(int i=0; i<nterSym_.size(); i++)
    {
        knowTable_[i]=new int[terSym_.size()];
    }
    for(int i=0; i<nterSym_.size(); i++)
    {
        for(int j=0; j<terSym_.size(); j++)
        {
            knowTable_[i][j]=-1;
        }
    }
    vector<Producer>::iterator iter;
    int i=0;
    for(iter=produce_.begin(); iter!=produce_.end(); iter++)
    {
        int indexRow=getNterIndex(iter->getLeft());

        set<char>::iterator it;
        for(it=selectSet_[i].begin(); it!=selectSet_[i].end(); it++)
        {
            int indexCol=getTerIndex(*it);
            knowTable_[indexRow][indexCol]=i;
        }
        i++;
    }
}
void SemaAnalyzer::showKnowTable()
{
    cout<<"知识表:"<<endl;
    for(int i=0; i<nterSym_.size(); i++)
    {
        for(int j=0; j<terSym_.size(); j++)
        {
            cout<<knowTable_[i][j]<<" ";
        }
        cout<<endl;
    }
}
int SemaAnalyzer::LL1Ana(string idenString)
{
    int catcherr;
    int curIndex=0;
    semaStack_.push('#');
    semaStack_.push(startSym_);
    while(semaStack_.top()!='#')
    {
        char curChar=idenString[curIndex];
        char stackTop=semaStack_.top();
        semaStack_.pop();
        if(isTerSym(stackTop))
        {
            if(curChar==stackTop)
            {
                curIndex++;
                continue;
            }
            else
            {
                catcherr=-1;
                break;
            }
        }
        else if(isNTerSym(stackTop))
        {
            int indexRow=getNterIndex(stackTop);
            int indexCol=getTerIndex(curChar);
            int indexPro=knowTable_[indexRow][indexCol];
            if(indexPro==-1)
            {
                catcherr=-1;
                break;
            }
            string tempString=produce_[indexPro].getRight();
            for(int i=tempString.length()-1; i>=0; i--)
            {
                semaStack_.push(tempString[i]);
            }
            continue;
        }
    }
    if(catcherr!=-1&&idenString[curIndex]=='#')
    {
        cout<<"该句子可以被此文法接受"<<endl;
    }
    else
    {
        cout<<"该句子不能被此文法接受"<<endl;
    }
}
string SemaAnalyzer::TokentransForm()
{
    TokenAnalyzer c;
    int catchError=c.automachine("C:/Users/lenovo/Desktop/Compiler/test2.txt");
    if(catchError!=-1)
    {
        c.showResult();
    }
    string deal;
    vector<Token>::iterator it;
    vector<Token> result=c.getResult();
    for(it=result.begin(); it!=result.end(); it++)
    {
        if(it->getType()==0)
        {
            deal=deal+'I';
        }
        else if(it->getType()==3)
        {
            deal=deal+'I';
        }
        else if(it->getType()==16||it->getType()==17)
        {
            deal=deal+'w';
        }
        else if(it->getType()==18||it->getType()==19)
        {
            deal=deal+'v';
        }
        else if(it->getType()==24)
        {
            deal=deal+'(';
        }
        else if(it->getType()==25)
        {
            deal=deal+')';
        }
    }
    deal=deal+'#';
    cout<<"转换后的字符串"<<deal<<endl;
    return deal;
}
/*******递归下降子程序分析法*******/
void SemaAnalyzer::recurZ(string idenString)
{
    int curIndex=0;
    curIndex=recurE(idenString,curIndex);
    if(curIndex!=-1)
    {
        cout<<"识别串可以被该文法接收"<<endl;
    }
    else
    {
        cout<<"识别串不能接收"<<endl;
    }
}
int SemaAnalyzer::recurE(string idenString,int curIndex)
{
    if(curIndex!=-1)
    {
        cout<<"使用产生式E->TR推导"<<endl;
    curIndex=recurT(idenString,curIndex);
    curIndex=recurR(idenString,curIndex);
    }
    return curIndex;
}
int SemaAnalyzer::recurR(string idenString,int curIndex)
{
    if(curIndex!=-1)
    {
    if(idenString[curIndex]=='w')
    {
        cout<<"使用产生式R->wTR推导"<<endl;
        curIndex++;
        curIndex=recurT(idenString,curIndex);
        curIndex=recurR(idenString,curIndex);
    }
    }
    return curIndex;
}
int SemaAnalyzer::recurT(string idenString,int curIndex)
{
    if(curIndex!=-1)
    {
    cout<<"使用产生式T->FU推导"<<endl;
    curIndex=recurF(idenString,curIndex);
    curIndex=recurU(idenString,curIndex);
    }
    return curIndex;
}
int SemaAnalyzer::recurU(string idenString,int curIndex)
{
    if(curIndex!=-1)
    {
    if(idenString[curIndex]=='v')
    {
        cout<<"使用产生式U->vFU推导"<<endl;
        curIndex++;
        curIndex=recurF(idenString,curIndex);
        curIndex=recurU(idenString,curIndex);
    }
    }
    return curIndex;
}
int SemaAnalyzer::recurF(string idenString,int curIndex)
{
    if(curIndex!=-1)
    {
    cout<<curIndex<<endl;
    if(idenString[curIndex]=='I')
    {
        cout<<"使用产生式F->I推导"<<endl;
        curIndex++;
        return curIndex;
    }
    else if(idenString[curIndex]=='(')
    {
        cout<<"使用产生式F->(E)推导"<<endl;
        curIndex++;
        curIndex=recurE(idenString,curIndex);
        if(idenString[curIndex]==')')
        {
            curIndex++;
        }
        else
        {
            curIndex=-1;
        }
        return curIndex;
    }
    }
}
