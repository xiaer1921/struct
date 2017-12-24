#include<stdio.h>
#include<stdlib.h>
#include "rb_tree.h"

#define rb_parent(r) ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r) ((r)->color == RED)
#define rb_is_black(r) ((r)->color == BLACK)
#define rb_set_red(r) do { (r)->color = RED ;} while(0)
#define rb_set_black(r) do { (r)->color = BLACK ; } while(0)
#define rb_set_parent(r,p) do { (r)->parent = (p); } while(0)
#define rb_set_color(r,c) do { (r)->color = (c); } while(0)

RBRoot* createRBTree()
{
    RBRoot* root = (RBRoot*)malloc(sizeof(RBRoot));
    root->node = NULL;
    return root;
}

static void preorder(RBTree tree)
{
    if(tree != NULL)
    {
        printf("%d ", tree->key);
        preorder(tree->left);
        preorder(tree->right);
    }
}

void preorderRBTree(RBRoot* root)
{
    if(root != NULL)
        preorder(root->node);
}

static void inorder(RBTree tree)
{
    if(tree != NULL)
    {
        inorder(tree->left);
        printf("%d ", tree->key);
        inorder(tree->right);
    }
}

void inorderRBTree(RBRoot* root)
{
    if (root != NULL)
        inorder(root->node);
}

static void postorder(RBTree tree)
{
    if(tree != NULL)
    {
        postorder(tree->left);
        postorder(tree->right);
        printf("%d ", tree->key);
    }
}

void postorderRBTree(RBRoot* root)
{
    if (root != NULL)
        postorder(root->node);
}

static Node* search(RBTree x, Type key)
{
    if (x == NULL || x->key == key)
        return x;
    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}

int rbTreeSearch(RBRoot* root, Type key)
{
    if(root != NULL)
        return search(root->node, key)? 0 : -1;
}

