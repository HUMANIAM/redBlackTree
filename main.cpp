#include <iostream>
#include "redblack.h"
using namespace std;

int main()
{
    RedBlackTree<int>rdb;
    std::vector<int> t = {10, 20, 30, 40, 35, 34, 100, 90, 80, 70, 60, 50};
    vector<int> tt = {10, 20};
    vector<bool> xxx= rdb.add(t);
     rdb.print();

    for(auto x : tt)
        rdb.remove(x);


    cout << "############################################\n";
    rdb.print();

    //cout << rdb.search(x) << endl;


//    ff(4);
    return 0;
}
