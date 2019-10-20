#include "redblack.h"

template<typename T>
RedBlackTree<T>::RedBlackTree()
{
    root=nullptr;
}
template<typename  T>
Node<T>::Node()
{
    right = nullptr;
    left = nullptr;
    element = 0;
    color = BLACK;
}
template<typename T>
Node<T>::Node(T&& element)
{
    this->element = element;
    right = new Node();
    left = new Node();
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
            current->left->parent = current;
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
            current->right->parent = current;
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
            current->left->parent = current;
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
            current->right->parent = current;
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
{   std::cout<<"check tree start"<<std::endl;
    while ( (current != root) && (current->parent->color == RED) ) {
        if ( current->parent == current->parent->parent->left ) {
            /* If current's parent is a left, temp is current's right 'uncle' */
            left(current);
        }
        else {
            /* repeat the "if" part with right and left
                  ecurrentchanged */
            right(current);
        }
    }
    /* color the root black */
    root->color = BLACK;
    std::cout<<"check tree end"<<std::endl;


}
template <class T>
void RedBlackTree<T>::left(Node<T>*&current)
{   std::cout<<"start left"<<std::endl;
    Node<T> * temp;
    temp = current->parent->parent->right;
    if (temp->color == RED ) {
        /* case 1 - change the colors */
        current->parent->color = BLACK;
        temp->color = BLACK;
        current->parent->parent->color = RED;
        /* Move current up the tree */
        current = current->parent->parent;
        return;
    }
    else {
        /* temp is a black node */
        if ( current == current->parent->right ) {
            /* and current is to the right */
            /* case 2 - move current up and rotate */
            current = current->parent;
            left_rotate( current );
            return;
        }

        /* case 3 */
        current->parent->color = BLACK;
        current->parent->parent->color = RED;
        right_rotate(current->parent->parent );
    }
    std::cout<<"end right"<<std::endl;
}
template <class T>
void RedBlackTree<T>::right(Node<T>*&current)
{   std::cout<<"start right"<<std::endl;
    Node<T> *temp;
    temp = current->parent->parent->left;
    if ( temp->color == RED ) {
        /* case 1 - change the colors */
        current->parent->color = BLACK;
        temp->color = BLACK;
        current->parent->parent->color = RED;
        /* Move current up the tree */
        current = current->parent->parent;
    }
    else {
        /* temp is a black node */
        if ( current == current->parent->left ) {
            /* and current is to the left */
            /* case 2 - move current up and rotate */
            current = current->parent;
            right_rotate( current );
        }
        /* case 3 */
        current->parent->color = BLACK;
        current->parent->parent->color = RED;
        left_rotate(current->parent->parent);
    }
    std::cout<<"end right"<<std::endl;
}

template <class T>
void RedBlackTree<T>::print()
{
    print(root);
}
template <class T>
void RedBlackTree<T>::print(Node<T>*current)
{
    if(current==nullptr)
    { return;
    }
    print(current->left);
    if(current->element!=0)
    std::cout<<"element : "<<current->element<<std::endl;
    print(current->right);

}
template <class T>
void RedBlackTree<T>::left_rotate(Node<T> *current ) {
    Node<T> *temp;
    temp = current->right;
    /* Turn temp's left sub-tree into x's right sub-tree */
    current->right = temp->left;
    if ( temp->left != nullptr )
        temp->left->parent = current;
    /* temp's new parent was x's parent */
    temp->parent = current->parent;
    /* Set the parent to point to temp instead of x */
    /* First see whether we're at the root */
    if ( current->parent == nullptr ) root = temp;
    else
        if ( current == (current->parent)->left )
            /* x was on the left of its parent */
            current->parent->left = temp;
        else
            /* x must have been on the right */
            current->parent->right = temp;
    /* Finalltemp, put x on temp's left */
    temp->left = current;
    current->parent = temp;
    std::cout<<"left rotate"<<std::endl;
}

template <class T>
void RedBlackTree<T>::right_rotate(Node<T> *current ) {
    Node<T> *temp;
    temp = current->right;
    /* Turn temp's left sub-tree into x's right sub-tree */
    current->right = temp->left;
    if ( temp->left != nullptr )
        temp->left->parent = current;
    /* temp's new parent was x's parent */
    temp->parent = current->parent;
    /* Set the parent to point to temp instead of x */
    /* First see whether we're at the root */
    if ( current->parent == nullptr ) root = temp;
    else
        if ( current == (current->parent)->left )
            /* x was on the left of its parent */
            current->parent->left = temp;
        else
            /* x must have been on the right */
            current->parent->right = temp;
    /* Finalltemp, put x on temp's left */
    temp->left = current;
    current->parent = temp;
    std::cout<<"right rotate"<<std::endl;
}

