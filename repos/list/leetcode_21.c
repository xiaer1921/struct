/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
//leetcode_21
typedef struct ListNode* ListPtr;
typedef struct ListNode ListNode;

void add(bool* tell, ListPtr* twoList, ListPtr* ll,ListPtr* result){
    if(*tell == false){
                *twoList = *ll;
                *result = *twoList;
                *tell = true;
                *ll = (*ll)->next;
                return ;
            }
    (*twoList)->next = *ll;
    *twoList = (*twoList)->next;
    *ll = (*ll)->next;
}

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    ListPtr twoList;
    ListPtr result;
    bool tell = false;
    if(l1 == NULL)
        return l2;
    if(l2 == NULL)
        return l1;
    while(l1 && l2){
        if(l1->val <= l2->val){
            add(&tell, &twoList, &l1, &result);
        }
        else{
            add(&tell, &twoList, &l2, &result);
        }
    }
    while(l1){
        add(&tell, &twoList, &l1, &result);
    }
    while(l2){
        add(&tell, &twoList, &l2, &result);
    }
    return result;
}
