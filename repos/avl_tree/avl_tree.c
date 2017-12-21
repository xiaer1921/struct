#include<stdio.h>
#include<stdlib.h>
#include "avl_tree.h"

#define HEIGHT(p) ( (p == NULL) ? -0 : (((Node* )(p))->height) )
#define MAX(a, b) ( (a) > (b) ? (a) : (b) )


int getAVLTreeHeight(AVLTree tree)
{
    return HEIGHT(tree);
}


void preorderAVLTree(AVLTree tree)
{
    if (tree != NULL)
    {
        printf("%d ", tree->key);
        preorderAVLTree(tree->left);
        preorderAVLTree(tree->right);
    }
}


void inorderAVLTree(AVLTree tree)
{
    if (tree != NULL)
    {
        inorderAVLTree(tree->left);
        printf("%d ", tree->key);
        inorderAVLTree(tree->right);
    }
}


void postorderAVLTree(AVLTree tree)
{
    if (tree != NULL)
    {
        postorderAVLTree(tree->left);
        postorderAVLTree(tree->right);
        printf("%d ", tree->key);
    }
}


//search a node with "key"
Node* avlTreeSearch(AVLTree x, Type key)
{
    if ( x == NULL || x->key == key)
        return x;
    if (key < x->key)
        return avlTreeSearch(x->left, key);
    else
        return avlTreeSearch(x->right, key);
}


//search a node with "key" via an iterative way
Node* iterativeAVLTreeSearch(AVLTree x, Type key)
{
    while ((x != NULL) && (x->key != key))
    {
        if(key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}


//get the node with a minimum key in avl tree
Node* avlTreeMinimum(AVLTree tree)
{
    if(tree == NULL)
        return NULL;
    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}


//get the node with a maximum key in avl tree
Node* avlTreeMaximum(AVLTree tree)
{
    if(tree == NULL)
        return NULL;
    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}


//return the root node after LL rotation
static Node* leftLeftRotation(AVLTree k2)
{
    AVLTree k1;
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = MAX( HEIGHT(k2->left), HEIGHT(k2->right)) + 1;
    k1->height = MAX( HEIGHT(k1->left), HEIGHT(k1->right)) + 1;
    return k1;
}


//return the root node after RR rotation
static Node* rightRightRotation(AVLTree k2)
{
    AVLTree k1;
    k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    k2->height = MAX( HEIGHT(k2->left), HEIGHT(k2->right)) + 1;
    k1->height = MAX( HEIGHT(k1->left), HEIGHT(k1->right)) + 1;
    return k1;
}


//return the root node after LR rotation
static Node* leftRightlRotation(AVLTree k3)
{
    k3->left = rightRightRotation(k3->left);
    return leftLeftRotation(k3);
}


//return the root node after RR rotation
static Node* rightLeftRotation(AVLTree k3)
{
    k3->right = leftLeftRotation(k3->right);
    return rightRightRotation(k3);
}


//create a avl node
static Node* avlTreeCreateNode(Type key, Node* left, Node* right)
{
    Node* p;

    if ((p = (Node* )malloc(sizeof(Node))) == NULL)
        return NULL;
    p->key = key;
    p->height = 0;
    p->left = left;
    p->right = right;
    return p;
}


//insert a node to avl tree and return root node
Node* avlTreeInsert(AVLTree tree, Type key)
{
    if(tree == NULL)
    {
        tree = avlTreeCreateNode(key, NULL, NULL);
        if (tree == NULL)
        {
            fprintf(stderr, "fail to create a avltree node\n");
            return NULL;
        }
    }
    else if (key < tree->key) // should insert this node with key to leftchild of tree
    {
        tree->left = avlTreeInsert(tree->left, key);
        //after inserting,adjust this tree if tree is imbalance
        if(HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
        {
            if (key < tree->left->key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightlRotation(tree);
        }
    }
    else if (key > tree->key)
    {
        tree->right = avlTreeInsert(tree->right, key);
        if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree =  rightLeftRotation(tree);
        }
    }
    else
    {
        fprintf(stderr, "fail to add a node with a same key");
        return NULL;
    }
    tree->height = MAX( HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
    return tree;
}


//delete a node and return root node of this tree.
static Node* deleteNode(AVLTree tree, Node* z)
{
    if (tree == NULL || z == NULL)
        return NULL;
    printf("de %d \n", tree->key);
    if (z->key < tree->key)
    {
        tree->left = deleteNode(tree->left, z);
        if( HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
        {
            Node* r = tree->right;
            if ( HEIGHT(r->left) > HEIGHT(r->right))
                tree = rightLeftRotation(tree);
            else
                tree = rightRightRotation(tree);
        }
    }
    else if (z->key > tree->key)
    {
        tree->right = deleteNode(tree->right, z);
        if( HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
        {
            Node* l = tree->left;
            if (HEIGHT(l->right) > HEIGHT(l->left))
                tree = leftRightlRotation(tree);
            else
                tree = leftLeftRotation(tree);
        }
    }
    else
    {
        if ( (tree->left) && (tree->right))
        {
            if( HEIGHT(tree->left) > HEIGHT(tree->right))
            {
                //replace tree with a max node of leftchild and delete this max node
                //after delete this max node, the tree still is balance
                Node* max = avlTreeMaximum(tree->left);
                tree->key = max->key;
                tree->left = deleteNode(tree->left, max);
            }
            else
            {
                Node* min = avlTreeMinimum(tree->right);
                tree->key = min->key;
                tree->left = deleteNode(tree->right, min);
            }
        }
        else
        {
            Node* tmp =  tree;
            tree = tree->left ? tree->left: tree->right;
            free(tmp);
        }
    }
    if (tree != NULL)
    {
        tree->height = MAX( HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
    }
    return tree;
}


Node* avlTreeDelete(AVLTree tree, Type key)
{
    Node* z;

    if( (z = avlTreeSearch(tree, key)) != NULL)
        tree = deleteNode(tree, z);
    return tree;
}


void destroyAVLTree(AVLTree tree)
{
    if(tree == NULL)
        return ;
    if (tree->left != NULL)
        destroyAVLTree(tree->left);
    if (tree->right != NULL)
        destroyAVLTree(tree->right);

    free(tree);
}

void printAVLTree(AVLTree tree, Type key, int direction)
{
    if(tree != NULL)
    {
        if(direction == 0)
            printf("%2d is root\n", tree->key);
        else
            printf("%2d is %2d's %6s child\n", tree->key, key, direction == 1 ? "right" : "left" );
        printAVLTree(tree->left, tree->key, -1);
        printAVLTree(tree->right, tree->key, 1);
    }
}
