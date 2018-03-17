#stack
#leetcode_20
typedef struct Node{
    char x;
    struct Node* next;
}Node;

typedef struct Stack{
    Node* head;
    Node* tail;
    bool empty;
}Stack;

Stack* init(){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->head = NULL;
    stack->tail = NULL;
    stack->empty = true;
    return stack;
}

void push(Stack* stack, char x){
    Node* node = (Node*)malloc(sizeof(Node));
    node->x = x;
    node->next = NULL;
    if(stack->empty == true){
        stack->empty = false;
        stack->head = node;
        stack->tail = node;
    }
    else{
        stack->tail->next = node;
        stack->tail = node;
    }
}

void pop(Stack* stack)
{
    if(stack->empty == true)
        return ;
    Node* cur = stack->head;
    Node* nextPtr;
    if(!cur->next){
        stack->empty = true;
        stack->head = NULL;
        stack->tail = NULL;
        free(cur);
    }
    else{
        nextPtr = cur->next;
        while(nextPtr->next){
            cur = nextPtr;
            nextPtr = nextPtr->next;
        }
        stack->tail = cur;
        cur->next = NULL;
        free(nextPtr);
    }
}

char gettail(Stack* stack)
{
    return stack->tail->x;
}

bool isValid(char* s) {
    Stack* stack = init();
    int len =  strlen(s);
    for(int i = 0; i < len; i++){
        if(s[i] == '(' || s[i] == '{' || s[i] == '[')
            push(stack, s[i]);
        switch(s[i]){
            case ')':
                if(stack->tail && stack->tail->x == '(')
                    pop(stack);
                else
                    return 0;
                break;
            case '}':
                if(stack->tail && stack->tail->x == '{')
                    pop(stack);
                else
                    return 0;
                break;
            case ']':
                if(stack->tail && stack->tail->x == '[')
                    pop(stack);
                else
                    return 0;
                break;
        }
    }
    if(stack->empty == true)
        return true;
    else
        return false;
}
