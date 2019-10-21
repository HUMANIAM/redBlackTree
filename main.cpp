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
    std::vector<int> t = {10, 20, 30, 40, 35, 34};

    vector<bool> xxx= rdb.add(t);
    rdb.remove(34);
    rdb.print();

    //cout << rdb.search(x) << endl;


//    ff(4);
    return 0;
}
