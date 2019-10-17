#ifndef REDBLACK_H
#define REDBLACK_H
#include <initializer_list>
#include <vector>
#include <memory>
enum Color{RED,BLACK};
template <typename T>
struct Node
{
    Node * left;
    Node * right;
    T element;
    Color color;
    Node(T&&);
};

template <typename T>
class RedBlackTree
{
    Node<T> *root;

public:
    // Add
    //bool add(T&&);
    bool add(T&& , Node<T>* = nullptr);
    bool add(std::initializer_list<T> args);
    bool add(std::vector<T>);
    //variadic add

    // Remove
    bool remove(T&&);
    bool remove(T&&, Node<T>* current_pos);
    std::initializer_list<T> remove(std::initializer_list<T> args);
    std::vector<T> remove(std::vector<T>);

    // Search

    bool search(T&&);
    bool search(T&&,Node<T>* current_pos= nullptr);
    std::initializer_list<bool> search(std::initializer_list<T> args);
    std::vector<bool> search(std::vector<T>);
};




#endif // REDBLACK_H
