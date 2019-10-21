#                            RedBlackTree
#### Red-Black-Tree is just a balanced search tree with every node in the tree has the data, left child, right child, and 		color.

## Properties 
- The root and NIL nodes are black.
- Children of red node are black.
- If a node is red, then its children are black.  
- All pathes from a node to its Nil descendants contain the same number of black nodes.

## Notes
- The longest path (root to farthest NIL) is no more than twice the length of the shortest path (root to the nearest NIL)
	- Shortest path: all black nodes
	- Longest path: alternative red-black 

## Operations
- Search   
- Deletion (require rotation)
- Insertion (require rotation)

## Time Complexity
- Search   O(log(n))
- Deletion O(log(n))
- Remove   O(log(n))

## Memory Complexity
- O(n)

## Applications 
- Java: java.util.TreeMap , java.util.TreeSet .
- C++ STL: map, multimap, multiset.
- Linux kernel: completely fair scheduler, linux/rbtree.h

## Resources
- 


