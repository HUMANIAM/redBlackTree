#                            RedBlackTree
##### Red-Black-Tree is just an approximately balanced binary search tree with every node in the tree has the data, left child, right child, and color.

### Properties 
- The root and NIL nodes are black.
- Children of red node are black.
- If a node is red, then its children are black.  
- All pathes from a node to its Nil descendants contain the same number of black nodes (height-black property).

### Used operations in rebalancing
- Rotation (doesn't break the BST property)
- Recoloring (doesn't affect the structure of the tree)

### Notes
- The longest path (root to farthest NIL) is no more than twice the length of the shortest path (root to the nearest NIL)
	- Shortest path: all black nodes
	- Longest path: alternative red-black 

## Operations
- Search   
- Deletion (require rotation and recoloring)
- Insertion (require rotation and recoloring)

## Time Complexity
- Search   O(log(n))
- Deletion O(log(n))
- Remove   O(log(n))

### Memory Complexity
- O(n)

### Applications 
- Java: java.util.TreeMap , java.util.TreeSet .
- C++ STL: map, multimap, multiset.
- Linux kernel: completely fair scheduler, linux/rbtree.h

### Test Benchmark against STL-SET C++
**comparing our implementation of redblack tree against the set data structure that is implemented internally using red-black tree and here are the results**

![benchMark test](http://arwash.rdi:5050/Misc/redblacktree/raw/master/Screenshot%20from%202019-10-24%2016-47-49.png)

## Resources
- Introduction to algorithms (CLRS book) (chapter-13 red-black tree)
- https://www.youtube.com/watch?v=hm2GHwyKF1o


