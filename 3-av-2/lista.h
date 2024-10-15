#include <stdbool.h>
#include "cliente.h"
#include "node.h"

typedef struct Lista_ Lista;

Lista **cria_lista_de_lista(int quantidade);
Lista *cria_lista();
void insere_cliente_na_lista(Lista *lista, Cliente *cliente);
Node *get_inicio(Lista *lista);
int get_quantidade(Lista *lista);
