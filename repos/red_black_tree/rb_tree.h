#ifndef _RBD_BLACK_TREE_H_
#define _RBD_BLACK_TREE_H_

#define RED 0 // red node
#define BLACK 1 // black node

typedef int Type;

typedef struct RBTreeNode
{
    unsigned char color;
    Type key;
    struct RBTreeNode* left;
    struct RBTreeNode* right;
    struct RBTreeNode* parent;
}Node, *RBTree;


typedef struct RBRoot{
    Node* node;
}RBRoot;

// return root of a red-black tree created
RBRoot* createRBTree();

void destroyRBTree(RBRoot* root);

//insert a node to red-black tree, return 0 if successful,return -1 if failed.
int insertRBTree(RBRoot* root, Type key);

void deleteRBTree(RBRoot* root, Type key);

void preorderRBTree(RBRoot* root);

void inorderRBTree(RBRoot* root);

void postorderRBTree(RBRoot* root);

int iterativeRBTreeSearch(RBRoot* root, Type key);

int rbTreeSearch(RBRoot* root, Type key);

//save the key of a maximum node to *val in tree if find
int rbTreeMinimum(RBRoot* root, int* val);

int rbTreeMaximum(RBRoot* root, int* val);

void printRBTree(RBRoot* root);

#endif
