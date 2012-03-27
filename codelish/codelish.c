/*
codelish.cpp
3.26.2012
*/
#include<stdlib.h>
#include<stdio.h>
// stack (for convenience)
typedef struct StackNode_s StackNode;
typedef struct Stack_s Stack;
struct StackNode_s{
    void* data;
};
struct Stack_s{
    StackNode** bottom; // array of StackNode*.
    size_t size;
    void* (*copyData)(void*);
    void (*deleteData)(void*);
};
Stack* newStackFromCopyAndDeleteMethods(void* (*copyData)(void*), void (*deleteData)(void*));
void deleteStack(Stack* stack);
void pushDataIntoStack(void* data, Stack* stack);
void popStack(Stack* stack);
void* topOfStack(Stack* stack);
void* elementOfStackAtIndex(Stack* stack, size_t index);


void* intCopy(void* x){
    void* ret = malloc(sizeof(int));
    (* (int*)ret) = (* (int*)x);
    return ret;
}
void intDel(void* x){ free(x); }
int main(int argc, char* argv[]){
    Stack* stack = newStackFromCopyAndDeleteMethods(&intCopy, &intDel);
    int x = 1;
    pushDataIntoStack((void*) &x, stack);
    x++;
    pushDataIntoStack((void*) &x, stack);
    x++;
    pushDataIntoStack((void*) &x, stack);
    popStack(stack);
    
    printf("%d\n", *(int*)elementOfStackAtIndex(stack,0));
    printf("%d\n", *(int*)elementOfStackAtIndex(stack,1));
    //printf("%d\n", *(int*)elementOfStackAtIndex(stack,2));
    printf("%d\n", *(int*)topOfStack(stack));
    popStack(stack);
    printf("%d\n", *(int*)topOfStack(stack));
    return 0;
}


// implementations.

// stack (for convenience)
Stack* newStackFromCopyAndDeleteMethods(void* (*copyData)(void*), void (*deleteData)(void*)){
    Stack* newStack = malloc(sizeof(Stack));
    newStack->bottom = NULL;
    newStack->size = 0;
    newStack->copyData = copyData;
    newStack->deleteData = deleteData;
    return newStack;
}
void deleteStack(Stack* stack){
    int i;
    for (i = 0; i < stack->size; i++){
        (*(stack->deleteData))(stack->bottom[i]->data);
        free(stack->bottom[i]);
    }
    free(stack->bottom);
    free(stack);
}
void pushDataIntoStack(void* data, Stack* stack){
    stack->bottom = realloc(stack->bottom, (stack->size+1)*sizeof(StackNode*));
    stack->bottom[stack->size] = malloc(sizeof(StackNode));
    stack->bottom[stack->size]->data = (*(stack->copyData))(data);
    stack->size++;
}
void popStack(Stack* stack){
    stack->size--;
    stack->deleteData(stack->bottom[stack->size]->data);
    free(stack->bottom[stack->size]);
    stack->bottom = realloc(stack->bottom, (stack->size)*sizeof(StackNode*));
}
void* topOfStack(Stack* stack){
    return stack->bottom[stack->size-1]->data;
}
void* elementOfStackAtIndex(Stack* stack, size_t index){
    return stack->bottom[index]->data;
}
