// simgc --> simple garbage collector.
#ifndef SIMGC_H
#define SIMGC_H

// SGC --> simple garbage collector.
typedef struct SGC_Object_s SGC_Object;
typedef struct SGC_State_s SGC_State;

struct SGC_Object_s{
	SGC_Object** x;
	size_t n;
	// If x == NULL, then Object may be used as a primitive type.
	// n == 0 --> None type,
	// n == 1 --> char type,
	// n == 2 --> int type.
	char c;
	int i;
};
struct SGC_State_s{
	SGC_Object** stack;
	size_t nstack;
};
SGC_State* SGC_new_State();
void SGC_del_State(SGC_State*);


SGC_State* SGC_new_State(){
	SGC_State* ret = malloc(sizeof(SGC_State));
	ret->stack = NULL;
	ret->nstack = 0;
	return ret;
}
void SGC_del_State(SGC_State* state){
	
}



#endif//SIMGC_H
