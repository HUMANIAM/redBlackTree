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

//template <typename T>
//bool RedBlackTree<T>::add(T&& element)
//{
//    return add(element,root);
//}

template <typename T>
bool RedBlackTree<T>::add(T&& element ,Node<T> * current)
{
    if(current==nullptr)
    {current = new Node<T>(std::forward<T>(element));
        if(root==current)
            current->color = BLACK;
        return true;
    }
    if(current->element==element)
    {
        return true;
    }

    if(current->element > element)
        add(std::forward<T>(element),current->left);
    else
        add(std::forward<T>(element),current->right);

    // Preform Recoloring and Rotation

}
