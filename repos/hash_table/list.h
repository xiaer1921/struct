#ifndef LIST_H_
#define LIST_H_
#include<stdbool.h>
#define Tsize 45


typedef int Item;

typedef struct node
{
    Item item;
    struct node* next;
}Node;

typedef Node* List;

void Initializelist(List* plist);

bool ListIsEmpty(const List* plist);

bool ListIsFull(const List* plist);

unsigned int ListItemCount(const List* plist);

bool AddItem(Item item, List* plist);

void Traverse(const List* plist, void (* pfunc)(Item item));

void EmptyTheList(List* plist);

#endif
