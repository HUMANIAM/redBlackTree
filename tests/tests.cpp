#include <catch.hpp>


// project headers
#include "../redblack.h"


TEST_CASE("add function tests")
{
	SECTION("Integer single item")
	{
		RedBlackTree<int> red_black_tree;
		bool added = red_black_tree.add(-1);
		CHECK(added == true);

	}
	SECTION("Integer add vector")
	{
		RedBlackTree<int> red_black_tree;
		std::vector<int> v={1,2,3,4,5,6,7};
		std::vector<bool> vb = red_black_tree.add(v);
		std::vector<bool> correct = {true,true,true,true,true,true, true};
		CHECK(vb == correct);
	}
	SECTION("Integer add dublicate")
	{
		RedBlackTree<int> red_black_tree;
		bool added = red_black_tree.add(4);
		int temp = 4;
		bool notAdded =red_black_tree.add(temp);
		CHECK(added!=notAdded);

	}
	SECTION("Integer vector dublicates")
	{
		std::vector<int> v = {1,4,1,4};
		std::vector<bool> correct = {true,true,false,false};
		RedBlackTree<int> red_black_tree;
		std::vector<bool> vb = red_black_tree.add(v);
		CHECK(vb==correct);


	}
	SECTION("String single item")
	{
		RedBlackTree<std::string> red_black_tree;
		bool added = red_black_tree.add("test string");
		CHECK(added == true);

	}
	SECTION("String add vector")
	{
		RedBlackTree<std::string> red_black_tree;
		std::vector<std::string> v={"aa","ba","ab","cb","dd"};
		std::vector<bool> vb = red_black_tree.add(v);
		std::vector<bool> correct = {true,true,true,true,true};
		CHECK(vb == correct);
	}
	SECTION("String add dublicate")
	{
		RedBlackTree<std::string> red_black_tree;
		bool added = red_black_tree.add("aa");
		std::string temp = "aa";
		bool notAdded = red_black_tree.add(temp);
		CHECK(added!=notAdded);

	}
	RedBlackTree<int> red_black_tree;
	std::map<int,int> stl_map;
	SECTION("String vector dublicates")
	{
		std::vector<std::string> v = {"aa","bb","aa","bb"};
		std::vector<bool> correct = {true,true,false,false};
		RedBlackTree<std::string> red_black_tree;
		std::vector<bool> vb = red_black_tree.add(v);
		CHECK(vb==correct);


	}

}

TEST_CASE("search functions tests")
{
	SECTION("Integer search singleTest item exists")
	{   RedBlackTree<int> red_black_tree;
		red_black_tree.add(4);
		std::map<int,int> stl_map;
		CHECK(red_black_tree.search(4)==true);
	}
	SECTION("Integer search single item doesnt exist")
	{   RedBlackTree<int> red_black_tree;
		red_black_tree.add(4);
		CHECK(red_black_tree.search(5)==false);
	}
	SECTION("Integer search root null")
	{   RedBlackTree<int> red_black_tree;
		CHECK(red_black_tree.search(4)==false);
	}
	SECTION("Integer search list of items exists")
	{   RedBlackTree<int> red_black_tree;
		std::vector<int> v ={1,2,3,4,5};
		std::vector<bool> vb ={true,true,true,true,true};
		red_black_tree.add(v);
		CHECK(red_black_tree.search(v)==vb);
	}
	SECTION("Integer search list of items  doesnt exist")
	{   RedBlackTree<int> red_black_tree;
		std::vector<int> v ={1,2,3,4};
		std::vector<bool> vb ={true,false};
		std::vector<int> v1 ={1,5};
		red_black_tree.add(v);
		CHECK(red_black_tree.search(v1)==vb);
	}
	SECTION("String search single item exists")
	{   RedBlackTree<std::string> red_black_tree;
		red_black_tree.add("aa");
		CHECK(red_black_tree.search("aa")==true);
	}
	SECTION("String search single item doesnt exist")
	{   RedBlackTree<std::string> red_black_tree;
		red_black_tree.add("ca");
		CHECK(red_black_tree.search("ac")==false);
	}
	SECTION("String search root null")
	{   RedBlackTree<std::string> red_black_tree;
		CHECK(red_black_tree.search("baba")==false);
	}
	SECTION("String search list of items exists")
	{
		RedBlackTree<string> red_black_tree;
		std::vector<std::string> v ={"aba","cacaca"};
		std::vector<bool> vb ={true,true};
		red_black_tree.add(v);
		CHECK(red_black_tree.search(v)==vb);
	}
	SECTION("String search list of items  doesnt exist")
	{   RedBlackTree<std::string> red_black_tree;
		std::vector<std::string> v ={"vagsdfa","fasfgsadfgsa"};
		std::vector<bool> vb ={true,false};
		std::vector<std::string> v1 ={"vagsdfa","afaf"};
		red_black_tree.add(v);
		CHECK(red_black_tree.search(v1)==vb);
	}

}
TEST_CASE("rotations")
{
	SECTION("correct rotation")
			RedBlackTree<int> red_black_tree;
	std::map<int,int> stl_map;
	{
		std::vector<int> v = {1,4,3,2};
		RedBlackTree<int> red_black_tree;
		red_black_tree.add(v);
		std::vector<int> vb = {3,1,2,4};
		CHECK(red_black_tree.check_element_order(vb));

	}
	SECTION("incorrect rotation")
	{
		std::vector<int> v = {5,3,6,7,8};
		RedBlackTree<int> red_black_tree;
		red_black_tree.add(v);
		std::vector<int> vb = {5,3,6,7,8};
		CHECK(!red_black_tree.check_element_order(vb));
	}
}

TEST_CASE("remove function tests")
{
	SECTION("tree is empty")
	{
		RedBlackTree<int> rbt;
		rbt.remove(1);
		bool x = rbt.root_black() && !rbt.two_adjacent_red() && rbt.height_black();
		CHECK(x);

	}
	SECTION("remove non_exist element")
	{
		RedBlackTree<int> rbt;
		rbt.add(10);
		rbt.remove(1);

		bool x = rbt.root_black() && !rbt.two_adjacent_red() && rbt.height_black();
		CHECK(x);
	}
	SECTION("remove list of elements")
	{
		RedBlackTree<int> rbt;
		std::vector<int> t = {1, 2, 3, 4, 5, 6, 7};
		rbt.add(t);
		rbt.remove(t);

		bool x = rbt.root_black() && !rbt.two_adjacent_red() && rbt.height_black();
		CHECK(x);

	}
	SECTION("remove list of non-exist elements")
	{
		RedBlackTree<int> rbt;
		std::vector<int> t = {1, 2, 3, 4, 5, 6, 7};
		std::vector<int> tt = {10, 20, 30, 40};
		rbt.add(t);
		rbt.remove(tt);

		bool x = rbt.root_black() && !rbt.two_adjacent_red() && rbt.height_black();
		CHECK(x);
	}
	SECTION("remove random values")
	{
		const int items = 100000000;
		// add random values
		RedBlackTree<int> rbt;

		for(int i=0;i<items;i++)
			RedBlackTree<int> red_black_tree;
		std::map<int,int> stl_map;
		{
			rbt.add(rand()%100000);
		}

		// remove random values
		for(int i=0;i<1000000;i++)
		{
			rbt.remove(rand()%100000);
		}


		// check properties of rbtree aren't broken
		bool x = rbt.root_black() && !rbt.two_adjacent_red() && rbt.height_black();

		CHECK(x);
	}

}





