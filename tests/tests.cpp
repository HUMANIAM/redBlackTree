#include "../redblack.h"
#define CATCH_CONFIG_RUNNER
#define TEST true
#include <catch.hpp>
#include <chrono>
int main()
{
    //If the TEST macro is defined to be true,
    //runCatchTests will be called and immediately
    //return causing the program to terminate. Change TEST
    //to false in the macro def at the top of this file
    //to skip tests and run the rest of your code.
    if (TEST)
    {
        return Catch::Session().run();
    }

    //start working on other parts of your project here.
    return 0;
}

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
        std::vector<bool> correct = {true,true,true,true,true,true,true};
        CHECK(vb == correct);
    }
    SECTION("Integer add dublicate")
    {
        RedBlackTree<int> red_black_tree;
        bool added = red_black_tree.add(4);
        int temp = 4;
        bool notAdded = red_black_tree.add(temp);
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
    SECTION("Integer search single item exists")
    {   RedBlackTree<int> red_black_tree;
        red_black_tree.add(4);
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
    {   RedBlackTree<std::string> red_black_tree;
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

TEST_CASE("Benchmark")
{
    SECTION("map insert sorted")
    {
        std::cout<<"Sorted benchmark"<<std::endl;
        RedBlackTree<int> red_black_tree;
        std::map<int,int> std_map;
        auto insert_time_rbt = std::chrono::high_resolution_clock::now();
        for(int i=0;i<100000;i++)
        {
            red_black_tree.add(i);
        }
        auto finish_insert_time_rbt = std::chrono::high_resolution_clock::now();
        auto insert_time_map = std::chrono::high_resolution_clock::now();
        for(int i=0;i<100000;i++)
        {
            std_map[i] = i;
        }
        auto finish_insert_time_map = std::chrono::high_resolution_clock::now();
        auto map_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (finish_insert_time_map - insert_time_map).count();
        std::cout<<"Time for map =  "<<map_duration<<std::endl;
        auto rbt_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (finish_insert_time_rbt - insert_time_rbt).count();
        std::cout<<"Time for rbt =  "<<rbt_duration<<std::endl;

    }
    SECTION("map insert unsorted")
    {
        std::srand(2);
        std::cout<<std::endl<<std::endl<<"random benchmark"<<std::endl;
        RedBlackTree<int> red_black_tree;
        std::map<int,int> std_map;
        auto insert_time_rbt = std::chrono::high_resolution_clock::now();
        for(int i=0;i<100000;i++)
        {
            red_black_tree.add(rand()%100000);
        }
        auto finish_insert_time_rbt = std::chrono::high_resolution_clock::now();
        auto insert_time_map = std::chrono::high_resolution_clock::now();
        for(int i=0;i<100000;i++)
        {
            std_map[i] = rand()%100000;
        }
        auto finish_insert_time_map = std::chrono::high_resolution_clock::now();
        auto map_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (finish_insert_time_map - insert_time_map).count();
        std::cout<<"Time for map =  "<<map_duration<<std::endl;
        auto rbt_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (finish_insert_time_rbt - insert_time_rbt).count();
        std::cout<<"Time for rbt =  "<<rbt_duration<<std::endl;

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
        vector<int> t = {1, 2, 3, 4, 5, 6, 7};
        rbt.add(t);
        rbt.remove(t);

        bool x = rbt.root_black() && !rbt.two_adjacent_red() && rbt.height_black();
        CHECK(x);

    }
    SECTION("remove list of non-exist elements")
    {
        RedBlackTree<int> rbt;
        vector<int> t = {1, 2, 3, 4, 5, 6, 7};
        vector<int> tt = {10, 20, 30, 40};
        rbt.add(t);
        rbt.remove(tt);

        bool x = rbt.root_black() && !rbt.two_adjacent_red() && rbt.height_black();
        CHECK(x);
    }

}
