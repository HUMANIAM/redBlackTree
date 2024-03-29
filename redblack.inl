#include "redblack.h"
#include <string.h>


// initialize init functions
template<typename T>
RedBlackTree<T>::RedBlackTree()
{
	root=nullptr;
}

template<typename T>
Node<T>::Node()
{

}

template<typename T>
Node<T>::Node(T&& element)
{
	this->element = element;
}

template<typename T>
Node<T>::Node(T& element)
{
	this->element = element;
}

template <typename T>
bool RedBlackTree<T>::is_empty()
{
	return root == nullptr;
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
		return false;
	}

	else if(current->element > element)
	{
		if(current->left==nullptr)
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
		return false;
	}

	else if(current->element > element)
	{
		if(current->left==nullptr)
		{
			current->left = new Node<T>(std::forward<T>(element));
			current->left->parent = current;
			// Check and preform recoloring and rotation
			check_tree(current->left);
			return true;
		}
		else{
			return add(std::forward<T>(element),current->left);
		}

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
	return (search_util(std::move(element), root) != nullptr);
}

template <typename T>
bool RedBlackTree<T>::search(T& element)
{
	T temp = element;
	return (search_util(std::move(temp), root) != nullptr);
}


// search for element in rbTree and if found return pointer to it else return null pointer
template<typename T>
Node<T>* RedBlackTree<T>::search_util(T&& element, Node<T>* current)
{
	if(current==nullptr)
	{
		return nullptr;
	}

	if(current->element == element)
	{
		return current;

	}else if(current->element > element)
	{
		return search_util(std::move(element),current->left);

	}else
	{
		return search_util(std::move(element),current->right);
	}

}

template <class T>
template < template < class ... > class Container, class ... Args >
std::vector<bool> RedBlackTree<T>::search(const Container<T,Args...>& list)
{
	std::vector<bool> search_results;
	for(T element : list)
	{
		search_results.push_back(search_util(std::move(element), root));
	}
	return search_results;
}


template <class T>
void RedBlackTree<T>::check_tree(Node<T> * current)
{
	insert_case1(current);

}
template <class T>
void RedBlackTree<T>::insert_case1(Node<T>* n)
{
	if (n->parent == NULL)
		n->color = BLACK;
	else
		insert_case2(n);
}
template <class T>
Color RedBlackTree<T>::node_color(Node<T>* n)
{
	return n == NULL ? BLACK : n->color;
}


template <class T>
void RedBlackTree<T>::insert_case2(Node<T>* n)
{
	if (node_color(n->parent) == BLACK)
		return;
	else
		insert_case3(n);
}
template <class T>
void RedBlackTree<T>::insert_case3(Node<T>* n)
{
	if (node_color(uncle(n)) == RED)
	{
		n->parent->color = BLACK;
		uncle(n)->color = BLACK;
		grandparent(n)->color = RED;
		insert_case1(grandparent(n));
	}
	else
	{
		insert_case4(n);
	}
}
template <class T>
void RedBlackTree<T>::insert_case4(Node<T>*n)
{
	if (n == n->parent->right && n->parent == grandparent(n)->left)
	{
		rotate_left( n->parent);
		n = n->left;
	}
	else if (n == n->parent->left && n->parent == grandparent(n)->right)
	{
		rotate_right(n->parent);
		n = n->right;
	}
	insert_case5(n);
}

template <class T>
void RedBlackTree<T>::insert_case5(Node<T>* n)
{
	n->parent->color = BLACK;
	grandparent(n)->color = RED;
	if (n == n->parent->left && n->parent == grandparent(n)->left)
	{
		rotate_right(grandparent(n));
	}
	else
	{
		if(n == n->parent->right && n->parent == grandparent(n)->right)
			rotate_left(grandparent(n));
	}
}


template <class T>
void RedBlackTree<T>::rotate_left(Node<T>* n)
{
	Node<T>* r = n->right;
	replace_node(n, r);
	n->right = r->left;
	if (r->left != NULL)
	{
		r->left->parent = n;
	}
	r->left = n;
	n->parent = r;
}



template<class T>
void RedBlackTree<T>::rotate_right(Node<T>* n)
{
	Node<T>* L = n->left;
	replace_node(n, L);
	n->left = L->right;
	if (L->right != NULL)
	{
		L->right->parent = n;
	}
	L->right = n;
	n->parent = L;
}

