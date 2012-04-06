#include<stdio.h>
#include<stdlib.h>

typedef struct Buffer_s Buffer;
struct Buffer_s{
    char* content;
    size_t size;
};
void freeBuffer(Buffer* buffer);
Buffer* loadBufferFromFileName(char* filename);
Buffer* loadBufferFromFileStream(FILE* fileStream);

void freeBuffer(Buffer* buffer){
    free(buffer->content);
    free(buffer);
}

Buffer* loadBufferFromFileName(char* filename){
    FILE* fileStream = fopen(filename, "rb");
    Buffer* ret = loadBufferFromFileStream(fileStream);
    fclose(fileStream);
    return ret;
}

Buffer* loadBufferFromFileStream(FILE* fileStream){
    size_t sizeRead = 0;
    
    Buffer* ret = malloc(sizeof(Buffer));
    ret->content = NULL;
    ret->size = 0;
    while (!feof(fileStream)){
        ret->content = realloc(ret->content, ret->size+(1024*sizeof(char)));
        sizeRead = fread(ret->content, sizeof(char), 1024, fileStream);
        ret->size += sizeRead;
    }
    
    fclose(fileStream);
    return ret;
}

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("Usage: %s [file name]\n", argv[0]);
        return 0;
    }
    Buffer* buffer = loadBufferFromFileName(argv[1]);
    printf("%lu\n", buffer->size);
    printf("0: %d %c\n", buffer->content[0], buffer->content[0]);
    printf("1: %d %c\n", buffer->content[1], buffer->content[1]);
    
    return 0;
}