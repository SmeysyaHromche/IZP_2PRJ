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
    return set.length == 0;
}

Set* reallocSet(Set* set, int numOfSets, int lenOfSet){ //allocates memory, memory needs to be freed!!!
    if(lenOfSet < 0 || numOfSets < 1) return NULL;

    set = (Set*) realloc(set, numOfSets*sizeof(Set));
    set[numOfSets - 1].length = lenOfSet;
    set[numOfSets - 1].set = calloc(set[numOfSets - 1].length,
                                    lenOfSet * sizeof(String));
    return set; //could be null
}

String setStr(char* value, int lenOfString){ //allocates memory, memory needs to be freed!!!
    String str;
    str.length = lenOfString;
    str.str = calloc(str.length, sizeof(char));
    for(int i = 0; i < lenOfString; i++){
        str.str[i] = value[i];
    }
    return str;
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

bool hasElem(Element *elem, Relation *rel) {
    for (int i = 0; i < rel->length; i++) {
        if (!memcmp(rel->relation + i, elem, sizeof(Element))) // rel->relation[i] == *elem
            return true;
    }
    return false;
}

bool isReflexive(Relation* rel, Set* u) {
    for (int i = 0; i < u->length; i++) { // prechadzam vsetky prvky a univerza U
        Element ref = createElem(u->set + i, u->set + i); // vytvorim (a, a)
        if (!hasElem(&ref, rel))
            return false;
    }
    return true;
}

bool isSymmetric(Relation* rel) {
    for (int i = 0; i < rel->length; i++) {
        // pre element rel->relation[i]; hladat jeho sym. element
        Element orig = rel->relation[i]; // *(rel->relation + i)
        // symetricky element
        Element sym = createElem(&orig.str2, &orig.str1);
        if (!hasElem(&sym, rel))
            return false;
    }
    return true;
}

bool isAntiSymmetric(Relation *rel) {
    for (int i = 0; i < rel->length; i++) {
        // pre element rel->relation[i]; hladat jeho sym. element
        Element orig = rel->relation[i]; // *(rel->relation + i)
        // symetricky element
        Element sym = createElem(&orig.str2, &orig.str1);
        // skip the reflexive elements
        if (!memcmp(&orig, &sym, sizeof(Element))) // orig == sym
            continue;
        if (hasElem(&sym, rel))
            return false;
    }
    return true;
}

bool isTransitive (Relation *rel) {
    for (int i = 0; i < rel->length; i++) {  // najdi first = (a, b)
        Element first = rel->relation[i]; // *(rel->relation + i)
        for (int j = 0; j < rel->length; j++) {  // najdi second = (b, c)
            Element second = rel->relation[j];
            if (!memcmp(&first.str2, &second.str1, sizeof(String))) // first.str2 == second.str1, tj. b == b
            {
                // vytvorime tranzitivny element trans = (a, c)
                Element trans = createElem(&first.str1, &second.str2);
                if (!hasElem(&trans, rel))
                    return false;
            }
        }
    }
    return true;
}

bool isFunction (Relation *rel) {
    for (int i = 0; i < rel->length; i++) {  // najdi first = (a, b)
        Element first = rel->relation[i]; // *(rel->relation + i)
        for (int j = 0; j < rel->length; j++) {  // najdi second = (a, c)
            Element second = rel->relation[j];
            if (!memcmp(&first.str1, &second.str1, sizeof(String)) && memcmp(&first.str2, &second.str2, sizeof(String))) // a == a and b != c
            {
                return false;
            }
        }
    }
    return true;
}

bool isInjective(Relation *rel) {
    for (int i = 0; i < rel->length; i++) {  // najdi first = (a, b)
        Element first = rel->relation[i]; // *(rel->relation + i)
        for (int j = 0; j < rel->length; j++) {  // najdi second = (c, b)
            Element second = rel->relation[j];
            if (!memcmp(&first.str2, &second.str2, sizeof(String)) && memcmp(&first.str1, &second.str1, sizeof(String))) // b == b and a != c
            {
                return false;
            }
        }
    }
    return true;
}

int main(){
    return 0;
}