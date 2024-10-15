#include "lista.h"
#include "cliente.h"

typedef struct Estrutura_ Estrutura;

Estrutura *cria_estrutura();
void insere_cliente(Estrutura *estrutura, int criterio, Cliente *cliente);
Lista *recupera_cliente(Estrutura *estrutura, int criterio, int complemento, const char *busca);
