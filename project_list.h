#ifndef PROJECT_LIST_H
#define PROJECT_LIST_H

#include "types.h"
#include <stdbool.h>

#define NULLP NULL

/* Elemento de la lista de proyectos */
typedef struct {
    tProjectName projectName;
    tNumVotes    numVotes;
    tProjectEco  projectEco;
} tItemP;

/* Nodo interno de la lista enlazada */
typedef struct tNodeP {
    tItemP        data;
    struct tNodeP *next;
} tNodeP;

typedef tNodeP *tPosP;
typedef tPosP   tListP;

void   createEmptyListP(tListP *L);
bool   isEmptyListP(tListP L);
tPosP  firstP(tListP L);
tPosP  lastP(tListP L);
tPosP  nextP(tPosP p, tListP L);
tPosP  previousP(tPosP p, tListP L);
bool   createNodeP(tPosP *p);
bool   insertItemP(tItemP d, tListP *L);
void   deleteAtPositionP(tPosP p, tListP *L);
tItemP getItemP(tPosP p, tListP L);
void   updateItemP(tItemP d, tPosP p, tListP *L);
tPosP  findItemP(tProjectName name, tListP L);

#endif