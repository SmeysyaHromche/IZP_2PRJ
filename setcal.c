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
    String** set;
} Set;

typedef struct{
    String* str1;
    String* str2;
} Element;

typedef struct{
    int length;
    Element* relation;
} Relation;

typedef struct{
    bool isSet;
    int pos;
} Position;

enum{U, S, R, C};
enum error{ERR_FOPEN, ERR_ALLOC, ERR_FIRSTLETTER, ERR_MAXSTRLEN, ERR_KEYWORD,
            ERR_ONLYLETTERS, ERR_NOTINUNI, ERR_UNOTFIRST, ERR_TWOUNIS, ERR_FALSEBRACKET,
            ERR_ELEMNOTINBR, ERR_WRONGNUMOFELEMS, ERR_MISSBR, ERR_MAXROW, ERR_NOFIRSTSPACE};

bool empty(Set set){
    if(set.length == 0) return true;
    else return false;
}

void freeAll(String* str, Set* set, Relation* rel, Position* pos, FILE* fp){
    if(str != NULL) free(str->str);
    free(str);
    if(set != NULL) free(set->set);
    free(set);
    if(rel != NULL) free(rel->relation);
    free(rel);
    free(pos);
    fclose(fp);
    return;
}

void error(int type, String* str, Set* set, Relation* rel, Position* pos, FILE* fp){

    switch(type){

        case ERR_FOPEN:
            fprintf(stderr, "Error: Failed to open file!\n");
        break;

        case ERR_ALLOC:
            fprintf(stderr, "Error: Failed to allocate memory!\n");
        break;

        case ERR_FIRSTLETTER:
            fprintf(stderr, "First letter of the row has to be | U | S | R | C |\n");
        break;

        case ERR_MAXSTRLEN:
            fprintf(stderr, "Maximum number of chars in element has been reached [%d]\n", MAXSTRLEN);
        break;

        case ERR_KEYWORD:
            fprintf(stderr, "Universum cannot contain keywords [true | false | commands] or elements of the same name\n");
        break;

        case ERR_ONLYLETTERS:
            fprintf(stderr, "Elements can only contain letters of standard English alphabet\n");
        break;

        case ERR_NOTINUNI:
            fprintf(stderr, "Element is not in Universum or this element is repeated\n");
        break;

        case ERR_UNOTFIRST:
            fprintf(stderr, "Universum has to be declared first\n");
        break;

        case ERR_TWOUNIS:
            fprintf(stderr, "You are not allowed to declare more than one Universum\n");
        break;

        case ERR_FALSEBRACKET:
            fprintf(stderr, "Two opened or closed brackets in row\n");
        break;

        case ERR_ELEMNOTINBR:
            fprintf(stderr, "Element in relation is out of brackets\n");
        break;

        case ERR_WRONGNUMOFELEMS:
            fprintf(stderr, "Number of expressions in one element of relation has to be 2\n");
        break;

        case ERR_MISSBR:
            fprintf(stderr, "There is a missing bracket at the end of relation\n");
        break;

        case ERR_MAXROW:
            fprintf(stderr, "Maximum amount of rows in file has been reached [%d]\n", MAXROW);
        break;

        case ERR_NOFIRSTSPACE:
            fprintf(stderr, "There has to be space between command | U | S | R | C | and elements or other commands\n");
        break;
    }

    freeAll(str, set, rel, pos, fp);
    exit(EXIT_FAILURE);
}

String* reallocStr(String* str, int numOfElems, char* value, int lenOfString){ //allocates memory, memory needs to be freed!!!

    str = (String*) realloc(str, numOfElems*sizeof(String));
    str[numOfElems - 1].length = lenOfString;
    str[numOfElems - 1].str = (char*) calloc(lenOfString, sizeof(char));
    for(int i = 0; i < lenOfString; i++){
        str[numOfElems - 1].str[i] = value[i];
    }
    return str; //could be null
}

Set* reallocSet(Set* set, int numOfSets){ //allocates memory, memory needs to be freed!!!
    if(numOfSets < 1) return NULL;

    set = (Set*) realloc(set, numOfSets*sizeof(Set));
    set[numOfSets - 1].set = NULL;
    return set; //could be null
}

Set* reallocSetElem(Set* set, int numOfSets, int lenOfSet){ //allocates memory, memory needs to be freed!!!

    set[numOfSets - 1].length = lenOfSet;
    set[numOfSets - 1].set = (String**) realloc(set[numOfSets - 1].set, lenOfSet*sizeof(String*));
    return set; //could be null
}

