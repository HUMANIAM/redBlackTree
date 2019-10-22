#include "redblack.h"
#include <string.h>

///////////////////////
//////////////////////////

// initialize init functions
template <typename T>
Node<T>* RedBlackTree<T>::root = nullptr;

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
            current->left->parent = current;
            // Check and preform recoloring and rotation
            add_fixup(current->left);
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
            add_fixup(current->right);
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
            add_fixup(current->left);
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
            add_fixup(current->right);
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
        print();
    }
    return search_results;
}

template <typename T>
bool RedBlackTree<T>::search(T&& element)
{
    return (search_util(std::move(element)) != nullptr);
}

template <typename T>
bool RedBlackTree<T>::search(T& element)
{
    T temp = element;
    return (search_util(std::move(temp)) != nullptr);
}


// search for element in rbTree and if found return pointer to it else return null pointer
template<typename T>
Node<T>* RedBlackTree<T>::search_util(T&& element, Node<T>* current){
    if(current==nullptr){
        return nullptr;
    }

    if(current->element == element)
    {
        return current;

    }else if(current->element > element)
    {
        return search_util(std::move(element),current->left);

    }else{
        return search_util(std::move(element),current->right);
    }

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
void RedBlackTree<T>::add_fixup(Node<T> * current)
{
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

}


template <class T>
void RedBlackTree<T>::left(Node<T>*current)
{
    Node<T> * temp;
    temp = current->parent->parent->right;

    if (temp!=nullptr && temp->color == RED ) {
        /* case 1 - change the colors */
        current->parent->color = BLACK;
        temp->color = BLACK;
        current->parent->parent->color = RED;
        /* Move current up the tree */
        current = current->parent->parent;
    }
    else {
        /* temp is a black node */
        if ( current == current->parent->right ) {
            /* and current is to the right */
            /* case 2 - move current up and rotate */
            current = current->parent;
            left_rotate( current );
        }

        /* case 3 */
        current->parent->color = BLACK;
        current->parent->parent->color = RED;
        right_rotate(current->parent->parent );
    }

}


template <class T>
void RedBlackTree<T>::right(Node<T>*current)
{
    Node<T> *temp;
    temp = current->parent->parent->left;

    if (temp!=nullptr && temp->color == RED ) {
        /* case 1 - change the colors */
        std::cout<<"case 1"<<std::endl;
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
}


template <class T>
void RedBlackTree<T>::print()
{
    print(root);
    std::cout<<std::endl<<std::endl;
}

template <class T>
void RedBlackTree<T>::print(Node<T>*current)
{
    if(current==nullptr)
    { return;
    }
    print(current->left);
   std::string color = current->color==0?"RED":"Black";
   std::cout<<"element : "<<current->element<<"  color: "<<color<<std::endl;
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
        if ( current == current->parent->left )
            /* x was on the left of its parent */
            current->parent->left = temp;
        else
            /* x must have been on the right */
            current->parent->right = temp;
    /* Finalltemp, put x on temp's left */
    temp->left = current;
    current->parent = temp;
}

template <class T>
void RedBlackTree<T>::right_rotate(Node<T> *current ) {
    Node<T> *temp;
    temp = current->left;
    /* Turn temp's right sub-tree into x's left sub-tree */
    current->left = temp->right;
    if ( temp->right != nullptr )
        temp->right->parent = current;
    /* temp's new parent was x's parent */
    temp->parent = current->parent;
    /* Set the parent to point to temp instead of x */
    /* First see whether we're at the root */
    if ( current->parent == nullptr ) root = temp;
    else
        if ( current == current->parent->right )
            /* x was on the right of its parent */
            current->parent->right = temp;
        else
            /* x must have been on the right */
            current->parent->left = temp;
    /* Finally, put x on temp's right */
    temp->right = current;
   current->parent = temp;
    std::cout<<"right rotate"<<std::endl;
}

/////////////////////////////////////////////// Remove node ///////////////////
using namespace std;
template<typename T>
void RedBlackTree<T>::remove_util(Node<T>* node_d){
    // temp will replace the node_d and temp_x will replace temp node
    //cout << "delete : " << node_d->element << " with parent " << node_d->parent->element << endl;
    Node<T>* temp = node_d;
    Node<T>* temp_x = nullptr;

    // for x is nullptr
    Node<T>* temp_parent = node_d->parent;
    Color temp_color = temp->color;

    if(node_d->left == nullptr)
    {
        temp_x = node_d->right;
        rb_transplant(node_d, node_d->right);

    }else if(node_d->right == nullptr)
    {
        temp_x = node_d->left;
        rb_transplant(node_d, node_d->left);
    }else
    {
        // find the minimum node in the lhs of the node_d
        temp = min_node(node_d->right);
        //keep some information about temp node
        temp_parent = temp->parent;
        temp_color = temp->color;
        temp_x = temp->right;

        // if temp is the smallest node in the right subtree of node_d and also child to it.
        if(temp_x != nullptr && temp->parent == node_d){
            temp_x->parent = temp;
        }else
        {
            rb_transplant(temp, temp_x);

            // make the right of node_d also right to node temp
            temp->right = node_d->right;
            if(temp->right != nullptr){
                temp->right->parent = temp;
            }
        }

        rb_transplant(node_d, temp);
        temp->left = node_d->left;
        temp->left->parent = temp;
        temp->color = node_d->color;
    }

    // delete node_d
    delete node_d;

    // check properties of rbTree aren't broken
    if(temp_color == BLACK){
        bool node_x_null = false;

        // create dummy node for temp_right
        if(root != nullptr && temp_x == nullptr){
            temp_x = new Node<T>(-1);
            temp_x->color = BLACK;
            temp_x->parent = temp_parent;
            temp_parent->left = temp_x;
            node_x_null = true;
        }

        rb_remove_fixup(temp_x, node_x_null);
    }

}


template <typename T>
void RedBlackTree<T>::remove(T&& element){
    Node<T>* node_addr = search_util(std::move(element));

    // the node doesn't exist in the rbTree
    if(node_addr == nullptr){
        return;
    }

    // remove the node
    remove_util(node_addr);
}

template <typename T>
void RedBlackTree<T>::remove(T& element){
    T t = element;
    remove(std::move(t));
}


// delete u and replace it with v
template <typename T>
void RedBlackTree<T>::rb_transplant(Node<T>* u, Node<T>* v){
    // We don't delete the node we just transplant it.
    if(u == root)
    {
        root = v;
    }else if (u == u->parent->left)
    {
        u->parent->left = v;
    }else
    {
        u->parent->right = v;
    }

    if(v != nullptr)
    {
        v->parent = u->parent;
    }
}


template <typename T>
void RedBlackTree<T>::rb_remove_fixup(Node<T>* node_x, bool delete_x){
    while(node_x != root && node_x->color == BLACK){

       if(node_x == node_x->parent->left){
           rb_remove_fixup_left(node_x);
       }else
       {
           rb_remove_fixup_right(node_x);
       }
    }

     node_x->color = BLACK;

    // if node_x is dummy node delete
    if(delete_x){
        if(node_x == node_x->parent->left){node_x->parent->left = nullptr;}
        else{node_x->parent->right == nullptr;}
        delete node_x;
    }
}

template <typename T>
Node<T>* RedBlackTree<T>::min_node(Node<T>* node){
    return (node->left == nullptr)? node : min_node(node->left);
}


/* Fix remove **/
template <class T>
void RedBlackTree<T>::remove_fixup_case1(Node<T>* sibling_w, Node<T>* node_x){
    sibling_w->color = BLACK;
    node_x->parent->color = RED;
    left_rotate(node_x->parent);
    sibling_w = node_x->parent->right;
}


template <class T>
Node<T>* RedBlackTree<T>::remove_fixup_case2(Node<T>* sibling_w, Node<T>* node_x){
    sibling_w->color = RED;
    return  node_x->parent;
}


template <class T>
Node<T>* RedBlackTree<T>::remove_fixup_case3(Node<T>* sibling_w, Node<T>* node_x){
    if(sibling_w->left != nullptr){
        sibling_w->left->color = BLACK;
    }

    sibling_w->color = RED;
    right_rotate(sibling_w);

    return node_x->parent->right;
}


template <class T>
Node<T>* RedBlackTree<T>::remove_fixup_case4(Node<T>* sibling_w, Node<T>* node_x){
    sibling_w->color = node_x->parent->color;

    node_x->parent->color = RED;
    if(sibling_w->right != nullptr){
        sibling_w->right->color = BLACK;
    }

    left_rotate(node_x->parent);
    return root;
}



template <typename T>
void RedBlackTree<T>::rb_remove_fixup_left(Node<T>*& node_x){
    /*Deal with NIL Nodes as they aren't exist so they must break your condition. if the condition
     * based on them. say a condition based on the children is black and the children were null that
     * break the condition.
     * */

    // sibiling of node_x is always exist where node_x is doubly black
    Node<T>* sibling_w = node_x->parent->right;

    if(sibling_w != nullptr && sibling_w->color == RED){
        // case 1
        remove_fixup_case1(sibling_w, node_x);
    }

    // children of w_sibling must be not null and has black color
    bool w_left_black  = (sibling_w->left != nullptr) && (sibling_w->left->color == BLACK);
    bool w_right_black = (sibling_w->right != nullptr) && (sibling_w->right->color == BLACK);
    if(w_left_black && w_right_black){
        // case 2
        node_x = remove_fixup_case2(sibling_w, node_x);

    }else if((sibling_w->right != nullptr) && (sibling_w->right->color == BLACK)){
       // case 3
        sibling_w = remove_fixup_case3(sibling_w, node_x);

    }else{
        // case 4
        node_x = remove_fixup_case4(sibling_w, node_x);
    }
}


template <typename T>
void RedBlackTree<T>::rb_remove_fixup_right(Node<T>* node_x){

}
