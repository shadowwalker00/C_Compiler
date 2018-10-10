#ifndef PRODUCER_H_INCLUDED
#define PRODUCER_H_INCLUDED
#include<string>
using namespace std;
class Producer
{
public:
    Producer(char a,string b);
    char getLeft();
    string getRight();
    void setProducer(char left,string right);
private:
    char  left_;
    string right_;
};
#endif // PRODUCER_H_INCLUDED
