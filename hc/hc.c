/*
hc.c
3.22.2012

Happy C.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
File manipulation stuff.

Unfortunately, ANSI C standards are a bit
lacking, e.g. when it comes to getting the
size of a file.
*/
typedef struct fileBufferStruct fileBuffer;
struct fileBufferStruct{
    char* content;
    size_t size;
};
fileBuffer* makeFileBuffer(FILE* fp){
    fileBuffer* ret = malloc(sizeof(fileBuffer));
    
    
    
    return ret;
}
void deleteFileBuffer(fileBuffer* fb){
    free(fb->content);
    free(fb);
}



int main(int argc, char* argv[]){
    size_t t = 0;
    t--;
    printf("%lu\n", t);
    return 0;
}