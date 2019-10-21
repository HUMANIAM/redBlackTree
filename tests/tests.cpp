#include "../redblack.h"
#define TEST true

#define CATCH_CONFIG_RUNNER
#define TEST true
#include <catch.hpp>
int main( int argc, char* const argv[] )
{
    //If the TEST macro is defined to be true,
    //runCatchTests will be called and immediately
    //return causing the program to terminate. Change TEST
    //to false in the macro def at the top of this file
    //to skip tests and run the rest of your code.
    if (TEST)
    {
        return Catch::Session().run(argc, argv);
    }

    //start working on other parts of your project here.
    return 0;
}

TEST_CASE("add function tests")
{
    SECTION("single item")
    {
        RedBlackTree<int> rdb;
        bool added = rdb.add(1);
        CHECK(added == true);

    }
    SECTION("add vector")
    {
        RedBlackTree<int> rdb;
        std::vector<int> v={1,2,3,4,5,6,7};
        std::vector<bool> vb = rdb.add(v);
        std::vector<bool> correct = {true,true,true,true,true,true,true};
        CHECK(vb == correct);
    }
    SECTION("add dublicate")
    {
        RedBlackTree<int> rdb;
        bool added = rdb.add(4);
        int temp = 4;
        bool notAdded = rdb.add(temp);
        CHECK(added!=notAdded);

    }
    SECTION("vector dublicates")
    {
        std::vector<int> v = {1,4,1,4};
        std::vector<bool> correct = {true,true,false,false};
        RedBlackTree<int> rdb;
        std::vector<bool> vb = rdb.add(v);
        CHECK(vb==correct);


    }

}

TEST_CASE("search functions tests")
{
    SECTION("search single item exists")
    {   RedBlackTree<int> rdb;
        rdb.add(4);
        CHECK(rdb.search(4)==true);
    }
    SECTION("search single item doesnt exist")
    {   RedBlackTree<int> rdb;
        rdb.add(4);
        CHECK(rdb.search(5)==false);
    }
    SECTION("search root null")
    {   RedBlackTree<int> rdb;
        CHECK(rdb.search(4)==false);
    }
    SECTION("search list of items exists")
    {   RedBlackTree<int> rdb;
        std::vector<int> v ={1,2,3,4,5};
        std::vector<bool> vb ={true,true,true,true,true};
        rdb.add(v);
        CHECK(rdb.search(v)==vb);
    }
    SECTION("search list of items  doesnt exist")
    {   RedBlackTree<int> rdb;
        std::vector<int> v ={1,2,3,4,5};
        std::vector<bool> vb ={true,true,false,true,false};
        std::vector<int> v1 ={1,2,6,4,8};
        rdb.add(v);
        CHECK(rdb.search(v1)==vb);
    }

}
TEST_CASE("rotations")
{
    SECTION("correct rotation")
    {
        std::vector<int> v = {1,4,3,2};
        RedBlackTree<int> rdb;
        rdb.add(v);
        std::vector<int> vb = {1,2,3,4};
        CHECK(rdb.check_element_order(vb));

    }
}
