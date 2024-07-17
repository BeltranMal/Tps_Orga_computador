#include "lib.h"

funcCmp_t *getCompareFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcCmp_t *)&intCmp;
        break;
    case TypeString:
        return (funcCmp_t *)&strCmp;
        break;
    case TypeCard:
        return (funcCmp_t *)&cardCmp;
        break;
    default:
        break;
    }
    return 0;
}
funcClone_t *getCloneFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcClone_t *)&intClone;
        break;
    case TypeString:
        return (funcClone_t *)&strClone;
        break;
    case TypeCard:
        return (funcClone_t *)&cardClone;
        break;
    default:
        break;
    }
    return 0;
}
funcDelete_t *getDeleteFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcDelete_t *)&intDelete;
        break;
    case TypeString:
        return (funcDelete_t *)&strDelete;
        break;
    case TypeCard:
        return (funcDelete_t *)&cardDelete;
        break;
    default:
        break;
    }
    return 0;
}
funcPrint_t *getPrintFunction(type_t t)
{
    switch (t)
    {
    case TypeInt:
        return (funcPrint_t *)&intPrint;
        break;
    case TypeString:
        return (funcPrint_t *)&strPrint;
        break;
    case TypeCard:
        return (funcPrint_t *)&cardPrint;
        break;
    default:
        break;
    }
    return 0;
}

/** Int **/

int32_t intCmp(int32_t *a, int32_t *b)
{
    if (*a > *b)
    {
        return -1;
    }
    else if (*a < *b)
    {
        return 1;
    }
    return 0;
}

void intDelete(int32_t *a)
{
    free(a);
}

void intPrint(int32_t *a, FILE *pFile)
{
    fprintf(pFile, "%d", *a);
}

int32_t *intClone(int32_t *a)
{
    int32_t *clone = (int32_t *)malloc(sizeof(int32_t));
    *clone = *a;
    return clone;
}

/** Lista **/

list_t *listNew(type_t t)
{
    list_t *nuevaLista = (list_t *)malloc(sizeof(list_t));
    nuevaLista->type = t;
    nuevaLista->size = 0;
    nuevaLista->first = 0;
    nuevaLista->last = 0;
    return nuevaLista;
}

uint8_t listGetSize(list_t *l)
{
    return l->size;
}

void *listGet(list_t *l, uint8_t i)
{
    if (i >= listGetSize(l))
    {
        return 0;
    }

    listElem_t *aux = l->first;
    for (uint8_t pos = 0; pos < i; pos++)
    {
        aux = aux->next;
    }
    return aux->data;
}

void listAddFirst(list_t *l, void *data)
{
    listElem_t *nodoNuevo = (listElem_t *)malloc(sizeof(listElem_t));
    funcClone_t *clonador = getCloneFunction(l->type);
    nodoNuevo->data = clonador(data);

    if (l->size == 0)
    {
        l->last = nodoNuevo;
    }
    else
    {
        nodoNuevo->next = l->first;
        l->first->prev = nodoNuevo;
    }

    l->first = nodoNuevo;
    l->size++;
}

void listAddLast(list_t *l, void *data)
{
    listElem_t *nodoNuevo = (listElem_t *)malloc(sizeof(listElem_t));
    funcClone_t *clonador = getCloneFunction(l->type);
    nodoNuevo->data = clonador(data);

    if (l->size == 0)
    {
        l->first = nodoNuevo;
    }
    else
    {
        nodoNuevo->prev = l->last;
        l->last->next = nodoNuevo;
    }

    l->last = nodoNuevo;
    l->size++;
}

