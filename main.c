/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Ali Abu-afash Nayef LOGIN 1: ali.nayef@udc.es
 * AUTHOR 2: Isabel Mª Teijido Bernal LOGIN 2: isabel.teijido@udc.es
 * GROUP: 4.2
 * DATE: 03 / 06 / 26
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "committee_list.h"

#define MAX_BUFFER 255

/* Lista global de comites evaluadores */
tListC committeeList;

/****
 * Objetivo: Imprimir la cabecera de una peticion (20 asteriscos y linea
 *   descriptiva con los parametros necesarios segun la operacion).
 * Entradas:
 *   - commandNumber: numero de peticion (cadena, p.ej. "01").
 *   - command: caracter identificador de la operacion (C, N, V, D, R, S, W).
 *   - param1: primer parametro (committeeName o projectName segun operacion).
 *   - param2: segundo parametro (totalEvaluators o projectName).
 *   - param3: tercer parametro (categoria: "eco" o "non-eco").
 * Salidas: ninguna (escribe en stdout).
 * Precondiciones: commandNumber y command validos.
 * Postcondiciones: Se imprime la cabecera por pantalla.
 ****/
void printHeader(char *commandNumber, char command,
                 char *param1, char *param2, char *param3) {
    printf("********************\n");
    switch (command) {
        case 'C':
            printf("%s C: committee %s totalevaluators %s\n",
                   commandNumber, param1, param2);
            break;
        case 'N':
            printf("%s N: committee %s project %s category %s\n",
                   commandNumber, param1, param2, param3);
            break;
        case 'V':
            printf("%s V: committee %s project %s\n",
                   commandNumber, param1, param2);
            break;
        case 'D':
            printf("%s D: project %s\n", commandNumber, param1);
            break;
        case 'R':
            printf("%s R:\n", commandNumber);
            break;
        case 'S':
            printf("%s S:\n", commandNumber);
            break;
        case 'W':
            printf("%s W:\n", commandNumber);
            break;
        default:
            break;
    }
}

/****
 * Objetivo: Procesar la operacion [C]reate: anadir un nuevo comite evaluador
 *   a la lista global con 0 votos validos, 0 votos nulos y lista de proyectos
 *   vacia.
 * Entradas:
 *   - committeeName: nombre del comite a crear.
 *   - totalEvaluatorsStr: numero total de evaluadores (cadena numerica).
 * Salidas: ninguna (escribe en stdout).
 * Precondiciones: Cadenas validas.
 * Postcondiciones: El comite queda insertado en orden alfabetico si exito.
 ****/
void processCreate(char *committeeName, char *totalEvaluatorsStr) {
    tItemC item; /* Elemento comite a insertar */

    if (findItemC(committeeName, committeeList) != NULLC) {
        printf("+ Error: Create not possible\n");
        return;
    }
    strcpy(item.committeeName, committeeName);
    item.totalEvaluators = atoi(totalEvaluatorsStr);
    item.validVotes = 0;
    item.nullVotes  = 0;
    createEmptyListP(&item.projectList);

    if (!insertItemC(item, &committeeList)) {
        printf("+ Error: Create not possible\n");
        return;
    }
    /* Nota: "totalEvaluators" con E mayuscula segun formato de salida */
    printf("* Create: committee %s totalEvaluators %d\n",
           committeeName, item.totalEvaluators);
}

/****
 * Objetivo: Procesar la operacion [N]ew: anadir un proyecto con 0 votos
 *   a la lista de proyectos de un comite existente.
 * Entradas:
 *   - committeeName: nombre del comite evaluador.
 *   - projectName: nombre del proyecto a anadir.
 *   - projectEcoStr: "eco" o "non-eco".
 * Salidas: ninguna (escribe en stdout).
 * Precondiciones: Cadenas validas.
 * Postcondiciones: El proyecto queda en la lista del comite si exito.
 ****/
void processNew(char *committeeName, char *projectName, char *projectEcoStr) {
    tPosC  posC;  /* Posicion del comite en la lista global */
    tItemC itemC; /* Datos del comite a modificar */
    tItemP itemP; /* Nuevo proyecto */

    posC = findItemC(committeeName, committeeList);
    if (posC == NULLC) {
        printf("+ Error: New not possible\n");
        return;
    }
    itemC = getItemC(posC, committeeList);
    if (findItemP(projectName, itemC.projectList) != NULLP) {
        printf("+ Error: New not possible\n");
        return;
    }
    strcpy(itemP.projectName, projectName);
    itemP.numVotes   = 0;
    itemP.projectEco = (strcmp(projectEcoStr, "eco") == 0);

    if (!insertItemP(itemP, &itemC.projectList)) {
        printf("+ Error: New not possible\n");
        return;
    }
    updateItemC(itemC, posC, &committeeList);
    printf("* New: committee %s project %s category %s\n",
           committeeName, projectName, projectEcoStr);
}