static Node* iterative_search(RBTree x, Type key)
{
    while( (x != NULL) && (x->key != key))
    {
        if( key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

int iterativeRBTreeSearch(RBRoot* root, Type key)
{
    if (root != NULL)
        return iterative_search(root->node, key)? 0: -1;
}

//search a minimum node in the tree
static Node* minimum(RBTree tree)
{
    if (tree == NULL)
        return NULL;
    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

int rbTreeMinimum(RBRoot* root, int* val)
{
    Node* node;
    if (root)
        node = minimum(root->node);
    if (node == NULL)
        return -1;
    *val = node->key;
    return 0;
}

static Node* maximum(RBTree tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

int rbTreeMaximum(RBRoot* root, int* val)
{
    Node* node;
    if (root != NULL)
        node = maximum(root->node);
    if(node == NULL)
        return -1;

    *val = node->key;
    return 0;
}

//find a successor node of x. successor node is a node what is minimum node in some node gt x node.
static Node* rbTreeSuccessor(RBTree x)
{
    if (x->right != NULL)
        return minimum(x->right);
    Node* y = x->parent;
    //if x don't have a right node, so there are two possibility.
    //1> if x is a left child, his successor node is his father node.
    //2> if x is a right child, his successor node is his the lowest father node with a lefe child node.
    while( (y != NULL) && (x == y->right ))
    {
        x = y;
        y = y->parent;
    }

    return y;
}

//fina a presuccessor node of x. successor node is a node what is maximum node in some node lt x node.
static Node* rbTreePreSuccessor(RBTree x)
{
    if (x->left != NULL)
        return maximum(x->left);
    Node* y = x->parent;
    //if x don't have a left child,so there are two possibility.
    //1> if x is a right child, his presuccessor node is his father node.
    //2> if x is a left child, his presuccessor node is his the lowest father node with a right child node.
    while( (y != NULL) && (x == y->left))
    {
        x = y;
        y = y->parent;
    }

    return y;
}

/*
left rotate to a red-black tree.
 like the following. aim at x node.
            px            py
            /             / 
           x              y
          / \            / \
         lx  y           x  ry
            / \         / \
            ly ry      lx ly
*/
static void rbTreeLeftRotate(RBRoot* root, Node* x)
{
    Node* y = x->right;
    x->right = y->left;

    if ( y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root->node = y;
    else
    {
        if(x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

// it is same like left rotate
static void rbTreeRightRotate(RBRoot* root, Node* y)
{
    Node* x = y->left;

    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if(y->parent == NULL)
        root->node = x;
    else
    {
        if (y->parent->right == y)
            y->parent->right = x;
        else
            y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

//insert-fix function 
//1>if parent node' color is black,including this node's height is 2,it don't to fix
//2>if parent node's color is red,it break out the rule that(if parent is red,so it's child is both black)
static void rbTreeInsertFixup(RBRoot* root, Node* node)
{
    Node *parent, *gparent;
    //1>node's height isn't 2,because it's parent is root,root's color is black
    //2>node's height isn't 1,because it's parent is NULL.
    while((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);
        
        // if father node is the leftchild of gparent.
        if(parent == gparent->left)
        {
            //case 1: uncle node's color is red
            {
                Node* uncle = gparent->right;
                if(uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }
            
            //case 2: uncle is a black node, and fix node is right node. case 2 will change to case 3.
            if (parent->right == node)
            {
                Node* tmp;
                rbTreeLeftRotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            //case 3: uncle is black, and fix node is left node.
            rb_set_black(parent);
            rb_set_red(gparent);
            rbTreeRightRotate(root, gparent);
        }
        // if father node is the right node of gparent.
        else
        {
            //case 1:uncle is a red node.
            {
                Node* uncle = gparent->left;
                if( uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            //case 2:uncle is a black node, and fix node is a left child.
            if (parent->left == node)
            {
                Node* tmp;
                rbTreeRightRotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            //case 3: uncle is black node, and fix node is right child.
            rb_set_black(parent);
            rb_set_red(gparent);
            rbTreeLeftRotate(root, gparent);
        }
    }

    //set root node to black
    rb_set_black(root->node);
}


static void rbTreeInsert(RBRoot* root, Node* node)
{
    Node* y = NULL;
    Node* x = root->node;

    while (x != NULL)
    {
        y = x;
        if( node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    rb_parent(node) = y;
    
    node->color = RED;
    if( y != NULL)
    {
        if( node->key < y->key)
            y->left = node;
        else
            y->right = node;
    }
    else
    {
        root->node = node;
        //if tree is NULL,node will is black after insertfix-function.
        //node->color = BLACK; this can skip,because it work in insertfix-function
    }

    //set a new node's color to red
    rbTreeInsertFixup(root, node);
}

static Node* createRBTreeNode(Type key, Node* parent, Node* left, Node* right)
{
    Node* p;
    if ((p = (Node*)malloc(sizeof(Node))) == NULL)
        return NULL;
    p->key = key;
    p->left = left;
    p->right = right;
    p->parent = parent;
    p->color = BLACK;

    return p;
}

int insertRBTree(RBRoot* root, Type key)
{
    Node* node;

    if (search(root->node, key) != NULL)
        return -1;
    if((node = createRBTreeNode(key, NULL, NULL, NULL)) == NULL)
        return -1;

    rbTreeInsert(root, node);

    return 0;
}

static void rbTreeDeleteFixup(RBRoot* root, Node* node, Node* parent)
{
    Node* other;
    while ((!node || rb_is_black(node)) && node != root->node)
    {
        if(parent->left == node)
        {
            other = parent->right;
            //other pointer must is't null 
            if(rb_is_red(other))
            {
                //case 1: x's brother is red
                rb_set_black(other);
                rb_set_red(parent);
                rbTreeLeftRotate(root, parent);
                other = parent->right;
            }
            
            if ((!other->left || rb_is_black(other->left)) && (!other->right || rb_is_black(other->right)))
            {
                //case2: x's brother (w)is black, and w's two child is black.
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if(!other->right || rb_is_black(other->right))
                {
                    //case 3: x's brother (w)is black, and w's leftchild is red, rightchild is black.
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rbTreeRightRotate(root, other);
                    other = parent->right;
                }
                //case4: x's brother is black, and w's rightchild is red, leftchild is red or black.
                rb_set_color(other, rb_color(parent)); 
                rb_set_black(parent);
                rb_set_black(other->right);
                rbTreeLeftRotate(root, parent);
                node = root->node;
                break;
            }
        }
        else
        {
            other = parent->left;
            if(rb_is_red(other))
            {
                //case1: x's brother is red
                rb_set_black(other);
                rb_set_red(parent);
                rbTreeRightRotate(root, parent);
                other = parent->left;
            }
            if((!other->left || rb_is_black(other->left)) && (!other->right || rb_is_black(other->right)))
            {
                //case2: x's brother(w) is black, and w's two child is both black.
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if(!other->left || rb_is_black(other->left))
                {
                    //case3: x's brother(w) is black, and w's leftchild is red, rightchild is black.
                    rb_set_black(other->right);
                    rb_set_red(other);
                    rbTreeLeftRotate(root, other);
                    other = parent->left;
                }

                //case4: x's brother (w)is black, and w's rightchild is red, leftchild is red or black.
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->left);
                rbTreeRightRotate(root, parent);
                node = root->node;
                break;
            }
        }
    }
    if(node)
        rb_set_black(node);
}


void rbTreeDelete(RBRoot* root, Node* node)
{
    Node *child, *parent;
    int color;

    // case1: the two child is't all NULL
    if ( (node->left != NULL) && (node->right != NULL) )
    {
        Node* replace = node;

        //the replace-node will replace the delete-node,and then delete the replace node.
        //get the successor node.
        replace = replace->right;
        while( replace->left !=  NULL)
            replace = replace->left;

        if(rb_parent(node))
        {
            if(rb_parent(node)->left == node)
                rb_parent(node)->left = replace;
            else
                rb_parent(node)->right = replace;
        }
        else
            root->node = replace;

        //child node is the replace-node's right child, and a node needs to adjust.
        //replace node don't have a leftchild, and it is a successor node.
        child = replace->right;
        parent = rb_parent(replace);

        // save the replace-node'color
        color = rb_color(replace);

        // the delete-node is his successor node's father
        if(parent == node)
            parent = replace;
        else
            {
                if(child)
                    rb_set_parent(child, replace);
                parent->left = child;

                replace->right = node->right;
                rb_set_parent(node->right,replace);
            }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if(color == BLACK)
            rbTreeDeleteFixup(root, child, parent);
        free(node);

        return ;
    }
    if(node->left != NULL)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;

    // save the replace-node's color.
    color = node->color;

    if(child)
        child->parent = parent;

    if(parent)
    {
        if(parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root->node = child;

    if(color == BLACK)
        rbTreeDeleteFixup(root, child, parent);
    free(node);
}

void deleteRBTree(RBRoot* root, Type key)
{
    Node *z, *node;
    if((z=search(root->node, key)) != NULL)
        rbTreeDelete(root, z);
}

static void rbTreeDestroy(RBTree tree)
{
    if(tree == NULL)
        return ;
    if(tree->left != NULL)
        rbTreeDestroy(tree->left);
    if(tree->right != NULL)
        rbTreeDestroy(tree->right);

    free(tree);
}

void destroyRBTree(RBRoot* root)
{
    if(root != NULL)
        rbTreeDestroy(root->node);

    free(root);
}

static void rbTreePrint(RBTree tree, Type key, int direction)
{
    if(tree != NULL)
    {
        if(direction == 0)
            printf("%2d (black) is root\n", tree->key);
        else
            printf("%2d (%s) is %2d's %6s child\n",tree->key, rb_is_red(tree)? "red": "black", key, direction == 1? "right": "left");

        rbTreePrint(tree->left, tree->key, -1);
        rbTreePrint(tree->right, tree->key, 1);
    }
}

void printRBTree(RBRoot* root)
{
    if(root != NULL && root->node != NULL)
        rbTreePrint(root->node, root->node->key, 0);
}
