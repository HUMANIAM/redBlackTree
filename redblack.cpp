#include "redblack.h"
#include <iostream>
#include <utility>
#include <memory>
template<typename T>
Node<T>::Node(T&& element)
{
    this->element = element;
    right = nullptr;
    left = nullptr;
    color = RED;
}

template <typename T>
bool RedBlackTree<T>::add(T&& element)
{       if(root==nullptr)
    {   root = new Node<T>(std::forward<T>(element));
        root->color = BLACK;
        return true;
    }
    return add(std::forward<T>(element),root);
}

template <typename T>
bool RedBlackTree<T>::add(T&& element ,Node<T> * current)
{
    if(current->element==element)
    {
        return true;
    }

    if(current->element > element)
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
