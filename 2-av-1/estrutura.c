#include <stdlib.h>
#include "requisicao.h"
#include "estrutura.h"

struct Estrutura_
{
    Requisicao *primeira_requisicao;
    Requisicao *ultima_requisicao;
};

Estrutura *create()
{
    Estrutura *estrutura = (Estrutura *)malloc(sizeof(struct Estrutura_));

    if (estrutura == NULL)
    {
        exit(1);
    }

    return estrutura;
}

void inserir(Estrutura *estrutura, Requisicao *requisicao)
{
    if (estrutura->primeira_requisicao == NULL) // Isto é, se ainda não existir nenhum elemento na fila...
    {
        estrutura->primeira_requisicao = requisicao; // A requisição é apontada no primeiro elemento da fila.
    }
    else
    {
        set_proximo_elemento(estrutura->ultima_requisicao, requisicao);
    }

    estrutura->ultima_requisicao = requisicao;
}

int get_size(Estrutura *estrutura) {
    return sizeof(estrutura);
}
