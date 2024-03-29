#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <chrono>
#include <time.h>
#include <string>
#include <set>
using namespace std;
#define PRINT_DASHES 61

// project headers
#include "redblack.h"

template <typename Duration>
auto duration_time(Duration const& duration)
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(duration);
}

/// Benchmark class
class Benchmark
{

public:

	template<typename T>
	vector<long> test_all_lvalue_objects(const vector<T>&);

	template<typename T>
	vector<long> test_all_rvalue_objects(const vector<T>&);

	// insertion of lvalues
	template<typename T>
	long insert_stl_set_lvalue(const std::vector<T>&);

	template<typename T>
	long insert_rbTree_lvalue(const std::vector<T>&);

	// insert rvalues
	template<typename T>
	long insert_stl_set_rvalue(const std::vector<T>&);

	template<typename T>
	long insert_rbTree_rvalue(const std::vector<T>&);

	// deletion of rvalues
	template<typename T>
	long delete_stl_set_lvalue(const std::vector<T>&);

	template<typename T>
	long delete_rbTree_lvalue(const std::vector<T>&);

	// insert rvalues
	template<typename T>
	long delete_stl_set_rvalue(const std::vector<T>&);

	template<typename T>
	long delete_rbTree_rvalue(const std::vector<T>&);
};

template<typename T>
vector<long> Benchmark::test_all_lvalue_objects(const vector<T>& elements)
{
	vector<long> results;
	results.push_back(insert_stl_set_lvalue(elements));
	results.push_back(insert_rbTree_lvalue(elements));
	results.push_back(delete_stl_set_lvalue(elements));
	results.push_back(delete_rbTree_lvalue(elements));
	return results;
}

template<typename T>
vector<long> Benchmark::test_all_rvalue_objects(const vector<T>& elements)
{
	vector<long> results;
	results.push_back(insert_stl_set_rvalue(elements));
	results.push_back(insert_rbTree_rvalue(elements));
	results.push_back(delete_stl_set_rvalue(elements));
	results.push_back(delete_rbTree_rvalue(elements));
	return results;
}

template <typename T >
long Benchmark::insert_stl_set_lvalue(const std::vector<T>& elements)
{
	set<T> stl_set;
	auto start_t = std::chrono::high_resolution_clock::now();
	for(auto it : elements)
	{
		stl_set.insert(it);
	}
	auto end_t = std::chrono::high_resolution_clock::now();

	return duration_time(end_t - start_t).count();
}

template<typename T>
long Benchmark::insert_rbTree_lvalue(const std::vector<T>& elements)
{
	RedBlackTree<T> rbt;
	auto start_t = std::chrono::high_resolution_clock::now();
	for(auto it : elements)
	{
		rbt.add(it);
	}
	auto end_t = std::chrono::high_resolution_clock::now();

	return duration_time(end_t - start_t).count();
}


template<typename T>
long Benchmark::Benchmark::insert_stl_set_rvalue(const std::vector<T>& elements)
{
	set<T> stl_set;
	auto start_t = std::chrono::high_resolution_clock::now();
	for(auto it : elements)
	{
		stl_set.insert(move(it));
	}
	auto end_t = std::chrono::high_resolution_clock::now();

	return duration_time(end_t - start_t).count();
}

template<typename T>
long Benchmark::insert_rbTree_rvalue(const std::vector<T>& elements)
{
	RedBlackTree<T> rbt;
	auto start_t = std::chrono::high_resolution_clock::now();
	for(auto it : elements)
	{
		rbt.add(move(it));
	}
	auto end_t = std::chrono::high_resolution_clock::now();

	return duration_time(end_t - start_t).count();
}

template <typename T >
long Benchmark::delete_stl_set_lvalue(const std::vector<T>& elements)
{
	set<T> stl_set;
	auto start_t = std::chrono::high_resolution_clock::now();
	for(auto it : elements)
	{
		stl_set.erase(it);
	}
	auto end_t = std::chrono::high_resolution_clock::now();

	return duration_time(end_t - start_t).count();
}

template<typename T>
long Benchmark::delete_rbTree_lvalue(const std::vector<T>& elements)
{
	RedBlackTree<T> rbt;
	auto start_t = std::chrono::high_resolution_clock::now();
	for(auto it : elements)
	{
		rbt.remove(it);
	}
	auto end_t = std::chrono::high_resolution_clock::now();

	return duration_time(end_t - start_t).count();
}


