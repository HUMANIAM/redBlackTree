#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <chrono>
#include <time.h>
#include <string>
#include <map>
using namespace std;
#define PRINT_DASHES 61
// project headers
#include "../redblack.h"
void print_headers(const string& type)
{
    cout << "  Comparison with " << type << endl;
    for(int i=0;i<PRINT_DASHES;i++)
        cout<<"#";
    cout<<endl;
    cout<<"Items   |";
    cout<<" stl_insert |";
    cout<<" rbt_insert |";
    cout<<" stl_delete |";
    cout<<" rbt_delete |";
    cout<<endl;
    for(int i=0;i<PRINT_DASHES;i++)
        cout<<"-";
    cout<<endl;
}

void print_results(int test_size,vector<long> v)
{    int limit;
     int size;
      limit=8;
       cout<<test_size;
        size = to_string(test_size).length();

         for(int j=0;j<limit - size;j++)
             cout<<" ";
          cout<<"|";

          for(uint i = 0 ; i < 4 ; i++ )
          {   limit=10;
              cout<<" "<<v[i];
              size = to_string(v[i]).length();
              for(int j=0;j<limit - size;j++)
                  cout<<" ";
              cout<<" |";
          }
           cout<<endl;
           for(int i=0;i<PRINT_DASHES;i++)
               cout<<"#";
            cout<<endl;
}
///////////////////////////////////////////////////////


template <typename Duration>
auto duration_time(Duration const& duration) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration);
}


class Benchmark{
    int items;

public:
    Benchmark (int items):items(items){}

    template<typename T>
    vector<long> test_all_lvalue_objects(const vector<T>&);

    template<typename T>
    vector<long> test_all_rvalue_objects();

    // insertion of lvalues
    template<typename T>
    long insert_stl_map_lvalue(const std::vector<T>&);

    template<typename T>
    long insert_rbTree_lvalue(const std::vector<T>&);

    // insert rvalues
    template<typename T>
    long insert_stl_map_rvalue(const std::vector<T>&);

    template<typename T>
    long insert_rbTree_rvalue(const std::vector<T>&);

    // deletion of rvalues
    template<typename T>
    long delete_stl_map_lvalue(const std::vector<T>&);

    template<typename T>
    long delete_rbTree_lvalue(const std::vector<T>&);

    // insert rvalues
    template<typename T>
    long delete_stl_map_rvalue(const std::vector<T>&);

    template<typename T>
    long delete_rbTree_rvalue(const std::vector<T>&);
};

template<typename T>
vector<long> Benchmark::test_all_lvalue_objects(const vector<T>& elements){
   vector<long> results;
   results.push_back(insert_stl_map_lvalue(elements));
   results.push_back(insert_rbTree_lvalue(elements));
   results.push_back(delete_stl_map_lvalue(elements));
   results.push_back(delete_rbTree_lvalue(elements));
   return results;
}

template <typename T >
long Benchmark::insert_stl_map_lvalue(const std::vector<T>& elements){
     map<T, int> stl_map;
    auto start_t = std::chrono::high_resolution_clock::now();
    for(auto it : elements){  stl_map[it] = 0;}
    auto end_t = std::chrono::high_resolution_clock::now();

    return duration_time(end_t - start_t).count();
}

template<typename T>
long Benchmark::insert_rbTree_lvalue(const std::vector<T>& elements){
    RedBlackTree<T> rbt;
    auto start_t = std::chrono::high_resolution_clock::now();
    for(auto it : elements){  rbt.add(it);}
    auto end_t = std::chrono::high_resolution_clock::now();

    return duration_time(end_t - start_t).count();
}


template<typename T>
long insert_stl_map_rvalue(const std::vector<T>& elements){
    map<T, int> stl_map;
    auto start_t = std::chrono::high_resolution_clock::now();
    for(auto it : elements){  stl_map[move(it)] = 0;}
    auto end_t = std::chrono::high_resolution_clock::now();

    return duration_time(end_t - start_t).count();
}

template<typename T>
long insert_rbTree_rvalue(const std::vector<T>& elements){
    RedBlackTree<T> rbt;
    auto start_t = std::chrono::high_resolution_clock::now();
    for(auto it : elements){  rbt.add(move(it));}
    auto end_t = std::chrono::high_resolution_clock::now();

    return duration_time(end_t - start_t).count();
}

template <typename T >
long Benchmark::delete_stl_map_lvalue(const std::vector<T>& elements){
    map<T, int> stl_map;
    auto start_t = std::chrono::high_resolution_clock::now();
    for(auto it : elements){  stl_map.erase(it);}
    auto end_t = std::chrono::high_resolution_clock::now();

    return duration_time(end_t - start_t).count();
}

template<typename T>
long Benchmark::delete_rbTree_lvalue(const std::vector<T>& elements){
    RedBlackTree<T> rbt;
    auto start_t = std::chrono::high_resolution_clock::now();
    for(auto it : elements){  rbt.remove(it);}
    auto end_t = std::chrono::high_resolution_clock::now();

    return duration_time(end_t - start_t).count();
}


template<typename T>
long delete_stl_map_rvalue(const std::vector<T>& elements){
    map<T, int> stl_map;
    auto start_t = std::chrono::high_resolution_clock::now();
    for(auto it : elements){  stl_map.erase(move(it));}
    auto end_t = std::chrono::high_resolution_clock::now();

    return duration_time(end_t - start_t).count();
}

template<typename T>
long delete_rbTree_rvalue(const std::vector<T>& elements){
    RedBlackTree<T> rbt;
    auto start_t = std::chrono::high_resolution_clock::now();
    for(auto it : elements){  rbt.remove(move(it));}
    auto end_t = std::chrono::high_resolution_clock::now();

    return duration_time(end_t - start_t).count();
}



#endif // BENCHMARK_H
