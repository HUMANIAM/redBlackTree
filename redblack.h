#ifndef REDBLACK_H
#define REDBLACK_H
#include <initializer_list>
#include <vector>
#include <memory>
#include <iostream>
#include <utility>

enum Color{RED,BLACK};
template <typename T>
struct Node
{
    T element;
    Color color = RED;
    Node * left = nullptr;
    Node * right = nullptr;
    Node * parent = nullptr;
    Node();
    Node(T&&);
    Node(T&);
};

template <typename T>
class RedBlackTree
{

private:
    Node<T> *root;
    int size_rb = 0;
    bool add(T&& , Node<T>*);
    bool add(T& , Node<T>*);
    void right(Node<T>*);
    void left(Node<T>*);
    Node<T>* search_util(T&&, Node<T>*);

    // Utility functions
    void left_rotate(Node<T>*);
    void right_rotate(Node<T>*);
    Node<T>* min_node(Node<T>*);
    void check_tree(Node<T>*);

    //**** Fuctions used when fix the tree after deletion ****///
    void remove_util(Node<T>*);
    void rb_remove_fixup(Node<T>*, bool);

    // when the node x located in the left of the parent
    void rb_remove_fixup_left(Node<T>*&);
    Node<T>* remove_fixup_left_case1(Node<T>*, Node<T>*);
    Node<T>* remove_fixup_left_case2(Node<T>*, Node<T>*);
    Node<T>* remove_fixup_left_case3(Node<T>*, Node<T>*);
    Node<T>* remove_fixup_left_case4(Node<T>*, Node<T>*);

    // when the node x located in the left of the parent
    void rb_remove_fixup_right(Node<T>*&);
    Node<T>* remove_fixup_right_case1(Node<T>*, Node<T>*);
    Node<T>* remove_fixup_right_case2(Node<T>*, Node<T>*);
    Node<T>* remove_fixup_right_case3(Node<T>*, Node<T>*);
    Node<T>* remove_fixup_right_case4(Node<T>*, Node<T>*);

    // Utility Functions
    bool haschild(Node<T>*);
    void delete_dummy(Node<T>*);
    void rb_transplant(Node<T>*, Node<T>*);
    void delete_leave(Node<T>*&, Node<T>*&, bool&);
    void print(Node<T>*);

public:
    RedBlackTree();
    // Add
    bool add(T&&);
    bool add(T&);
    template < template < class ... > class Container, class ... Args >
    std::vector<bool> add(const Container<T,Args...>&);

    // Remove
    void remove(T&&);
    void remove(T&);
    template < template < class ... > class Container, class ... Args >
    void remove(const Container<T,Args...>&);

    // Search
    bool search(T&&);
    bool search(T&);
    template < template < class ... > class Container, class ... Args >
    std::vector<bool> search(const Container<T,Args...>&);

    //print the red black tree in ascending order
    void print();

    int size_rbt();

    bool check_element_order(std::vector<T>);
    void get_elements(Node<T>*,std::vector<T>&);
    void clean_tree(Node<T>*);

};


// utilities functins
template <typename T>
void create_NIL();
#include "redblack.inl"
#endif // REDBLACK_H