/****
 * Objetivo: Procesar la operacion [V]ote: emitir un voto para un proyecto
 *   en un comite evaluador. Si el proyecto no existe, el voto es nulo.
 * Entradas:
 *   - committeeName: nombre del comite receptor del voto.
 *   - projectName: nombre del proyecto al que se vota.
 * Salidas: ninguna (escribe en stdout).
 * Precondiciones: Cadenas validas.
 * Postcondiciones: Si el proyecto existe, numVotes y validVotes crecen en 1.
 *   Si no, nullVotes crece en 1.
 ****/
void processVote(char *committeeName, char *projectName) {
    tPosC  posC;  /* Posicion del comite */
    tItemC itemC; /* Datos del comite */
    tPosP  posP;  /* Posicion del proyecto */
    tItemP itemP; /* Datos del proyecto */

    posC = findItemC(committeeName, committeeList);
    if (posC == NULLC) {
        printf("+ Error: Vote not possible\n");
        return;
    }
    itemC = getItemC(posC, committeeList);
    posP  = findItemP(projectName, itemC.projectList);

    if (posP == NULLP) {
        itemC.nullVotes++;
        updateItemC(itemC, posC, &committeeList);
        printf("+ Error: Vote not possible. Project %s not found in committee %s. NULLVOTE\n",
               projectName, committeeName);
        return;
    }
    itemP = getItemP(posP, itemC.projectList);
    itemP.numVotes++;
    updateItemP(itemP, posP, &itemC.projectList);
    itemC.validVotes++;
    updateItemC(itemC, posC, &committeeList);

    printf("* Vote: committee %s project %s category %s numvotes %d\n",
           committeeName, projectName,
           itemP.projectEco ? "eco" : "non-eco",
           itemP.numVotes);
}

/****
 * Objetivo: Procesar la operacion [D]isqualify: eliminar un proyecto de
 *   todas las listas locales, convirtiendo sus votos en nulos.
 * Entradas:
 *   - projectName: nombre del proyecto a descalificar.
 * Salidas: ninguna (escribe en stdout).
 * Precondiciones: Cadena valida.
 * Postcondiciones: El proyecto queda eliminado de todos los comites que
 *   lo tuviesen y sus votos pasan a nullVotes.
 ****/
void processDisqualify(char *projectName) {
    tPosC  posC;  /* Posicion del comite en la lista global */
    tItemC itemC; /* Datos del comite a modificar */
    tPosP  posP;  /* Posicion del proyecto en la lista del comite */
    tItemP itemP; /* Datos del proyecto a eliminar */

    if (isEmptyListC(committeeList)) {
        printf("+ Error: Disqualify not possible\n");
        return;
    }
    posC = firstC(committeeList);
    while (posC != NULLC) {
        itemC = getItemC(posC, committeeList);
        printf("Committee %s\n", itemC.committeeName);

        posP = findItemP(projectName, itemC.projectList);
        if (posP != NULLP) {
            itemP = getItemP(posP, itemC.projectList);
            itemC.nullVotes  += itemP.numVotes;
            itemC.validVotes -= itemP.numVotes;
            deleteAtPositionP(posP, &itemC.projectList);
            updateItemC(itemC, posC, &committeeList);
            printf("Project %s disqualified\n", projectName);
        } else {
            printf("No project %s\n", projectName);
        }
        printf("\n"); /* Linea en blanco despues de cada comite */
        posC = nextC(posC, committeeList);
    }
}

/****
 * Objetivo: Procesar la operacion [R]emove: eliminar los comites con
 *   0 votos validos, liberando antes sus listas de proyectos.
 * Entradas: ninguna.
 * Salidas: ninguna (escribe en stdout).
 * Precondiciones: ninguna.
 * Postcondiciones: Los comites con validVotes==0 son eliminados de
 *   committeeList.
 ****/
