#include <iostream>
#include "redblack.h"
using namespace std;
template<class T,class T2>
bool fun(T x,T2 y)
{
    return x==y;
}
int main()
{
    RedBlackTree<int>rdb;
    std::vector<int> t;
    t.push_back(3);
    int xx = 5;
    vector<bool> x= rdb.add(t);
    rdb.add(xx);
    rdb.search(t);
    fun(xx,4);

    return 0;
}
