#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
void print(Item item)
{
    printf("%d ",item);
}

int main()
{
    List list;
    printf("This is 0\n");
    Initializelist(&list);
    printf("This is 1\n");
    Item k1 =1, k2 = 2, k3 = 3;
    AddItem(k1, &list);
    AddItem(k2, &list);
    AddItem(k3, &list);
    printf("This is 2\n");
    bool b = ListIsFull(&list);
    bool b1 = ListIsEmpty(&list);
    printf("%d \n", b);
    printf("%d \n", b1);

    printf("%d \n", ListItemCount(&list));
    Traverse(&list, print);
    
    return 0;
}
