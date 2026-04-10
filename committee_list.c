/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Ali Abu-afash Nayef LOGIN 1: ali.nayef@udc.es
 * AUTHOR 2: Isabel Mª Teijido Bernal LOGIN 2: isabel.teijido@udc.es
 * GROUP: 4.2
 * DATE: 06 / 03 / 26
 */

#include "committee_list.h"
#include <string.h>

/****
 * Objetivo: Inicializar una lista de comités vacía.
 * Entradas:
 *   - L: puntero a la lista a inicializar.
 * Salidas: ninguna.
 * Precondiciones: L debe ser un puntero válido.
 * Postcondiciones: *L queda con lastPos = NULLC (lista vacía).
 ****/
void createEmptyListC(tListC *L) {
    L->lastPos = NULLC;
}

/****
 * Objetivo: Comprobar si la lista de comités está vacía.
 * Entradas:
 *   - L: lista de comités.
 * Salidas: true si está vacía; false en caso contrario.
 * Precondiciones: L debe estar inicializada.
 * Postcondiciones: L no se modifica.
 ****/
bool isEmptyListC(tListC L) {
    return (L.lastPos == NULLC);
}

/****
 * Objetivo: Obtener la posición del primer elemento de la lista.
 * Entradas:
 *   - L: lista de comités (no utilizada; incluida por consistencia de interfaz).
 * Salidas: posición 0 (primer índice del array).
 * Precondiciones: L debe estar inicializada y no estar vacía.
 * Postcondiciones: L no se modifica.
 ****/
tPosC firstC(tListC L) {
    return 0;
}

/****
 * Objetivo: Obtener la posición del último elemento de la lista.
 * Entradas:
 *   - L: lista de comités.
 * Salidas: índice del último elemento (lastPos), o NULLC si la lista está vacía.
 * Precondiciones: L debe estar inicializada.
 * Postcondiciones: L no se modifica.
 ****/
tPosC lastC(tListC L) {
    return L.lastPos;
}

/****
 * Objetivo: Obtener la posición siguiente a una posición dada.
 * Entradas:
 *   - p: posición actual (índice válido en la lista).
 *   - L: lista de comités.
 * Salidas: p+1 si no es el último; NULLC si p es el último elemento.
 * Precondiciones: p debe ser una posición válida en L.
 * Postcondiciones: L no se modifica.
 ****/
tPosC nextC(tPosC p, tListC L) {
    if (p == L.lastPos)
        return NULLC;
    return p + 1;
}

/****
 * Objetivo: Obtener la posición anterior a una posición dada.
 * Entradas:
 *   - p: posición actual (índice válido en la lista).
 *   - L: lista de comités (no utilizada; incluida por consistencia de interfaz).
 * Salidas: p-1 si no es el primero; NULLC si p es el primer elemento (0).
 * Precondiciones: p debe ser una posición válida en L.
 * Postcondiciones: L no se modifica.
 ****/
tPosC previousC(tPosC p, tListC L) {
    if (p == 0)
        return NULLC;
    return p - 1;
}

/****
 * Objetivo: Insertar un elemento en la lista de forma ordenada por committeeName.
 * Entradas:
 *   - d: elemento (tItemC) a insertar.
 *   - L: puntero a la lista de comités.
 * Salidas: true si la inserción fue correcta; false si la lista está llena.
 * Precondiciones: L debe estar inicializada.
 * Postcondiciones: El elemento queda insertado en orden alfabético ascendente
 *   por committeeName. Las posiciones de los elementos posteriores al insertado
 *   pueden haber cambiado de valor.
 ****/
bool insertItemC(tItemC d, tListC *L) {
    tPosC i;   /* Índice para desplazar elementos hacia la derecha */
    tPosC pos; /* Posición de inserción encontrada */

    if (L->lastPos == MAX_COMMITTEES - 1)
        return false;

    /* Localizar la posición de inserción para mantener el orden */
    pos = 0;
    while (pos <= L->lastPos && strcmp(L->data[pos].committeeName, d.committeeName) < 0)
        pos++;

    /* Desplazar los elementos posteriores una posición a la derecha */
    for (i = L->lastPos; i >= pos; i--)
        L->data[i + 1] = L->data[i];

    L->data[pos] = d;
    L->lastPos++;

    return true;
}

/****
 * Objetivo: Eliminar el elemento en la posición indicada de la lista.
 * Entradas:
 *   - p: posición del elemento a eliminar (índice válido).
 *   - L: puntero a la lista de comités.
 * Salidas: ninguna.
 * Precondiciones: p debe ser una posición válida en L y la lista de proyectos
 *   del comité en p debe estar vacía.
 * Postcondiciones: El elemento es eliminado; los elementos posteriores se
 *   desplazan una posición a la izquierda y lastPos decrece en 1.
 ****/
void deleteAtPositionC(tPosC p, tListC *L) {
    tPosC i; /* Índice para desplazar elementos hacia la izquierda */

    for (i = p; i < L->lastPos; i++)
        L->data[i] = L->data[i + 1];

    L->lastPos--;
}

/****
 * Objetivo: Obtener el elemento almacenado en una posición de la lista.
 * Entradas:
 *   - p: posición del elemento (índice válido).
 *   - L: lista de comités.
 * Salidas: copia del elemento (tItemC) almacenado en p.
 * Precondiciones: p debe ser una posición válida en L.
 * Postcondiciones: L no se modifica.
 ****/
tItemC getItemC(tPosC p, tListC L) {
    return L.data[p];
}

/****
 * Objetivo: Actualizar el elemento almacenado en una posición de la lista.
 * Entradas:
 *   - d: nuevo valor del elemento.
 *   - p: posición a modificar (índice válido).
 *   - L: puntero a la lista de comités.
 * Salidas: ninguna.
 * Precondiciones: p debe ser una posición válida en L.
 * Postcondiciones: El elemento en p queda reemplazado por d.
 ****/
void updateItemC(tItemC d, tPosC p, tListC *L) {
    L->data[p] = d;
}

/****
 * Objetivo: Buscar un comité por su nombre aprovechando el orden de la lista.
 *   La búsqueda se detiene en cuanto el nombre del elemento actual supera
 *   alfabéticamente al buscado, sin necesidad de recorrer la lista entera.
 * Entradas:
 *   - name: nombre del comité a buscar.
 *   - L: lista de comités.
 * Salidas: posición del comité si se encuentra; NULLC si no existe.
 * Precondiciones: L debe estar inicializada.
 * Postcondiciones: L no se modifica.
 ****/
tPosC findItemC(tCommitteeName name, tListC L) {
    tPosC i; /* Índice para recorrer la lista */

    i = 0;
    while (i <= L.lastPos && strcmp(L.data[i].committeeName, name) < 0)
        i++;

    if (i <= L.lastPos && strcmp(L.data[i].committeeName, name) == 0)
        return i;

    return NULLC;
}