/*
4.3.2012
Take any binary file, and convert it into a text file with purely lower case letter.
*/
#include<stdio.h>
#include<stdlib.h>

/* Headers */
typedef struct Buffer_s Buffer;
struct Buffer_s{
    char* content;
    size_t size; // number of chars in buffer
};
/* File reading methods */
void freeBuffer(Buffer* buffer);
Buffer* loadBufferFromFileName(char* filename);
Buffer* loadBufferFromFileStream(FILE* fileStream);
void concatToFirstBuffer(Buffer* first, Buffer*, second);
void writeBufferToFileByFileName(Buffer* buffer, char* filename);
void writeBufferToFileStream(Buffer* buffer, FILE* fileStream);
/* conversions */
typedef struct LetterSequence_s LetterSequence;
struct LetterSequence_s{
    unsigned char* letters;
    size_t size;
};
void freeLetterSequence(LetterSequence* ls);
void addLetterToSequence(unsigned char c, LetterSequence* ls);
LetterSequence* lettersequenceFromChar(unsigned char c);
unsigned char charFromLetterSequence(LetterSequence* ls);

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("Usage: %s ['encode'|'decode'] [filename]", argv[0]);
        return 0;
    }
    
    Buffer* buffer = loadBufferFromFileName(argv[2]);
    if (strcmp(argv[1],"encode") == 0){
        int i;
        for (i = 0; i < buffer->size; i++){
            Buffer* toAdd = buffer->content[i];
        }
    }
    
    
    return 0;
}

/* Implementations */

// File Reading methods.
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
    return ret;
}
void concatToFirstBuffer(Buffer* first, Buffer*, second){
    first->content = realloc(first->content, (first->size+second->size) * sizeof(char));
    size_t i;
    for (i = first->size; i < first->size + second->size; i++){
        first->content[i] = second->content[i-first->size];
    }
    first->size += second->size;
}
void writeBufferToFileByFileName(Buffer* buffer, char* filename){
    FILE* fileStream = fopen(filename);
    writeBufferToFileStream(buffer, fileStream);
    fclose(fileStream);
}
void writeBufferToFileStream(Buffer* buffer, FILE* fileStream){
    fwrite(buffer->content,buffer->size,sizeof(char),fileStream);
}

// Conversion methods.
void freeLetterSequence(LetterSequence* ls){
    free(ls->letters);
    free(ls);
}
void addLetterToSequence(unsigned char c, LetterSequence* ls){
    ls->letters = realloc(ls->letters, ls->size+1); ls->size++;
    ls->letters[ls->size-1] = c;
}
LetterSequence* lettersequenceFromChar(unsigned char c){
    LetterSequence* ret = malloc(sizeof(LetterSequence));
    ret->letters = NULL;
    ret->size = 0;
    while (c > 24){
        addLetterToSequence('a', ret);
        c -= 24;
    }
    addLetterToSequence('b' + c, ret);
    return ret;
}
unsigned char charFromLetterSequence(LetterSequence* ls){
    char ret = 0;
    int i = 0;
    
    for (i = 0; i < ls->size; i++){
        if (ls->letters[i] == 'a'){
            ret += 24;
        }
        else {
            ret += (ls->letters[i] - 'b');
        }
    }
    return ret;
}