template  <class T>
void RedBlackTree<T>::replace_node(Node<T>* oldn,Node<T>* newn)
{
	if (oldn->parent == NULL)
	{
		root = newn;
	}
	else
	{
		if (oldn == oldn->parent->left)
			oldn->parent->left = newn;
		else
			oldn->parent->right = newn;
	}
	if (newn != NULL)
	{
		newn->parent = oldn->parent;
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
	{
		return;
	}
	print(current->left);
	std::string color = current->color==0?"RED":"Black";
	std::cout<<"element : "<<current->element<<"  color: "<<color<<std::endl;
	print(current->right);

}



/////////////////////////////////////////////// Remove Node From RBTree  ///////////////////

template <typename T>
void RedBlackTree<T>::remove(T&& element)
{
	Node<T>* node_addr = search_util(std::move(element), root);

	// the node doesn't exist in the rbTree
	if(node_addr == nullptr)
	{
		return;
	}

	// remove the node
	remove_util(node_addr);
}

template <typename T>
void RedBlackTree<T>::remove(T& element)
{
	T t = element;
	remove(std::move(t));
}

template <typename T>
template < template < class ... > class Container, class ... Args >
void RedBlackTree<T>::remove(const Container<T,Args...>& container)
{
	for(T element : container) {
		remove(std::move(element));
	}
}

template<typename T>
void RedBlackTree<T>::remove_util(Node<T>* node_d)
{
	// temp will replace the node_d and temp_x will replace temp node
	Node<T>* temp = node_d;
	Node<T>* temp_x = nullptr;

	// for x is nullptr
	Color temp_color = temp->color;
	bool node_x_null = false;

	if(!haschild(node_d))
	{
		bool root_n = root == node_d;
		delete_leave(node_d, temp_x, node_x_null);
		if(root_n){
			return;
		}

	}else
	{
		bool temp_has_children = true;
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
			temp_color = temp->color;
			temp_x = temp->right;
			temp_has_children = haschild(temp);

			// if temp is the smallest node in the right subtree of node_d and also child to it.
			if(!temp_has_children && temp_color == BLACK)
			{
				node_d->element = temp->element;
				temp_x = temp;
				temp_x->color = BLACK;
				node_x_null = true;

			}else if(temp_x != nullptr && temp->parent == node_d)
			{
				temp_x->parent = temp;

			}else
			{
				rb_transplant(temp, temp_x);

				// make the right of node_d also right to node temp
				temp->right = node_d->right;
				if(temp->right != nullptr)
				{
					temp->right->parent = temp;
				}

			}
			if(temp_has_children || temp_color == RED)
			{
				rb_transplant(node_d, temp);
				temp->left = node_d->left;
				temp->left->parent = temp;
				temp->color = node_d->color;
			}

			if(temp_has_children)
				delete node_d;
		}
	}

	// check properties of rbTree aren't broken
	if(temp_color == BLACK)
	{
		rb_remove_fixup(temp_x, node_x_null);
	}
}

///////////////////// Fix RBTree properties after deletion /////////////////
template <typename T>
void RedBlackTree<T>::rb_remove_fixup(Node<T>* node_x, bool delete_x)
{
	Node<T>* node_x_t = node_x;
	while(node_x != root && node_x->color == BLACK)
	{

		if(node_x == node_x->parent->left)
		{
			rb_remove_fixup_left(node_x);
		}else
		{
			rb_remove_fixup_right(node_x);
		}
	}

	node_x->color = BLACK;

	// if node_x is dummy node delete
	if(delete_x)
	{
		delete_dummy(node_x_t);
	}
}

/////////// Fix the height black of node located in the left hand side of the parent ///
template <class T>
Node<T>* RedBlackTree<T>::remove_fixup_left_case1(Node<T>* sibling_w, Node<T>* node_x)
{
	sibling_w->color = BLACK;
	node_x->parent->color = RED;
	rotate_left(node_x->parent);
	return node_x->parent->right;
}


template <class T>
Node<T>* RedBlackTree<T>::remove_fixup_left_case2(Node<T>* sibling_w, Node<T>* node_x)
{
	sibling_w->color = RED;
	return  node_x->parent;
}


