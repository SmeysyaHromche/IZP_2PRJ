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

String* setStr(char* value, int lenOfString){ //allocates memory, memory needs to be freed!!!
    if(lenOfString < 1) return NULL;

    String string;
    String* str;
    str = &string;
    str->length = lenOfString;
    str->str = calloc(str->length, sizeof(char));
    for(int i = 0; i < lenOfString; i++){
        str->str[i] = value[i];
    }
    return str; //could be null
}

Relation* reallocRel(Relation* rel, int numOfRels, int lenOfRel){ //allocates memory, memory needs to be freed!!!
    if(lenOfRel < 0 || numOfRels < 1) return NULL;

    rel = (Relation*) realloc(rel, numOfRels*sizeof(Relation));
    rel[numOfRels - 1].length = lenOfRel;
    rel[numOfRels - 1].relation = calloc(rel[numOfRels - 1].length,
                                    lenOfRel * sizeof(Element));
    return rel; //could be null
}

Element createElem(String* str1, String* str2){
    Element elem;
    elem.str1 = *str1;
    elem.str2 = *str2;
    return elem;
}

main(){


    return 0;
}

