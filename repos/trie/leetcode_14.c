//Longest Common Prefix
//trie leetcode_14

typedef struct Node{
    struct Node* child[26];
    int count;
} Node;

Node* init(){
    Node* root = (Node*)malloc(sizeof(Node));
    root->count = 0;
    for(int i = 0; i < 26; i++)
        root->child[i] = NULL;
    return root;
}

Node* new_child(){
    Node* child = init();
    child->count = 1;
    return child; 
}

void insert_node(Node* root, char* a){
    int num;
    
    Node* p =root;
    int len = strlen(a);
    for(int i = 0; i< len; i++){
        num = (a[i] - 'a');

        if(! p->child[num] ){
          struct Node* child = new_child();
            p->child[num] = child;
        }
        else
        {
          (p->child[num]->count)++;
        }
        p = p->child[num];
    }
}

char* find_longest(int strsSize, Node* root){
    Node* cur = root;
    char* result = (char*)malloc(1000000);
    int k = 0,i,biaoji=0;
    bool ifLongest = false;
    while(!ifLongest){
        for(i = 0; i < 26; i++){
            if(cur->child[i] == NULL)
                continue;
            if(cur->child[i]->count != strsSize){
                biaoji = 1;
                break;
            }
              result[k++] = 'a' + i;
              cur = cur->child[i];
            break;
        }
        if(i == 26 || biaoji == 1)
            ifLongest = true;
    }
    if(strlen(result) == 0)
        return "";
    return result;
}

char* longestCommonPrefix(char** strs, int strsSize) {
    if(strsSize == 0)
        return "";
    if(strsSize == 1)
        return strs[0];
    for(int i = 0; i< strsSize; i++){
        if(strlen(strs[i]) == 0)
            return "";
    }
    
    Node* root = init();
    for(int i = 0; i < strsSize; i++){
        insert_node(root, strs[i]);
    }
    char *p = find_longest(strsSize, root);
    return p;
}