template <class T>
Node<T>* RedBlackTree<T>::remove_fixup_left_case3(Node<T>* sibling_w, Node<T>* node_x)
{
	if(sibling_w->left != nullptr)
	{
		sibling_w->left->color = BLACK;
	}

	sibling_w->color = RED;
	rotate_right(sibling_w);

	return node_x->parent->right;
}


template <class T>
Node<T>* RedBlackTree<T>::remove_fixup_left_case4(Node<T>* sibling_w, Node<T>* node_x)
{
	sibling_w->color = node_x->parent->color;

	node_x->parent->color = BLACK;
	if(sibling_w->right != nullptr)
	{
		sibling_w->right->color = BLACK;
	}

	rotate_left(node_x->parent);
	return root;
}

template <typename T>
void RedBlackTree<T>::rb_remove_fixup_left(Node<T>*& node_x)
{
	/*Deal with NIL Nodes as they aren't exist but they can break your condition.
	 **/

	// sibiling of node_x is always exist where node_x is doubly black
	Node<T>* sibling_w = node_x->parent->right;

	if(sibling_w->color == RED)
	{
		// case 1
		sibling_w = remove_fixup_left_case1(sibling_w, node_x);
	}

	// children of w_sibling has black color
	bool w_left_black  = (sibling_w->left  == nullptr) || (sibling_w->left->color == BLACK);
	bool w_right_black = (sibling_w->right == nullptr) || (sibling_w->right->color == BLACK);
	if(w_left_black && w_right_black)
	{
		// case 2
		node_x = remove_fixup_left_case2(sibling_w, node_x);

	}else if(w_right_black)
	{
		// case 3
		sibling_w = remove_fixup_left_case3(sibling_w, node_x);

	}else
	{
		// case 4
		node_x = remove_fixup_left_case4(sibling_w, node_x);
	}
}

/////////// Fix the height black of node located in the right hand side of the parent ///
template <class T>
Node<T>* RedBlackTree<T>::remove_fixup_right_case1(Node<T>* sibling_w, Node<T>* node_x)
{
	sibling_w->color = BLACK;
	node_x->parent->color = RED;
	rotate_right(node_x->parent);
	return node_x->parent->left;
}


template <class T>
Node<T>* RedBlackTree<T>::remove_fixup_right_case2(Node<T>* sibling_w, Node<T>* node_x)
{
	sibling_w->color = RED;
	return  node_x->parent;
}


template <class T>
Node<T>* RedBlackTree<T>::remove_fixup_right_case3(Node<T>* sibling_w, Node<T>* node_x)
{
	if(sibling_w->right != nullptr)
	{
		sibling_w->right->color = BLACK;
	}

	sibling_w->color = RED;
	rotate_left(sibling_w);

	return node_x->parent->left;
}


template <class T>
Node<T>* RedBlackTree<T>::remove_fixup_right_case4(Node<T>* sibling_w, Node<T>* node_x)
{
	sibling_w->color = node_x->parent->color;

	node_x->parent->color = BLACK;
	if(sibling_w->left != nullptr)
	{
		sibling_w->left->color = BLACK;
	}

	rotate_right(node_x->parent);
	return root;
}

template <typename T>
void RedBlackTree<T>::rb_remove_fixup_right(Node<T>*& node_x)
{
	/*Deal with NIL Nodes as they aren't exist but they can break your condition.
	 **/

	// sibiling of node_x is always exist where node_x is doubly black
	Node<T>* sibling_w = node_x->parent->left;

	if(sibling_w->color == RED)
	{
		// case 1
		sibling_w = remove_fixup_right_case1(sibling_w, node_x);
	}

	// children of w_sibling has black color
	bool w_left_black  = (sibling_w->left  == nullptr) || (sibling_w->left->color == BLACK);
	bool w_right_black = (sibling_w->right == nullptr) || (sibling_w->right->color == BLACK);
	if(w_left_black && w_right_black)
	{
		// case 2
		node_x = remove_fixup_right_case2(sibling_w, node_x);

	}else if(w_left_black)
	{
		// case 3
		sibling_w = remove_fixup_right_case3(sibling_w, node_x);

	}else
	{
		// case 4
		node_x = remove_fixup_right_case4(sibling_w, node_x);
	}
}


/////////////////////// Utility Functions  //////////////////////////////////////////
template <typename T>
bool RedBlackTree<T>::haschild(Node<T>* node)
{
	return (node->left != nullptr) || (node->right != nullptr);
}

