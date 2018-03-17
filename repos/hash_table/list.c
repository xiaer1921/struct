#include<stdio.h>
#include<stdlib.h>
#include "list.h"

static void CopyToNode(Item item, Node* pnode);

void Initializelist(List* plist)
{
    *plist = NULL;
}

bool ListIsEmpty(const List* plist)
{
    if(*plist)
        return false;
    else
        return true;
}

bool ListIsFull(const List* plist)
{
    Node* pt;
    bool full;
    pt = (Node *)malloc(sizeof(Node));
    if (pt)
        full = false;
    else
        full = true;
    free(pt);
    return full;
}

unsigned int ListItemCount(const List* plist)
{
    unsigned int num=0;
    Node* cur=*plist;
    while(cur)
    {
        num++;
        cur = cur->next;
    }
    return num;
}

bool AddItem(Item item, List* plist)
{
    Node* pt;
    pt = (Node*)malloc(sizeof(Node));
    if (!pt)
        return false;
    Node* cur = *plist;
    CopyToNode(item, pt);
    pt->next = NULL;
    if (!cur)
        *plist = pt;
    else
    {
        //pt->next = cur->next;
        //plist = pt;
        while(cur->next)
            cur = cur->next;
        cur->next = pt;
    }
    return true;
}

void Traverse(const List* plist, void (* pfunc)(Item item))
{
    Node* cur = *plist;
    while(cur)
    {
        (*pfunc)(cur->item);
        cur = cur->next;
    }
}

void EmptyTheList(List* plist)
{
    Node* next;
    while(*plist)
    {
        next = (*plist)->next;
        free(*plist);
        *plist = next;
    }
}

static void CopyToNode(Item item, Node* pnode)
{
    pnode->item  = item;
}
