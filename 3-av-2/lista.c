#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "node.h"
#include "cliente.h"

struct Lista_
{
    Node *inicio;

    int quantidade;
};

Lista **cria_lista_de_lista(int quantidade)
{
    Lista **lista_de_lista = (Lista **)malloc(sizeof(struct Lista_) * quantidade);

    if (lista_de_lista == NULL)
    {
        printf("Nao foi possivel alocar memoria para ponteiros de ponteiros de Lista.\n");
        exit(1);
    }

    return lista_de_lista;
}

Lista *cria_lista()
{
    Lista *lista = (Lista *)malloc(sizeof(struct Lista_) * 256);

    if (lista == NULL)
    {
        printf("Nao foi possivel alocar memoria para lista.\n");
        exit(1);
    }

    lista->inicio = NULL;
    lista->quantidade = 0;

    return lista;
}

void insere_cliente_na_lista(Lista *lista, Cliente *cliente)
{
    Node *node = cria_node(cliente, lista->inicio);
    set_next(node, lista->inicio);

    lista->inicio = node;
    lista->quantidade++;
}

Node *get_inicio(Lista *lista)
{
    return lista->inicio;
}

int get_quantidade(Lista *lista)
{
    return lista->quantidade;
}