void processRemove(void) {
    tPosC  posC;    /* Posicion actual durante el recorrido */
    tItemC itemC;   /* Datos del comite candidato a eliminar */
    tPosP  posP;    /* Auxiliar para vaciar la lista de proyectos */
    bool   removed; /* Indica si se elimino al menos un comite */

    if (isEmptyListC(committeeList)) {
        printf("+ Error: Remove not possible\n");
        return;
    }
    removed = false;
    posC    = firstC(committeeList);

    while (posC != NULLC) {
        itemC = getItemC(posC, committeeList);

        if (itemC.validVotes == 0) {
            /* Vaciar lista de proyectos (precondicion de deleteAtPositionC) */
            while (!isEmptyListP(itemC.projectList)) {
                posP = firstP(itemC.projectList);
                deleteAtPositionP(posP, &itemC.projectList);
            }
            updateItemC(itemC, posC, &committeeList);
            printf("* Remove: committee %s\n", itemC.committeeName);
            deleteAtPositionC(posC, &committeeList);
            removed = true;
            /* Tras el borrado el array se desplaza; verificar limites */
            if (isEmptyListC(committeeList) || posC > lastC(committeeList))
                posC = NULLC;
            /* Si no, el siguiente elemento esta ahora en posC */
        } else {
            posC = nextC(posC, committeeList);
        }
    }
    if (!removed)
        printf("+ Error: Remove not possible\n");
}

/****
 * Objetivo: Procesar la operacion [S]tats: mostrar estadisticas de voto
 *   de todos los comites evaluadores.
 * Entradas: ninguna.
 * Salidas: ninguna (escribe en stdout).
 * Precondiciones: ninguna.
 * Postcondiciones: committeeList no se modifica.
 * Notas de formato:
 *   - Porcentaje de proyecto = numVotes / validVotes * 100 (0 si validVotes==0).
 *   - Participation usa "voters" si el comite tiene proyectos, "evaluators" si no.
 *   - Linea en blanco despues de cada bloque de comite (incluido el ultimo).
 ****/
void processStats(void) {
    tPosC  posC;       /* Posicion del comite */
    tItemC itemC;      /* Datos del comite actual */
    tPosP  posP;       /* Posicion del proyecto */
    tItemP itemP;      /* Datos del proyecto actual */
    int    totalVotes; /* Votos emitidos (validos + nulos) */
    float  pctProject; /* Porcentaje de votos de un proyecto */
    float  pctPart;    /* Porcentaje de participacion */

    if (isEmptyListC(committeeList)) {
        printf("+ Error: Stats not possible\n");
        return;
    }
    posC = firstC(committeeList);
    while (posC != NULLC) {
        itemC = getItemC(posC, committeeList);
        printf("Committee %s\n", itemC.committeeName);

        if (isEmptyListP(itemC.projectList)) {
            printf("No projects\n");
        } else {
            posP = firstP(itemC.projectList);
            while (posP != NULLP) {
                itemP = getItemP(posP, itemC.projectList);
                /* Porcentaje sobre votos validos del comite */
                pctProject = (itemC.validVotes > 0)
                    ? ((float)itemP.numVotes / itemC.validVotes * 100.0f)
                    : 0.0f;
                printf("Project %s category %s numvotes %d (%.2f%%)\n",
                       itemP.projectName,
                       itemP.projectEco ? "eco" : "non-eco",
                       itemP.numVotes,
                       pctProject);
                posP = nextP(posP, itemC.projectList);
            }
        }

        totalVotes = itemC.validVotes + itemC.nullVotes;
        pctPart    = (itemC.totalEvaluators > 0)
            ? ((float)totalVotes / itemC.totalEvaluators * 100.0f)
            : 0.0f;
        printf("Nullvotes %d\n", itemC.nullVotes);
        /* "voters" si hay proyectos en la lista; "evaluators" si esta vacia */
        if (isEmptyListP(itemC.projectList))
            printf("Participation: %d votes from %d evaluators (%.2f%%)\n",
                   totalVotes, itemC.totalEvaluators, pctPart);
        else
            printf("Participation: %d votes from %d voters (%.2f%%)\n",
                   totalVotes, itemC.totalEvaluators, pctPart);

        printf("\n"); /* Linea en blanco despues de cada comite */
        posC = nextC(posC, committeeList);
    }
}

/****
 * Objetivo: Procesar la operacion [W]inners: mostrar el proyecto ganador
 *   de cada categoria (eco y non-eco) por comite.
 *   Reglas: un unico proyecto (incluso con 0 votos) gana; empate o
 *   categoria vacia => "No winner".
 * Entradas: ninguna.
 * Salidas: ninguna (escribe en stdout).
 * Precondiciones: ninguna.
 * Postcondiciones: committeeList no se modifica.
 ****/
