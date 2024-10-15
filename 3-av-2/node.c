#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "cliente.h"

struct Node_
{
    Cliente *cliente;
    Node *next;
};

Node *cria_node(Cliente *param_cliente, Node *param_next)
{
    Node *node = (Node *)malloc(sizeof(struct Node_));

    if (node == NULL)
    {
        printf("Nao foi possivel alocar memoria para Node.\n");
        exit(1);
    }

    node->cliente = param_cliente;
    node->next = param_next;

    return node;
}

Cliente *get_data(Node *node)
{
    return node->cliente;
}

Node *get_next(Node *node)
{
    return node->next;
}

void set_next(Node *node, Node *next)
{
    node->next = next;
}
