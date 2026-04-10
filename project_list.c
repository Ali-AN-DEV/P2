/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Ali Abu-afash Nayef LOGIN 1: ali.nayef@udc.es
 * AUTHOR 2: Isabel Mª Teijido Bernal LOGIN 2: isabel.teijido@udc.es
 * GROUP: 4.2
 * DATE: 03 / 06 / 26
 */

#include "project_list.h"
#include <stdlib.h>
#include <string.h>

/****
 * Objetivo: Inicializar una lista de proyectos vacía.
 * Entradas:
 *   - L: puntero a la lista a inicializar.
 * Salidas: ninguna.
 * Precondiciones: L debe ser un puntero válido.
 * Postcondiciones: *L queda establecida como lista vacía (NULLP).
 ****/
void createEmptyListP(tListP *L) {
    *L = NULLP;
}

/****
 * Objetivo: Comprobar si la lista de proyectos está vacía.
 * Entradas:
 *   - L: lista de proyectos.
 * Salidas: true si la lista está vacía; false en caso contrario.
 * Precondiciones: L debe estar inicializada.
 * Postcondiciones: L no se modifica.
 ****/
bool isEmptyListP(tListP L) {
    return (L == NULLP);
}

/****
 * Objetivo: Obtener la posición del primer elemento de la lista.
 * Entradas:
 *   - L: lista de proyectos.
 * Salidas: posición del primer elemento, o NULLP si la lista está vacía.
 * Precondiciones: L debe estar inicializada.
 * Postcondiciones: L no se modifica.
 ****/
tPosP firstP(tListP L) {
    return L;
}

/****
 * Objetivo: Obtener la posición del último elemento de la lista.
 * Entradas:
 *   - L: lista de proyectos.
 * Salidas: posición del último elemento, o NULLP si la lista está vacía.
 * Precondiciones: L debe estar inicializada.
 * Postcondiciones: L no se modifica.
 ****/
tPosP lastP(tListP L) {
    tPosP p; /* Puntero auxiliar para recorrer la lista */

    if (L == NULLP)
        return NULLP;

    p = L;
    while (p->next != NULLP)
        p = p->next;

    return p;
}

/****
 * Objetivo: Obtener la posición siguiente a una posición dada.
 * Entradas:
 *   - p: posición actual (debe ser válida en L).
 *   - L: lista de proyectos (no utilizada; incluida por consistencia de interfaz).
 * Salidas: posición siguiente a p, o NULLP si p es el último elemento.
 * Precondiciones: p debe ser una posición válida en L.
 * Postcondiciones: L no se modifica.
 ****/
tPosP nextP(tPosP p, tListP L) {
    return p->next;
}

/****
 * Objetivo: Obtener la posición anterior a una posición dada.
 * Entradas:
 *   - p: posición actual (debe ser válida en L).
 *   - L: lista de proyectos.
 * Salidas: posición anterior a p, o NULLP si p es el primer elemento.
 * Precondiciones: p debe ser una posición válida en L.
 * Postcondiciones: L no se modifica.
 ****/
tPosP previousP(tPosP p, tListP L) {
    tPosP q; /* Puntero auxiliar para localizar el nodo anterior */

    if (p == L)
        return NULLP;

    q = L;
    while (q->next != p)
        q = q->next;

    return q;
}

/****
 * Objetivo: Reservar memoria para un nuevo nodo de la lista de proyectos.
 * Entradas:
 *   - p: puntero donde se almacenará la dirección del nodo creado.
 * Salidas: true si la reserva fue correcta; false si no hay memoria disponible.
 * Precondiciones: p debe ser un puntero válido.
 * Postcondiciones: Si devuelve true, *p apunta a un nodo con memoria reservada.
 ****/
bool createNodeP(tPosP *p) {
    *p = malloc(sizeof(tNodeP));
    return (*p != NULLP);
}