Relation* reallocRel(Relation* rel, int numOfRels){ //allocates memory, memory needs to be freed!!!
    if(numOfRels < 1) return NULL;

    rel = (Relation*) realloc(rel, numOfRels*sizeof(Relation));
    rel[numOfRels - 1].relation = NULL;
    return rel; //could be null
}

Relation* reallocRelElem(Relation* rel, int numOfRels, int lenOfRel){ //allocates memory, memory needs to be freed!!!
    if(lenOfRel < 0 || numOfRels < 1) return NULL;

    rel[numOfRels - 1].length = lenOfRel;
    rel[numOfRels - 1].relation = (Element*) realloc(rel[numOfRels - 1].relation, lenOfRel*sizeof(Element));
    rel[numOfRels - 1].relation[lenOfRel - 1].str1 = NULL;
    rel[numOfRels - 1].relation[lenOfRel - 1].str2 = NULL;

    return rel; //could be null
}

Position* reallocPos(Position* pos, int numOfSets, int numOfRels){ //allocates memory, memory needs to be freed!!!

    int position = numOfRels + numOfSets;
    pos = (Position*) realloc(pos, position*sizeof(Position));

    return pos; //could be null
}

bool checkStr(char* value, String* str, int numOfElems){
    if(!strcmp(value, "U") ||
       !strcmp(value, "S") ||
       !strcmp(value, "R") ||
       !strcmp(value, "C") ||
       !strcmp(value, "true") ||
       !strcmp(value, "false") ||
       !strcmp(value, "empty") ||
       !strcmp(value, "card") ||
       !strcmp(value, "complement") ||
       !strcmp(value, "union") ||
       !strcmp(value, "intersect") ||
       !strcmp(value, "minus") ||
       !strcmp(value, "subseteq") ||
       !strcmp(value, "subset") ||
       !strcmp(value, "equals") ||
       !strcmp(value, "reflexive") ||
       !strcmp(value, "symmetric") ||
       !strcmp(value, "antisymmetric") ||
       !strcmp(value, "transitive") ||
       !strcmp(value, "function") ||
       !strcmp(value, "domain") ||
       !strcmp(value, "codomain") ||
       !strcmp(value, "injective") ||
       !strcmp(value, "surjective") ||
       !strcmp(value, "bijective"))
            return true;

    if(str != NULL){
    for(int i = 0; i < numOfElems; i++){
        if(!strcmp(value, str[i].str)) return true;
    }
    }

    return false;
}

bool checkSet(Set* set, char* value, int numOfSets, int numOfElems){

    bool inUni = false;
    for(int i = 0; i < set[0].length; i++){
        if(!strcmp(set[0].set[i]->str, value)){
            reallocSetElem(set, numOfSets, numOfElems);
            set[numOfSets - 1].set[numOfElems - 1] = set[0].set[i];
            inUni = true;
            break;
        }
    }
    if(!inUni) return true;

    for(int i = 0; i < numOfElems - 1; i++){
        if(set[numOfSets - 1].set[i] == set[numOfSets - 1].set[numOfElems - 1]) return true;
    }

    return false;
}

bool checkRelStr1(Set* set, Relation* rel, char* value, int numOfRels, int numOfElems){

    bool inUni = false;
    for(int i = 0; i < set[0].length; i++){
        if(!strcmp(set[0].set[i]->str, value)){
            rel[numOfRels - 1].relation[numOfElems - 1].str1 = set[0].set[i];
            inUni = true;
            break;
        }
    }
    if(!inUni) return true;
    return false;
}

bool checkRelStr2(Set* set, Relation* rel, char* value, int numOfRels, int numOfElems){

    bool inUni = false;
    for(int i = 0; i < set[0].length; i++){
        if(!strcmp(set[0].set[i]->str, value)){
            rel[numOfRels - 1].relation[numOfElems - 1].str2 = set[0].set[i];
            inUni = true;
            break;
        }
    }
    if(!inUni) return true;

    for(int i = 0; i < rel[numOfRels - 1].length - 1; i++){
        if(rel[numOfRels - 1].relation[i].str1 == rel[numOfRels - 1].relation[numOfElems - 1].str1 &&
           rel[numOfRels - 1].relation[i].str2 == rel[numOfRels - 1].relation[numOfElems - 1].str2)
            return true;
    }
    return false;
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
