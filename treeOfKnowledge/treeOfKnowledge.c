#include<stdio.h>

typedef struct treeStruct tree;
struct treeStruct {
	// answer or question depending on context.
	char content[64];
	
	tree* yes;
	tree* no;
};


int main(int argc, char* argv[]){
	
	return 0;
}
