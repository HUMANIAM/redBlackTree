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
    T element;
    Color color;
    Node(T&&);
    Node(T&);
};

template <typename T>
class RedBlackTree
{private:
    bool add(T&& , Node<T>*);
    bool add(T& , Node<T>*);
    bool remove(T&&, Node<T>*);
    bool remove(T&, Node<T>*);
    bool search(T&&,Node<T>*);
    bool search(T&,Node<T>*);
    Node<T> *root;

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

};
template<typename T>
RedBlackTree<T>::RedBlackTree()
{
    root=nullptr;
}

template<typename T>
Node<T>::Node(T&& element)
{
    this->element = element;
    right = nullptr;
    left = nullptr;
    color = RED;
}
template<typename T>
Node<T>::Node(T& element)
{
    this->element = element;
    right = nullptr;
    left = nullptr;
    color = RED;
}

template <typename T>
bool RedBlackTree<T>::add(T&& element)
{
    if(root==nullptr)
    {   root = new Node<T>(std::forward<T>(element));
        root->color = BLACK;
        return true;
    }
    return add(std::forward<T>(element),root);
}
template <typename T>
bool RedBlackTree<T>::add(T& element)
{   if(root==nullptr)
    {   root = new Node<T>(std::forward<T>(element));
        root->color = BLACK;
        return true;
    }
    return add(std::forward<T>(element),root);
}
template <typename T>
bool RedBlackTree<T>::add(T& element ,Node<T> * current)
{
    if(current->element==element)
    {
        return true;
    }

    else if(current->element > element)
    {   if(current->left==nullptr)
        {
            current->left = new Node<T>(std::forward<T>(element));
            // Check and preform recoloring and rotation
            return true;
        }
        else
            return add(std::forward<T>(element),current->left);
    }
    else
    {
        if(current->right==nullptr)
        {
            current->right = new Node<T>(std::forward<T>(element));
            // Check and preform recoloring and rotation
            return true;
        }
        else
            return add(std::forward<T>(element),current->right);
    }


}

template <typename T>
bool RedBlackTree<T>::add(T&& element ,Node<T> * current)
{
    if(current->element==element)
    {
        return true;
    }

    else if(current->element > element)
    {   if(current->left==nullptr)
        {
            current->left = new Node<T>(std::forward<T>(element));
            // Check and preform recoloring and rotation
            return true;
        }
        else
            return add(std::forward<T>(element),current->left);
    }
    else
    {
        if(current->right==nullptr)
        {
            current->right = new Node<T>(std::forward<T>(element));
            // Check and preform recoloring and rotation
            return true;
        }
        else
            return add(std::forward<T>(element),current->right);
    }


}

template <class T>
template < template < class ... > class Container, class ... Args >
std::vector<bool> RedBlackTree<T>::add(const Container<T,Args...>& list)
{
    std::vector<bool> search_results;
    for(T element : list)
    {
        search_results.push_back(add(std::move(element)));
    }
    return search_results;
}

template <typename T>
bool RedBlackTree<T>::search(T&& element)
{
    return search(std::move(element),root);
}

template <typename T>
bool RedBlackTree<T>::search(T& element)
{
    return search(std::move(element),root);
}

template <typename T>
bool RedBlackTree<T>::search(T&& element,Node<T>* current)
{
    if(current==nullptr)
        return false;

    if(current->element==element)
        return true;

    else if(current->element>element)
        return search(std::move(element),current->left);

    else
        return search(std::move(element),current->right);
}

template <typename T>
bool RedBlackTree<T>::search(T& element,Node<T>* current)
{
    if(current==nullptr)
        return false;

    if(current->element==element)
        return true;

    else if(current->element>element)
        return search(std::move(element),current->left);

    else
        return search(std::move(element),current->right);
}

template <class T>
template < template < class ... > class Container, class ... Args >
std::vector<bool> RedBlackTree<T>::search(const Container<T,Args...>& list)
{   std::vector<bool> search_results;
    for(T element : list)
    {
        search_results.push_back(search(std::move(element)));
    }
    return search_results;
}

#endif // REDBLACK_H
