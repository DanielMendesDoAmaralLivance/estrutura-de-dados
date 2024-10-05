#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "requisicao.h"

struct Requisicao_
{
    char nome[40];
    int inscricao;
    char procedimento[10];

    // Usado apenas internamente. Cada elemento guardará o endereço do próximo elemento da lista.
    Requisicao *proximo_elemento;
};

Requisicao *cria_requisicao(
    char *nome_parametro,
    int inscricao_parametro,
    char *procedimentoParametro)
{
    Requisicao *requisicao = (Requisicao *)malloc((sizeof(struct Requisicao_)));

    if (requisicao == NULL)
    {
        printf("Nao foi possivel alocar memoria para requisicao.");
        exit(1);
    }

    strcpy(requisicao->nome, nome_parametro);
    requisicao->inscricao = inscricao_parametro;
    strcpy(requisicao->procedimento, procedimentoParametro);
    requisicao->proximo_elemento = NULL; // Assim que é criado, ele não "aponta" para nenhum outro elemento.

    return requisicao;
}

char *get_nome(Requisicao *requisicao)
{
    return requisicao->nome;
}

int get_inscricao(Requisicao *requisicao)
{
    return requisicao->inscricao;
}

char *get_procedimento(Requisicao *requisicao)
{
    return requisicao->procedimento;
}

Requisicao *get_proximo_elemento(Requisicao *requisicao)
{
    return requisicao->proximo_elemento;
}

void set_proximo_elemento(Requisicao *requisicao_a_receber_proximo_elemento, Requisicao *proximo_elemento)
{
    requisicao_a_receber_proximo_elemento->proximo_elemento = proximo_elemento;
}
