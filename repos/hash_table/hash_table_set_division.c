/*
slove collision via list or set and dividing a bigger prime.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include "list.h"

const int primes[] = {3, 7, 11, 17, 23, 29, 37, 47, 59, 71, 89, 107, 131, 163, 197, 239, 293, 353, 431, 521, 631, 761, 919, 1103, 1327, 1597, 1931, 2333, 2801, 3371, 4049, 4861, 5839, 7013, 8419, 10103, 12143, 14591, 17519, 21023, 25229, 30293, 36353, 43627, 52361, 62851, 75431, 90523, 108631, 130363, 156437,187751, 225307, 270371, 324449, 389357, 467237, 560689, 672827, 807403, 968897, 1162687, 1395263, 1674319, 2009191, 2411033, 2893249, 3471899, 4166287, 4999559, 5999471, 7199369};

typedef struct SingleIntSet
{
    List* plist;
    int size;
}Set;

void init(Set *s, int size)
{
    s->plist = (List*)malloc(sizeof(List) * size);
    s->size = size;
    List* begin = s->plist;
    while(begin < s->plist+size)
    {
        Initializelist(begin);
        begin++;
    }
}

bool isPrime(int candidate)
{
    if ((candidate & 1) != 0)
    {
        int limit = (int)sqrt(candidate);
        for(int divisor = 3; divisor <= limit; divisor += 2)
        {
            if((candidate % divisor) == 0)
                return false;
        }
        return true;
    }
    return (candidate == 2);
}

int getPrime(int min)
{
    for(int i=0; i<(sizeof(primes)/sizeof(primes[0])); i++)
    {
        int prime = primes[i];
        if(prime >= min)
            return prime;
    }

    for(int i = (min | 1); i < INT_MAX; i++)
    {
        if(isPrime(i))
            return i;
    }
    return min;
}

int hash(int h, const Set* s)
{
    return h % (s->size);
}

void add(int item, const Set* s)
{
    AddItem(item, (s->plist) + hash(item, s));
}

int maxItem(const int *a, int len)
{
    int max = -1;
    for (int i = 0; i < len; i++)
        if(a[i] > max)
            max = a[i];
    return max;
}

bool find(int item, const Set* s)
{
    List* plist = (s->plist) + hash(item, s);
    Node* cur = *plist;
    while(cur)
    {
        if(cur->item == item)
            return true;
    }
    return false;
}

int main()
{
    Set s;
    Item a[]={3,13,23,33};

    init(&s, getPrime(maxItem(a, 4)));
    for(int i = 0; i < 4; i++)
        add(a[i], &s);
    for(int i = 0; i < 4; i++)
        printf("%d \n",find(a[i], &s));
    return 0;
}
