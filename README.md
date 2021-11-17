# IZP_2PRJ
# do tohodle repositare strilejte ten projekt
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    int length;
    char* str;
} String;

typedef struct{
    int length;
    String* set;
} Set;

typedef struct{
    String str1;
    String str2;
} Element;

typedef struct{
    int length;
    Element* relation;
} Relation;

bool empty(Set set){
    if(set.length == 0) return true;
    else return false;
}

Set* reallocSet(Set* set, int numOfSets, int lenOfSet){ //allocates memory, memory needs to be freed!!!
    if(lenOfSet < 0 || numOfSets < 1) return NULL;

    set = (Set*) realloc(set, numOfSets*sizeof(Set));
    set[numOfSets - 1].length = lenOfSet;
    set[numOfSets - 1].set = calloc(set[numOfSets - 1].length,
                                    lenOfSet * sizeof(String));
    return set; //could be null
}

String* mallocStr(char* value, int lenOfString){ //allocates memory, memory needs to be freed!!!
    if(lenOfString < 1) return NULL;

    String* str;
    str = (String*) malloc(sizeof(String));
    str->length = lenOfString;
    str->str = calloc(str->length, sizeof(char));
    for(int i = 0; i < lenOfString; i++){
        str->str[i] = value[i];
    }
    return str; //could be null
}
