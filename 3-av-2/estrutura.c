#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "estrutura.h"
#include "lista.h"
#include "cliente.h"
#include "node.h"

#define HASH_TABLE_TAM_INICIAL 256
#define CRITERIO_NOME 1
#define CRITERIO_BAIRRO 2

struct Estrutura_
{
    Lista **clientes_por_nome;
    int tamanho_clientes_por_nome;
    int quantidade_clientes_por_nome;

    Lista **clientes_por_bairro;
    int tamanho_clientes_por_bairro;
    int quantidade_clientes_por_bairro;
};

unsigned int hash_string(const char *str, unsigned int tamanho)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash % tamanho;
}

void inicializar_hash_table(Lista **hash_table, int tamanho)
{
    int i;

    for (i = 0; i < tamanho; i++)
    {
        hash_table[i] = cria_lista();
    }
}

Estrutura *cria_estrutura()
{
    Estrutura *estrutura = (Estrutura *)malloc(sizeof(struct Estrutura_));

    if (estrutura == NULL)
    {
        printf("Nao foi possivel alocar memoria para Estrutura.\n");
        exit(1);
    }

    estrutura->tamanho_clientes_por_nome = HASH_TABLE_TAM_INICIAL;
    estrutura->clientes_por_nome = cria_lista_de_lista(estrutura->tamanho_clientes_por_nome);
    estrutura->quantidade_clientes_por_nome = 0;

    estrutura->tamanho_clientes_por_bairro = HASH_TABLE_TAM_INICIAL;
    estrutura->clientes_por_bairro = cria_lista_de_lista(estrutura->tamanho_clientes_por_bairro);
    estrutura->quantidade_clientes_por_bairro = 0;

    inicializar_hash_table(estrutura->clientes_por_nome, estrutura->tamanho_clientes_por_nome);

    inicializar_hash_table(estrutura->clientes_por_bairro, estrutura->tamanho_clientes_por_bairro);

    return estrutura;
}

void insere_cliente(Estrutura *estrutura, int criterio, Cliente *cliente)
{
    unsigned int indice;

    switch (criterio)
    {
    case CRITERIO_NOME:
        indice = hash_string(get_nome(cliente), estrutura->tamanho_clientes_por_nome);

        insere_cliente_na_lista(estrutura->clientes_por_nome[indice], cliente);

        estrutura->quantidade_clientes_por_nome++;
        break;
    case CRITERIO_BAIRRO:
        indice = hash_string(get_bairro(cliente), estrutura->tamanho_clientes_por_bairro);

        insere_cliente_na_lista(estrutura->clientes_por_bairro[indice], cliente);

        estrutura->quantidade_clientes_por_bairro++;
        break;
    default:
        printf("Criterio %d nao implementado. Pulando insercao de Cliente na Estrutura...\n", criterio);
        break;
    }
}

Lista *recupera_cliente(Estrutura *estrutura, int criterio, int complemento, const char *busca)
{
    Lista *lista_filtrada = cria_lista();
    Node *node;
    Cliente *cliente;

    unsigned int indice_de_busca;

    switch (criterio)
    {
    case CRITERIO_NOME:
    {
        if (busca == NULL)
            return lista_filtrada;

        indice_de_busca = hash_string(busca, estrutura->tamanho_clientes_por_nome);

        node = get_inicio(estrutura->clientes_por_nome[indice_de_busca]);
        while (node)
        {
            cliente = get_data(node);
            if (strcmp(get_nome(cliente), busca) == false)
            {
                insere_cliente_na_lista(lista_filtrada, cliente);
            }
            node = get_next(node);
        }
        break;
    }
    case CRITERIO_BAIRRO:
    {
        if (busca == NULL)
            return lista_filtrada;

        indice_de_busca = hash_string(busca, estrutura->tamanho_clientes_por_bairro);
        node = get_inicio(estrutura->clientes_por_bairro[indice_de_busca]);
        while (node)
        {
            cliente = get_data(node);
            if (strcmp(get_bairro(cliente), busca) == false)
            {
                insere_cliente_na_lista(lista_filtrada, cliente);
            }
            node = get_next(node);
        }
        break;
    }
    default:
        printf("Criterio %d nao implementado. Pulando recuperacao de Cliente na Estrutura...\n", criterio);
        break;
    }

    return lista_filtrada;
}
