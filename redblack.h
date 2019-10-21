#ifndef REDBLACK_H
#define REDBLACK_H
#include <initializer_list>
#include <vector>
#include <memory>
#include <iostream>
#include <utility>
/////////////////////////////
template <typename T>
void f(T xx, T* x = nullptr);

template <typename T>
void ff(const T&){
    std::cout << "hello" << std::endl;
}

/////////////////////////////
enum Color{RED,BLACK};
template <typename T>
struct Node
{
    Node * left;
    Node * right;
    Node * parent;
    T element;
    Color color;
    Node(T&&);
    Node(T&);
};

template <typename T>
class RedBlackTree
{

private:
    static Node<T> *root;
    bool add(T&& , Node<T>*);
    bool add(T& , Node<T>*);
    //bool search(T&&,Node<T>*);    // unnecessary
    //bool se, Node<T>* = nullptrarch(T&,Node<T>*);     // unnecessery
    void right(Node<T>*);
    void left(Node<T>*);
    Node<T>* search_util(T&&, Node<T>* = root);

    // Utility functions
    void left_rotate(Node<T>*);
    void right_rotate(Node<T>*);
    Node<T>* min_node(Node<T>*);
    void add_fixup(Node<T>*);

    void rb_transplant(Node<T>*, Node<T>*);
    void rb_remove_fixup(Node<T>*);
    void remove_util(Node<T>*);
    void print(Node<T>*);

public:
    RedBlackTree();
    // Add
    template < template < class ... > class Container, class ... Args >
    std::vector<bool> add(const Container<T,Args...>&);

    bool add(T&&);
    bool add(T&);

    // Remove
    void remove(T&&);
    void remove(T&);

    template < template < class ... > class Container, class ... Args >
    std::vector<bool> remove(Container<T,Args ...>);

    // Search
    bool search(T&&);
    bool search(T&);

    template < template < class ... > class Container, class ... Args >
    std::vector<bool> search(const Container<T,Args...>&);

    //print the red black tree in ascending order
    void print();
};


// utilities functins
template <typename T>
void create_NIL();
#include "redblack.inl"
#endif // REDBLACK_H
