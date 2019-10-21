#include <iostream>
#include "redblack.h"
using namespace std;

int main()
{
    int x = 15;
//    //f(new int(5));
//    f(10, new int);
//    f(10);
    RedBlackTree<int>rdb;
    std::vector<int> t;
    int xx = 1;
    rdb.add(xx);
    t.push_back(4);
    t.push_back(3);
    t.push_back(2);
    vector<bool> xxx= rdb.add(t);
    //rdb.print();

    cout << rdb.search(x) << endl;


//    ff(4);
    return 0;
}
