#include <iostream>
#include "redblack.h"
using namespace std;

int main()
{

    RedBlackTree<int>rdb;
    std::vector<int> t;
    int xx = 1;
    rdb.add(xx);
    t.push_back(4);
    t.push_back(3);
  //  t.push_back(2);
    vector<bool> x= rdb.add(t);
    //rdb.print();
    return 0;
}