void *listRemove(list_t *l, uint8_t i)
{
    uint8_t tamanio = listGetSize(l); // saca  tamaño
    if (i >= tamanio) // fuera de rango
    {
        return 0;
    }

    listElem_t *aux = l->first; //saca el first element
    for (uint8_t pos = 0; pos < i; pos++)//buscamos elemento
    {
        aux = aux->next;
    }

    void *dato = listGet(l,i);

    if (i == tamanio - 1)
    {
        l->last = aux->prev;

    }
    else if (i == 0)
    {
        l->first = aux->next;
        l->first->prev = NULL;
    }
    else
    {
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
    }
    
    free(aux );
    l->size--;
    return dato;
}
// Invierte el contenido del i-esimo elemento con el j-esimo elemento de la lista. Si alguno de los dos
// indices se encuentra fuera de rango, no realiza ninguna accion.
void listSwap(list_t *l, uint8_t i, uint8_t j)
{
    if (i == j)
    {
        return;
    }

    if ((i >= l->size || j >= l->size))
    {
        return;
    }

    listElem_t *nodoA = l->first;
    listElem_t *nodoB = l->first;
    while (i > 0 || j > 0)
    {
        if (i > 0)
        {
            nodoA = nodoA->next;
            i--;
        }

        if (j > 0)
        {
            nodoB = nodoB->next;
            j--;
        }
    }

    void *datoAux = nodoA->data;
    nodoA->data = nodoB->data;
    nodoB->data = datoAux;
}

list_t *listClone(list_t *l)
{
    list_t *clonLista = listNew(l->type);
    clonLista->first = l->first;
    for (uint8_t i = 0; i < l->size; i++)
    {
        listAddLast(clonLista, listGet(l, i));
    }
    clonLista->last = l->last;
    clonLista->size = l->size;
    return clonLista;
}

void listDelete(list_t *l)
{
    uint8_t tamanio = listGetSize(l);
    funcDelete_t *eliminador = getDeleteFunction(l->type);
    for (uint8_t i = 0; i < tamanio; i++)
    {
        eliminador(listRemove(l, 0));
    }
    free(l);
}

void listPrint(list_t *l, FILE *pFile)
{
    funcPrint_t *printeador = getPrintFunction(l->type);
    fprintf(pFile, "[");
    uint8_t size = listGetSize(l);
    for (uint8_t i = 0; i < size; i++)
    {
        printeador(listGet(l, i), pFile);
        if (i + 1 < size)
        {
            fprintf(pFile, ",");
        }
    }
    fprintf(pFile, "]");
}

/** Game **/

game_t *gameNew(void *cardDeck, funcGet_t *funcGet, funcRemove_t *funcRemove, funcSize_t *funcSize, funcPrint_t *funcPrint, funcDelete_t *funcDelete)
{
    game_t *game = (game_t *)malloc(sizeof(game_t));
    game->cardDeck = cardDeck;
    game->funcGet = funcGet;
    game->funcRemove = funcRemove;
    game->funcSize = funcSize;
    game->funcPrint = funcPrint;
    game->funcDelete = funcDelete;
    return game;
}
int gamePlayStep(game_t *g)
{
    int applied = 0;
    uint8_t i = 0;
    while (applied == 0 && i + 2 < g->funcSize(g->cardDeck))
    {
        card_t *a = g->funcGet(g->cardDeck, i);
        card_t *b = g->funcGet(g->cardDeck, i + 1);
        card_t *c = g->funcGet(g->cardDeck, i + 2);
        if (strCmp(cardGetSuit(a), cardGetSuit(c)) == 0 || intCmp(cardGetNumber(a), cardGetNumber(c)) == 0)
        {
            card_t *removed = g->funcRemove(g->cardDeck, i);
            cardAddStacked(b, removed);
            cardDelete(removed);
            applied = 1;
        }
        i++;
    }
    return applied;
}
uint8_t gameGetCardDeckSize(game_t *g)
{
    return g->funcSize(g->cardDeck);
}
void gameDelete(game_t *g)
{
    g->funcDelete(g->cardDeck);
    free(g);
}
void gamePrint(game_t *g, FILE *pFile)
{
    g->funcPrint(g->cardDeck, pFile);
}