void processWinners(void) {
    tPosC  posC;         /* Posicion del comite */
    tItemC itemC;        /* Datos del comite actual */
    tPosP  posP;         /* Posicion del proyecto */
    tItemP itemP;        /* Datos del proyecto actual */
    tItemP ecoWinner;    /* Ganador categoria eco */
    tItemP nonEcoWinner; /* Ganador categoria non-eco */
    bool   ecoFound;     /* Se encontro al menos un proyecto eco */
    bool   nonEcoFound;  /* Se encontro al menos un proyecto non-eco */
    bool   ecoTie;       /* Hay empate en eco */
    bool   nonEcoTie;    /* Hay empate en non-eco */

    if (isEmptyListC(committeeList)) {
        printf("+ Error: Winners not possible\n");
        return;
    }
    posC = firstC(committeeList);
    while (posC != NULLC) {
        itemC      = getItemC(posC, committeeList);
        printf("Committee %s\n", itemC.committeeName);

        ecoFound    = false;
        nonEcoFound = false;
        ecoTie      = false;
        nonEcoTie   = false;

        posP = firstP(itemC.projectList);
        while (posP != NULLP) {
            itemP = getItemP(posP, itemC.projectList);
            if (itemP.projectEco) {
                if (!ecoFound) {
                    ecoWinner = itemP; ecoFound = true;
                } else if (itemP.numVotes > ecoWinner.numVotes) {
                    ecoWinner = itemP; ecoTie = false;
                } else if (itemP.numVotes == ecoWinner.numVotes) {
                    ecoTie = true;
                }
            } else {
                if (!nonEcoFound) {
                    nonEcoWinner = itemP; nonEcoFound = true;
                } else if (itemP.numVotes > nonEcoWinner.numVotes) {
                    nonEcoWinner = itemP; nonEcoTie = false;
                } else if (itemP.numVotes == nonEcoWinner.numVotes) {
                    nonEcoTie = true;
                }
            }
            posP = nextP(posP, itemC.projectList);
        }

        /*
         * Criterios: sin proyectos => No winner; 1 proyecto (aunque tenga
         * 0 votos) => gana; varios sin empate => mayor gana; empate => No winner.
         */
        if (ecoFound && !ecoTie)
            printf("Category eco: Project %s numvotes %d\n",
                   ecoWinner.projectName, ecoWinner.numVotes);
        else
            printf("Category eco: No winner\n");

        if (nonEcoFound && !nonEcoTie)
            printf("Category non-eco: Project %s numvotes %d\n",
                   nonEcoWinner.projectName, nonEcoWinner.numVotes);
        else
            printf("Category non-eco: No winner\n");

        printf("\n"); /* Linea en blanco despues de cada comite */
        posC = nextC(posC, committeeList);
    }
}

/****
 * Objetivo: Despachar una peticion: imprimir la cabecera y ejecutar la
 *   funcion de procesado correspondiente.
 * Entradas:
 *   - commandNumber: numero de la peticion.
 *   - command: caracter identificador de la operacion.
 *   - param1, param2, param3: parametros (pueden ser NULL segun operacion).
 * Salidas: ninguna.
 * Precondiciones: commandNumber y command validos.
 * Postcondiciones: Se imprime la cabecera y se ejecuta la operacion.
 ****/
void processCommand(char *commandNumber, char command,
                    char *param1, char *param2, char *param3) {
    printHeader(commandNumber, command, param1, param2, param3);
    switch (command) {
        case 'C': processCreate(param1, param2);       break;
        case 'N': processNew(param1, param2, param3);  break;
        case 'V': processVote(param1, param2);         break;
        case 'D': processDisqualify(param1);           break;
        case 'R': processRemove();                     break;
        case 'S': processStats();                      break;
        case 'W': processWinners();                    break;
        default:                                       break;
    }
}

/****
 * Objetivo: Leer y procesar todas las peticiones del fichero de entrada.
 * Entradas:
 *   - filename: ruta al fichero de texto con las peticiones.
 * Salidas: ninguna.
 * Precondiciones: filename es una ruta accesible.
 * Postcondiciones: Todas las peticiones del fichero han sido procesadas.
 ****/
void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");
    if (f != NULL) {
        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command       = strtok(NULL, delimiters);
            param1        = strtok(NULL, delimiters);
            param2        = strtok(NULL, delimiters);
            param3        = strtok(NULL, delimiters);
            processCommand(commandNumber, command[0], param1, param2, param3);
        }
        fclose(f);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

/****
 * Objetivo: Punto de entrada del programa. Inicializa committeeList y
 *   procesa el fichero de peticiones indicado.
 * Entradas:
 *   - nargs: numero de argumentos de linea de comandos.
 *   - args: vector de argumentos.
 * Salidas: 0 en caso de ejecucion correcta.
 * Precondiciones: ninguna.
 * Postcondiciones: Todas las peticiones han sido procesadas.
 ****/
int main(int nargs, char **args) {
    char *file_name = "create.txt";

    createEmptyListC(&committeeList);

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);
    return 0;
}