template<typename T>
long Benchmark::delete_stl_set_rvalue(const std::vector<T>& elements)
{
	set<T> stl_set;
	auto start_t = std::chrono::high_resolution_clock::now();
	for(auto it : elements)
	{
		stl_set.erase(move(it));
	}
	auto end_t = std::chrono::high_resolution_clock::now();

	return duration_time(end_t - start_t).count();
}

template<typename T>
long Benchmark::delete_rbTree_rvalue(const std::vector<T>& elements)
{
	RedBlackTree<T> rbt;
	auto start_t = std::chrono::high_resolution_clock::now();
	for(auto it : elements)
	{
		rbt.remove(move(it));
	}
	auto end_t = std::chrono::high_resolution_clock::now();

	return duration_time(end_t - start_t).count();
}
///////////////////////////////////////////////////////////////////

const int max_items = 1e7;
const int max_Rondom = 1e7;
static Benchmark benchmark;

static void print_headers(const string& type)
{
	cout << "  Comparison with " << type << endl;
	for(int i=0;i<PRINT_DASHES;i++)
		cout<<"*";
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

static void print_results(int test_size,vector<long> v)
{
	int limit=8;
	cout<<test_size;
	int size = to_string(test_size).length();

	for(int j=0;j<limit - size;j++)
		cout<<" ";
	cout<<"|";

	for(uint i = 0 ; i < 4 ; i++ )
	{
		limit=10;
		cout<<" "<<v[i];
		size = to_string(v[i]).length();
		for(int j=0;j<limit - size;j++)
			cout<<" ";
		cout<<" |";
	}
	cout<<endl;
	for(int i=0;i<PRINT_DASHES;i++)
		cout<<"-";
	cout<<endl;
}
///  ####### Benchmark for insertion and deletion of our RB tree agains STL set (implemented using RB Tree also)
static vector<int> get_sorted_integers(int sz)
{
	vector<int> elements;
	for(int i=0; i < sz; i++)
	{
		elements.push_back(i);
	}
	return elements;
}

static vector<int> get_unsorted_integers(int sz)
{
	vector<int> elements;
	for(int i=0; i < sz; i++)
	{
		elements.push_back(rand() % max_Rondom);
	}
	return elements;
}

static vector<string> get_sorted_strings(int sz)
{
	vector<string> elements;
	for(int i=0; i < sz; i++)
	{
		elements.push_back(to_string(i));
	}
	return elements;
}

static vector<string> get_unsorted_strings(int sz)
{
	vector<string> elements;
	for(int i=0; i < sz; i++)
	{
		elements.push_back(to_string(rand() % max_Rondom));
	}
	return elements;
}

// Deletion and insertin of primitive values like int, float, ...
void primitive_benchmark()
{
	print_headers("Integers (primitive type) in sorted order");

	for(int citem = 100; citem <= max_items; citem *= 10)
	{
		vector<long> results = benchmark.test_all_lvalue_objects(get_sorted_integers(citem));
		print_results(citem, results);
	}
	cout << "\n";

	print_headers("Integers (primitive type) in unsorted order");

	for(int citem = 100; citem <= max_items; citem *= 10)
	{
		vector<long> results = benchmark.test_all_lvalue_objects(get_unsorted_integers(citem));
		print_results(citem, results);
	}
	cout << "\n";

}

// Deletion and insertion of lvalue objects has expensive copy operation like vectors, strings, user-defined objects
void lvalue_benchmark()
{
	print_headers("Strings passed as lvalue");

	for(int citem = 100; citem <= max_items; citem *= 10)
	{
		vector<long> results = benchmark.test_all_lvalue_objects(get_unsorted_strings(citem));
		print_results(citem, results);
	}
	cout << "\n";
}

// Deletion and insertion of lvalue objects has expensive copy operation like vectors, strings, user-defined objects
void rvalue_benchmark()
{
	print_headers("Strings passed as rvalue");

	for(int citem = 100; citem <= max_items; citem *= 10)
	{
		vector<long> results = benchmark.test_all_rvalue_objects(get_unsorted_strings(citem));
		print_results(citem, results);
	}
	cout << "\n";
}

void run_benchmark()
{
	primitive_benchmark();
	lvalue_benchmark();
	rvalue_benchmark();
}
#endif // BENCHMARK_H
