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
    Node * left;
    Node * right;
    Node * parent;
    T element;
    Color color;
    Node(T&&);
    Node(T&);
    Node();
};

template <typename T>
class RedBlackTree
{

private:
    bool add(T&& , Node<T>*);
    bool add(T& , Node<T>*);
    bool remove(T&&, Node<T>*);
    bool remove(T&, Node<T>*);
    bool search(T&&,Node<T>*);
    bool search(T&,Node<T>*);
    void right(Node<T>*&);
    void left(Node<T>*&);
    Node<T> *root;

    // Utility functions
    void left_rotate(Node<T>*);
    void right_rotate(Node<T>*);
    void min_node(Node<T>*);
    void check_tree(Node<T>*);
    void rb_transplant(Node<T>*, Node<T>*);
    void rb_remove_fixup(Node<T*>);
    void print(Node<T>*);

public:
    RedBlackTree();
    // Add
    template < template < class ... > class Container, class ... Args >
    std::vector<bool> add(const Container<T,Args...>&);

    bool add(T&&);
    bool add(T&);

    // Remove
    bool remove(T&&);
    bool remove(T&);

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

#include "redblack.inl"
#endif // REDBLACK_H