template <typename T>
void RedBlackTree<T>::delete_dummy(Node<T>* node)
{
	if(node == node->parent->left)
	{
		node->parent->left = nullptr;

	}else
	{
		node->parent->right = nullptr;
	}

	delete node;
}

// make bridge between u parent node and v node
template <typename T>
void RedBlackTree<T>::rb_transplant(Node<T>* u, Node<T>* v)
{
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
Node<T>* RedBlackTree<T>::min_node(Node<T>* node)
{
	return (node->left == nullptr)? node : min_node(node->left);
}

template <typename T>
void RedBlackTree<T>::delete_leave(Node<T>*& node_d, Node<T>*& temp_x, bool& node_x_null)
{
	if(node_d == root)
	{
		delete node_d;
		root = nullptr;
		return;
	}

	// keep the node_d if it is black to used in fixing the tree height black
	// else delete it.
	if(node_d->color == BLACK)
	{
		temp_x = node_d;
		node_x_null = true;
	}else
	{
		delete_dummy(node_d);
	}
}

// elements are in_order traverse
template <class T>
bool RedBlackTree<T>::check_element_order(std::vector<T> v)
{
	std::vector<T> elements;
	get_elements(root,elements);
	if(v.size()!=elements.size())
		return false;

	for(unsigned int i = 0;i<v.size();i++)
	{
		if(v[i]!=elements[i])
			return false;
	}
	return true;
}


template <class T>
void RedBlackTree<T>::get_elements(Node<T> *ptr,std::vector<T>& v)
{
	if(ptr == nullptr)
		return;
	v.push_back(ptr->element);
	get_elements(ptr->left,v);
	get_elements(ptr->right,v);
}

template <class T>
RedBlackTree<T>::~RedBlackTree<T>()
{   clean_tree(root);
	root = nullptr;
}

template <class T>
void RedBlackTree<T>::clean_tree(Node<T>*node)
{
	if(node==nullptr)
		return;
	clean_tree(node->left);
	clean_tree(node->right);
	node->left = nullptr;
	node->right = nullptr;
	node->parent = nullptr;
	delete node;

}

// test functions
template <class T>
bool RedBlackTree<T>::root_black()
{
	return (root == nullptr) || (root->color == BLACK);
}

template <class T>
bool RedBlackTree<T>::two_adjacent_red()
{
	return two_adjacent_red(root);
}

template <class T>
bool RedBlackTree<T>::height_black()
{
	return height_black(root).second;
}

template <class T>
bool RedBlackTree<T>::two_adjacent_red(Node<T>* current)
{
	if(current == nullptr)
	{
		return false;
	}

	bool left_red = (current->left != nullptr && current->left->color == RED);
	if((current->color == RED) && left_red)
	{
		return true;
	}

	bool right_red = (current->right != nullptr && current->right->color == RED);
	if((current->color == RED) && right_red){ return true; }


	return  two_adjacent_red(current->right) || two_adjacent_red(current->left);
}

template <class T>
std::pair<int,bool> RedBlackTree<T>::height_black(Node<T>*node)
{
	if(node==nullptr)
	{
		return std::make_pair(0,true);
	}
	std::pair<int,bool> left = height_black(node->left);
	if(!left.second)
		return std::make_pair(-1,false);
	std::pair<int,bool> right = height_black(node->right);
	if(!right.second)
		return std::make_pair(-1,false);
	if(right.first == left.first)
	{
		if(node->color==BLACK)
			return std::make_pair(left.first+1,true);
		return std::make_pair(left.first,true);
	}
	return std::make_pair(-1,false);

}

template <class T>
Node<T>* RedBlackTree<T>::grandparent(Node<T>* n)
{
	if(n!=NULL && n->parent!=NULL &&n->parent->parent!=NULL)
		return n->parent->parent;
	return NULL;
}

template<class T>
Node<T>* RedBlackTree<T>::sibling(Node<T>* n)
{
	if (n!=NULL && n->parent!=NULL && n == n->parent->left)
		return n->parent->right;
	else if(n!=NULL && n->parent!=NULL)
		return n->parent->left;

	return NULL;

}
template <class T>
Node<T>* RedBlackTree<T>::uncle(Node<T>* n)
{
	if(n!=NULL && n->parent!=NULL && n->parent->parent!=NULL)
		return sibling(n->parent);
	return NULL;
}