/****
 * Objetivo: Insertar un elemento en la lista de forma ordenada por projectName.
 * Entradas:
 *   - d: elemento (tItemP) a insertar.
 *   - L: puntero a la lista de proyectos.
 * Salidas: true si la inserción fue correcta; false si no hay memoria disponible.
 * Precondiciones: L debe estar inicializada.
 * Postcondiciones: El elemento queda insertado en orden alfabético ascendente
 *   por projectName. Las posiciones de los elementos posteriores al insertado
 *   pueden haber variado.
 ****/
bool insertItemP(tItemP d, tListP *L) {
    tPosP newNode; /* Nuevo nodo a insertar */
    tPosP p;       /* Puntero para localizar la posición de inserción */
    tPosP prev;    /* Puntero al nodo anterior a la posición de inserción */

    if (!createNodeP(&newNode))
        return false;

    newNode->data = d;
    newNode->next = NULLP;

    /* Buscar la posición de inserción para mantener el orden */
    p = *L;
    prev = NULLP;
    while (p != NULLP && strcmp(p->data.projectName, d.projectName) < 0) {
        prev = p;
        p = p->next;
    }

    newNode->next = p;

    if (prev == NULLP)
        *L = newNode;         /* Insertar al principio */
    else
        prev->next = newNode; /* Insertar en posición intermedia o al final */

    return true;
}

/****
 * Objetivo: Eliminar el elemento en la posición indicada de la lista.
 * Entradas:
 *   - p: posición del elemento a eliminar (debe ser válida).
 *   - L: puntero a la lista de proyectos.
 * Salidas: ninguna.
 * Precondiciones: p debe ser una posición válida en L.
 * Postcondiciones: El nodo es eliminado y su memoria liberada.
 ****/
void deleteAtPositionP(tPosP p, tListP *L) {
    tPosP prev; /* Puntero al nodo anterior al que se desea eliminar */

    if (p == *L) {
        *L = (*L)->next;
    } else {
        prev = previousP(p, *L);
        prev->next = p->next;
    }

    free(p);
}

/****
 * Objetivo: Obtener el elemento almacenado en una posición de la lista.
 * Entradas:
 *   - p: posición del elemento (debe ser válida).
 *   - L: lista de proyectos (no utilizada; incluida por consistencia de interfaz).
 * Salidas: copia del elemento (tItemP) almacenado en p.
 * Precondiciones: p debe ser una posición válida en L.
 * Postcondiciones: L no se modifica.
 ****/
tItemP getItemP(tPosP p, tListP L) {
    return p->data;
}

/****
 * Objetivo: Actualizar el elemento almacenado en una posición de la lista.
 * Entradas:
 *   - d: nuevo valor del elemento.
 *   - p: posición a modificar (debe ser válida).
 *   - L: puntero a la lista de proyectos (no utilizado; incluido por consistencia).
 * Salidas: ninguna.
 * Precondiciones: p debe ser una posición válida en L.
 * Postcondiciones: El campo data del nodo p queda reemplazado por d.
 ****/
void updateItemP(tItemP d, tPosP p, tListP *L) {
    p->data = d;
}

/****
 * Objetivo: Buscar un proyecto por su nombre aprovechando el orden de la lista.
 *   La búsqueda se detiene en cuanto el nombre del nodo actual supera
 *   alfabéticamente al buscado, sin necesidad de recorrer la lista entera.
 * Entradas:
 *   - name: nombre del proyecto a buscar.
 *   - L: lista de proyectos.
 * Salidas: posición del proyecto si se encuentra; NULLP si no existe.
 * Precondiciones: L debe estar inicializada.
 * Postcondiciones: L no se modifica.
 ****/
tPosP findItemP(tProjectName name, tListP L) {
    tPosP p; /* Puntero para recorrer la lista */

    p = L;
    while (p != NULLP && strcmp(p->data.projectName, name) < 0)
        p = p->next;

    if (p != NULLP && strcmp(p->data.projectName, name) == 0)
        return p;

    return NULLP;
}