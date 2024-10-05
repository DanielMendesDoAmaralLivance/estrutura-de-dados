#include <stdio.h>
#include <stdlib.h>
#include "requisicao.h"
#include "estrutura.h"

struct Estrutura_
{
    int quantidade;

    Requisicao *primeira_requisicao;
    Requisicao *ultima_requisicao;
};

Estrutura *create()
{
    Estrutura *estrutura = (Estrutura *)malloc(sizeof(struct Estrutura_));

    if (estrutura == NULL)
    {
        printf("Nao foi possivel alocar memoria para estrutura.");
        exit(1);
    }

    estrutura->quantidade = 0;
    estrutura->primeira_requisicao = NULL;
    estrutura->ultima_requisicao = NULL;

    return estrutura;
}

void inserir(Estrutura *estrutura, Requisicao *requisicao)
{
    if (estrutura->primeira_requisicao == NULL)
    {
        // Se ainda não existir nenhum elemento na fila, o novo elemento entrará como primeiro elemento da fila.
        estrutura->primeira_requisicao = requisicao;
    }
    else
    {
        // Se já existir 1 elemento na fila (que é tanto o primeiro como o último), o último elemento (até então) apontará para o novo elemento. Então, ficará ->
        // primeiro_elemento...ultimo_elemento->new_elemento. É assim que é configurado o proximo elemento do primeiro elemento.
        // E, claro, se já existir dois (ou mais) elementos na fila (por ex, 3), o primeiro elemento já saberá quem é o próximo, e temos o último também. Então, ficará:
        // p_elemento->prox_elemento...ultimo_elemento->new_elemento
        // E.. assim por diante.
        set_proximo_elemento(estrutura->ultima_requisicao, requisicao);
    }

    // Setamos o último elemento da fila aqui.
    estrutura->ultima_requisicao = requisicao;
    estrutura->quantidade++;
}

Requisicao *remover(Estrutura *estrutura)
{
    Requisicao *requisicao_a_ser_removida = estrutura->primeira_requisicao;
    if (requisicao_a_ser_removida != NULL)
    {
        estrutura->primeira_requisicao = get_proximo_elemento(estrutura->primeira_requisicao);

        estrutura->quantidade--;
        return requisicao_a_ser_removida;
    }
    else
    {
        printf("Estrutura nao contem nenhum elemento.");
        return NULL;
    }
}

void libera(Requisicao *requisicao)
{
    free(requisicao);
}

int get_size(Estrutura *estrutura)
{
    return estrutura->quantidade;
}
