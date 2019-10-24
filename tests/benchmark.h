#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <chrono>
#include <time.h>
#include <string>
#include <map>
using namespace std;

// project headers
#include "../redblack.h"

template <typename Duration>
auto duration_time(Duration const& duration) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration);
}

const int items = 100000000;

class Test{
    int items;


    template<typename T>
    long insert_stl_map(const std::vector<T>&, map<T, int>);

    template<typename T>
    long insert_rbTree(const std::vector<T>&, RedBlackTree<T>);

    public:
    Test (int items):items(items){}

    // test for lvalue objects that has expensive cost of copy like strings, containers, larger user-defined objs
    long lvalue_sorted_strings();
    long lvalue_ranodem_strings();

    // test for rvalue objects that has expensive cost of copy like strings, containers, larger user-defined objs
    long rvalue_sorted_strings();
    long rvalue_ranodem_strings();

    // test for integer numbers
    long sorted_integers();
    long random_integers();

};

template <typename T >
long Test::insert_stl_map(const std::vector<T>& elements, map<T, int> stl_map){
    auto start_t = std::chrono::high_resolution_clock::now();
    for(auto it : elements){  stl_map[it] = 0;}
    auto end_t = std::chrono::high_resolution_clock::now();

    return duration_time(end_t - start_t).count();
}

template<typename T>
long insert_rbTree(const std::vector<T>& elements, RedBlackTree<T> rbt){
    auto start_t = std::chrono::high_resolution_clock::now();
    for(auto it : elements){  rbt.add(it);}
    auto end_t = std::chrono::high_resolution_clock::now();

    return duration_time(end_t - start_t).count();
}


//long Test::lvalue_sorted_strings(){
//     RedBlackTree<std::string> rbt;
//     std::map<std::string,int> std_map;
//     std::vector<std::string> inserted_items;

//     // insert items in stl_map and rbtree
//     for(int i=0;i<items;i++){inserted_items.push_back(std::to_string(i));}
//     for(auto it : inserted_items){   std_map[it] = 0;  rbt.add(it); }

//     /** compute deletion time */

//     // deletion time taken by rbt
//     auto insert_time_rbt = std::chrono::high_resolution_clock::now();
//     for(auto it : inserted_items){   rbt.remove(it); }
//     auto finish_insert_time_rbt = std::chrono::high_resolution_clock::now();

//     // deletion time taken by stl map
//     auto insert_time_map = std::chrono::high_resolution_clock::now();
//     for(auto it : inserted_items){   std_map.erase(it); }
//     auto finish_insert_time_map = std::chrono::high_resolution_clock::now();

//     std::cout << "\n          #####################################\n";
//     std::cout << "          Deletion Benchmark For Sorted Strings of Numbers\n";
//     std::cout << "          #####################################\n";
//     auto map_duration = std::chrono::duration_cast<std::chrono::milliseconds>
//             (finish_insert_time_map - insert_time_map).count();
//     std::cout<<"STL_MAP  =  " << map_duration << std::endl;

//     auto rbt_duration = std::chrono::duration_cast<std::chrono::milliseconds>
//             (finish_insert_time_rbt - insert_time_rbt).count();
//     std::cout << "RB_Tree =  " << rbt_duration << std::endl;

//}

//long Test::rvalue_sorted_strings(){
//    RedBlackTree<std::string> rbt;
//    std::map<std::string,int> std_map;

//    // insert items
//    for(int i=0;i<items;i++){std_map[std::to_string(i)]=0; rbt.add(std::to_string(i));};

//    // delete items time

//}


#endif // BENCHMARK_H
