#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef int Type;

typedef struct AVLTreeNode
{
    Type key;
    int height;
    struct AVLTreeNode* left;
    struct AVLTreeNode* right;
}Node, *AVLTree;

int getAVLTreeHeight(AVLTree tree);

void preorderAVLTree(AVLTree tree);

void inorderAVLTree(AVLTree tree);

void postorderAVLTree(AVLTree tree);

void printAVLTree(AVLTree tree, Type key, int direction);

//search a node with "key" in avl tree
Node* avlTreeSearch(AVLTree x, Type key);

//search a node with "key" via an iterative way in avl tree
Node* iterativeAVLTreeSearch(AVLTree x, Type key);

//search a node with minimum key
Node* avlTreeMinimum(AVLTree tree);

//search a node with maximum key
Node* avlTreeMaximum(AVLTree tree);

//insert a node to the avl tree
Node* avlTreeInsert(AVLTree tree, Type key);

//delete a node with key in avl tree, return null if tree
//is null or not find a node with the key
Node* avlTreeDelete(AVLTree tree, Type key);

//delete a avl tree
void destroyAVLTree(AVLTree tree);

#endif
