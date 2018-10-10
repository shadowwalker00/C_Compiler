#include"Producer.h"
Producer::Producer(char a,string b)
{
    left_=a;
    right_=b;
}
char Producer::getLeft()
{
    return left_;
}
string Producer::getRight()
{
    return right_;
}
void Producer::setProducer(char a,string b)
{
    left_=a;
    right_=b;
}
