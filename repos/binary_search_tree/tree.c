#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"

typedef struct pair
{
    Node* parent;
    Node* child;
}Pair;

static Node* MakeNode(const Item* pi);
static bool ToLeft(const Item* i1, const Item* i2);
static bool ToRight(const Item* i1, const Item* i2);
static void AddNode(Node* new_node, Node* root);
static void InOrder(const Node* root, void (* pfunc)(Item item));
static Pair SeekItem(const Item* pi, const Tree* ptree);
static void DeleteNode(Node** ptr);
static void DeleteAllNode(Node* ptr);


void InitializeTree(Tree* ptree)
{
    ptree->root = NULL;
    ptree->size = 0;
}

bool TreeIsEmpty(const Tree* ptree)
{
    return ptree->root == NULL;
}

bool TreeIsFull(const Tree* ptree)
{
    return ptree->size == MAXITEMS;
}

int TreeItemCount(const Tree* ptree)
{
    return ptree->size;
}

bool AddItem(const Item* pi, Tree* ptree)
{
    Node* new_node;
    if(TreeIsFull(ptree))
    {
        fprintf(stderr, "Tree is full\n");
        return false;
    }
    //if have a same item in tree, child attr is not null
    if (SeekItem(pi, ptree).child != NULL)
    {
        fprintf(stderr, "fail to add duplicate item\n");
        return false;
    }
    new_node = MakeNode(pi);
    //don't have enough memory to alloc
    if(!new_node)
    {
        fprintf(stderr, "couldn't create node\n");
        return false;
    }
    ptree->size++;
    if (ptree->root == NULL)
        ptree->root = new_node;
    else
        AddNode(new_node, ptree->root);
    return true;
}

bool InTree(const Item* pi, Tree* ptree)
{
    return (SeekItem(pi, ptree).child != NULL)? true : false;
}

bool DeleteItem(const Item* pi, Tree* ptree)
{
    Pair look;
    look = SeekItem(pi, ptree);
    if (look.child == NULL)
        return false;
    if (look.parent == NULL)
        DeleteNode(&ptree->root);
    else if (look.parent->left == look.child)
        DeleteNode(&look.parent->left);
    else
        DeleteNode(&look.parent->right);
    ptree->size--;
    return true;
}

void Traverse(const Tree* ptree, void (*pfun)(Item Item))
{
    if (ptree != NULL)
        InOrder(ptree->root, pfun);
}

void DeleteAll(Tree* ptree)
{
    if (ptree != NULL)
        DeleteAllNode(ptree->root);
    ptree->root = NULL;
    ptree->size = 0;
}

static Node* MakeNode(const Item* pi)
{
    Node * new_node;
    new_node = (Node *)malloc(sizeof(Node));
    if (new_node != NULL)
    {
        new_node->item = *pi;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}
// three ways:preorder traversal, inorder traversal and postorder traversal
// there is inorder traversal
static void InOrder(const Node* root, void (* pfunc)(Item item))
{
    if (root != NULL)
    {
        InOrder(root->left, pfunc);
        (*pfunc)(root->item);
        InOrder(root->right, pfunc);
    }
}

static void DeleteAllNode(Node* root)
{
    Node* pright;
    if (root != NULL)
    {
        pright = root->right;
        DeleteAllNode(root->left);
        free(root);
        DeleteAllNode(pright);
    }
}

static bool ToLeft(const Item* i1, const Item* i2)
{
    int cmp1;

    if (cmp1 = strcmp(i1->petname, i2->petname) < 0)
        return true;
    else  if (cmp1 == 0 && strcmp(i1->petkind, i2->petkind) < 0)
        return true;
    else
        return false;
}

static bool ToRight(const Item* i1, const Item* i2)
{
    int cmp1;
    if (cmp1 = strcmp(i1->petname, i2->petname) > 0)
        return true;
    else if (cmp1 == 0 && strcmp(i1->petkind, i2->petkind) > 0)
        return true;
    else
        return false;
}

static void AddNode(Node* new_node, Node* root)
{
    if (ToLeft(&new_node->item, &root->item))
    {
        if(root->left == NULL)
            root->left = new_node;
        else
            AddNode(new_node, root->left);
    }
    else if (ToRight(&new_node->item, &root->item))
    {
        if(root->right == NULL)
            root->right = new_node;
        else
            AddNode(new_node, root->right);
    }
    else
    {
        fprintf(stderr, "location error in AddNode()\n");
        exit(1);
    }
}

static Pair SeekItem(const Item* pi, const Tree* ptree)
{
   Pair look;
   look.parent = NULL;
   look.child = ptree->root;
   if (look.child == NULL)
       return look;
   while(look.child !=NULL)
   {
       if(ToLeft(pi, &(look.child->item)))
       {
           look.parent = look.child;
           look.child = look.child->left;
       }
       else if(ToRight(pi,&(look.child->item)))
       {
           look.parent = look.child;
           look.child = look.child->right;
       }
       else
           //find a item equal to *pi
           break;
   }
   return look;
}

static void DeleteNode(Node** ptr)
{
    Node* temp;
    puts((*ptr)->item.petname);
    if((*ptr)->left == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->right;
        free(temp);
    }
    else if ((*ptr)->right == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
    else
    {
        //put this right child tree(1) to the rightest of this left child tree(2),because 1 all gt 2. 
        for (temp = (*ptr)->left; temp->right !=NULL; temp = temp->right)
        continue;
        temp->right = (*ptr)->right;
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
}
