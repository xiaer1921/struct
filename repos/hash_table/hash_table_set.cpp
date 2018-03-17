/*
slove collision via list or set.
*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<set>
using namespace std;
class SingleIntSet
{
    private:
        set<int> s[10];

        int Hash(int value)
        {
            if(value >= 0 && value <= 9)
                return value;
            else
                return value - 10;
            //return value % 10;  division hash method
        }
    public:
        void Add(int item)
        {
            s[Hash(item)].insert(item);
        }
        bool Find(int item)
        {
            return s[Hash(item)].end() == s[Hash(item)].find(item)? false: true;
        }
        void Remove(int item)
        {
            s[Hash(item)].erase(item);
        }
};

int main()
{
    SingleIntSet values;
    values.Add(5);
    printf("%d \n", values.Find(5));
    values.Remove(5);
    printf("%d \n", values.Find(5));
    values.Add(6);
    values.Add(16);
    printf("%d \n", values.Find(6));
    printf("%d \n", values.Find(16));
    return 0;
}
