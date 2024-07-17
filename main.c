#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "lib.h"


char *suits[] = {"espada","oro", "copa", "basto", "comodin"};

void prueba_array()
{
    array_t *mazo = arrayNew(TypeCard, 5);

    for(int32_t i = 0; i < 5; i++)
    {
        card_t *c = cardNew(suits[i],&i);
        arrayAddLast(mazo,c);
    }
    arrayPrint(mazo, stdout);
    
    card_t *primer_carta = arrayGet(mazo, 4);
    card_t *carta_apilar = arrayGet(mazo,0);

    cardAddStacked(primer_carta, carta_apilar);
    arrayPrint(mazo, stdout);

    arrayDelete(mazo);
}

void prueba_list()
{
    list_t *mazo = listNew(TypeCard);

    for(int32_t i = 0; i < 5; i++)
    {
        card_t *c = cardNew(suits[i],&i);
        listAddLast(mazo,c);
    }
    listPrint(mazo, stdout);
    
    card_t *primer_carta = listGet(mazo, 1);
    card_t *carta_apilar = listGet(mazo,2);

    cardAddStacked(primer_carta, carta_apilar);
    listPrint(mazo, stdout);

    listDelete(mazo);
}

int main(void)
{
    prueba_array();
    prueba_list();
    return 0;
}
