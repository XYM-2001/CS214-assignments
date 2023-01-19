#include <stdlib.h>
#include <stdio.h>
#include "strbuf.h"
#include <string.h>

#ifndef DEBUG
#define DEBUG 0
#endif

int sb_init(strbuf_t *L, size_t length)
{
    L->data = malloc(sizeof(char) * (length+1));
    if (!L->data) return 1;

    L->length = length;
    L->used   = 0;
    L->data[0] = '\0';
    return 0;
}

void sb_destroy(strbuf_t *L)
{
    free(L->data);
}


int sb_append(strbuf_t *L, char item)
{
    if (L->used == L->length) {
	size_t size = L->length * 2;
	char *p = realloc(L->data, sizeof(char) * (size+1));
	if (!p) return 1;

	L->data = p;
	L->length = size;

	if (DEBUG) printf("Increased size to %lu\n", size);
    }

    L->data[L->used] = item;
    ++L->used;
    L->data[L->used+1] = '\0';
    return 0;
}


int sb_remove(strbuf_t *L, char *item)
{
    if (L->used == 0) return 1;

    --L->used;

    if (item) *item = L->data[L->used];
    L->data[L->used] = '\0';
    return 1;
}
int sb_insert(strbuf_t *list, int index, char item)
{
    if(!list || index < 0){
        return 1;
    }
    size_t length = list->length;
    if(index >= list->used){
        list-> used = index + 1;
    }
    else {
        list-> used += 1;
    }
    if(list->used > length && (list->used) <= (length*2)){
        list->data = realloc(list->data, sizeof(int)*(length*2+1));
        if(list->data == NULL){
            return 1;
        }
        list->length = length*2;
        length *= 2;
    }
    else if(list->used > length*2){
        list->data = realloc(list->data, sizeof(int)*(list->used+1));
        if(list->data == NULL){
            return 1;
        }
        list->length = list->used;
        length = list->used; 
    }
    for(int i = index+1; i < length; i++){
        list->data[i] = list->data[i-1];
    }
    list->data[index] = item;
    list->data[list->used] = '\0';
    return 0;
}
int sb_concat(strbuf_t *sb, char *str){
    size_t oldused = sb->used;
    if(!sb || !str){
        return 1;
    }
    sb->used += strlen(str);
    if (sb->used > sb->length && (sb->used) <= sb->length*2 ){
        sb->data = realloc(sb->data, sizeof(int)*(sb->length*2+1));
        if(!sb->data) return 1;
        sb->length = sb->length*2;
    }
    else if(sb->used > sb->length*2){
        sb->data = realloc(sb->data, sizeof(int)*(sb->used+1));
        if(!sb->data) return 1;
        sb->length = sb->used;
    }
    for(int i = 0; i < strlen(str); i++){
        sb->data[i+oldused] = str[i];
    }
    sb->data[sb->used] = '\0';
    return 0;
}