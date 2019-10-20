#include "redblack.h"

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
    parent = nullptr;
    color = RED;
}
template<typename T>
Node<T>::Node(T& element)
{
    this->element = element;
    right = nullptr;
    left = nullptr;
    parent = nullptr;
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
            check_tree(current->left);
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
            check_tree(current->right);
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
            check_tree(current->left);
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
            check_tree(current->right);
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
template <class T>
void RedBlackTree<T>::check_tree(Node<T> * current)
{
    current->colour = RED;
    while ( (current != root) && (current->parent->colour == RED) ) {
        if ( current->parent == current->parent->parent->left ) {
            /* If current's parent is a left, y is current's right 'uncle' */
            left(current);
        }
        else {
            /* repeat the "if" part with right and left
                  ecurrentchanged */
            right(current);
        }
    }
    /* Colour the root black */
    root->colour = BLACK;


}
template <class T>
void RedBlackTree<T>::left(Node<T>*&current)
{    Node<T> * temp;
     temp = current->parent->parent->right;
      if ( temp->colour == RED ) {
          /* case 1 - change the colours */
          current->parent->colour = BLACK;
          temp->colour = BLACK;
          current->parent->parent->colour = RED;
          /* Move current up the tree */
          current = current->parent->parent;
      }
      else {
          /* y is a black node */
          if ( current == current->parent->right ) {
              /* and current is to the right */
              /* case 2 - move current up and rotate */
              current = current->parent;
              left_rotate( current );
          }
          /* case 3 */
          current->parent->colour = BLACK;
          current->parent->parent->colour = RED;
          right_rotate(current->parent->parent );
      }

}
template <class T>
void RedBlackTree<T>::right(Node<T>*&current)
{
    Node<T> *temp;
    temp = current->parent->parent->left;
    if ( temp->colour == RED ) {
        /* case 1 - change the colours */
        current->parent->colour = BLACK;
        temp->colour = BLACK;
        current->parent->parent->colour = RED;
        /* Move current up the tree */
        current = current->parent->parent;
    }
    else {
        /* y is a black node */
        if ( current == current->parent->left ) {
            /* and current is to the left */
            /* case 2 - move current up and rotate */
            current = current->parent;
            right_rotate( current );
        }
        /* case 3 */
        current->parent->colour = BLACK;
        current->parent->parent->colour = RED;
        left_rotate(current->parent->parent );
    }
}
