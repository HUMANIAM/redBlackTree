#include "../redblack.h"
#define TEST true

#define CATCH_CONFIG_RUNNER
#define TEST true
#include <catch.hpp>
#include <chrono>
int main( int argc, char* const argv[] )
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
    SECTION("single item")
    {
        RedBlackTree<int> red_black_tree;
        bool added = red_black_tree.add(1);
        CHECK(added == true);

    }
    SECTION("add vector")
    {
        RedBlackTree<int> red_black_tree;
        std::vector<int> v={1,2,3,4,5,6,7};
        std::vector<bool> vb = red_black_tree.add(v);
        std::vector<bool> correct = {true,true,true,true,true,true,true};
        CHECK(vb == correct);
    }
    SECTION("add dublicate")
    {
        RedBlackTree<int> red_black_tree;
        bool added = red_black_tree.add(4);
        int temp = 4;
        bool notAdded = red_black_tree.add(temp);
        CHECK(added!=notAdded);

    }
    SECTION("vector dublicates")
    {
        std::vector<int> v = {1,4,1,4};
        std::vector<bool> correct = {true,true,false,false};
        RedBlackTree<int> red_black_tree;
        std::vector<bool> vb = red_black_tree.add(v);
        CHECK(vb==correct);


    }

}

TEST_CASE("search functions tests")
{
    SECTION("search single item exists")
    {   RedBlackTree<int> red_black_tree;
        red_black_tree.add(4);
        CHECK(red_black_tree.search(4)==true);
    }
    SECTION("search single item doesnt exist")
    {   RedBlackTree<int> red_black_tree;
        red_black_tree.add(4);
        CHECK(red_black_tree.search(5)==false);
    }
    SECTION("search root null")
    {   RedBlackTree<int> red_black_tree;
        CHECK(red_black_tree.search(4)==false);
    }
    SECTION("search list of items exists")
    {   RedBlackTree<int> red_black_tree;
        std::vector<int> v ={1,2,3,4,5};
        std::vector<bool> vb ={true,true,true,true,true};
        red_black_tree.add(v);
        CHECK(red_black_tree.search(v)==vb);
    }
    SECTION("search list of items  doesnt exist")
    {   RedBlackTree<int> red_black_tree;
        std::vector<int> v ={1,2,3,4,5};
        std::vector<bool> vb ={true,true,false,true,false};
        std::vector<int> v1 ={1,2,6,4,8};
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
        std::vector<int> vb = {1,2,3,4};
        CHECK(red_black_tree.check_element_order(vb));

    }
}

TEST_CASE("Benchmark")
{
    SECTION("map insert sorted")
    {

        std::cout<<"Sorted bench zeft"<<std::endl;
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
        std::srand(1);
        std::cout<<std::endl<<std::endl<<"random bench zeft"<<std::endl;
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


