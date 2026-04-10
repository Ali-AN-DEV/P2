#ifndef COMMITTEE_LIST_H
#define COMMITTEE_LIST_H

#include "types.h"
#include "project_list.h"
#include <stdbool.h>

#define MAX_COMMITTEES 10
#define NULLC -1

typedef int tPosC;

/* Elemento de la lista de comités */
typedef struct {
    tCommitteeName committeeName;
    tNumVotes      totalEvaluators;
    tNumVotes      validVotes;
    tNumVotes      nullVotes;
    tListP         projectList;
} tItemC;

typedef struct {
    tItemC data[MAX_COMMITTEES];
    tPosC  lastPos;
} tListC;

void   createEmptyListC(tListC *L);
bool   isEmptyListC(tListC L);
tPosC  firstC(tListC L);
tPosC  lastC(tListC L);
tPosC  nextC(tPosC p, tListC L);
tPosC  previousC(tPosC p, tListC L);
bool   insertItemC(tItemC d, tListC *L);
void   deleteAtPositionC(tPosC p, tListC *L);
tItemC getItemC(tPosC p, tListC L);
void   updateItemC(tItemC d, tPosC p, tListC *L);
tPosC  findItemC(tCommitteeName name, tListC L);

#endif