#include <stdbool.h>
#include "cliente.h"

typedef struct Node_ Node;

Node *cria_node(Cliente *param_cliente, Node *param_next);
Cliente *get_data(Node *node);
Node *get_next(Node *node);
void set_next(Node *node, Node *next);
