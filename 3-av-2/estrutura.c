#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "estrutura.h"
#include "lista.h"
#include "cliente.h"
#include "node.h"

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

Estrutura *cria_estrutura()
{
    Estrutura *estrutura = (Estrutura *)malloc(sizeof(struct Estrutura_));

    if (estrutura == NULL)
    {
        printf("Nao foi possivel alocar memoria para Estrutura.\n");
        exit(1);
    }

    estrutura->clientes_por_nome = cria_lista_de_lista(256);
    estrutura->tamanho_clientes_por_nome = 256;
    estrutura->quantidade_clientes_por_nome = 0;

    estrutura->clientes_por_bairro = cria_lista_de_lista(256);
    estrutura->tamanho_clientes_por_bairro = 256;
    estrutura->quantidade_clientes_por_bairro = 0;

    int i;
    for (i = 0; i < estrutura->tamanho_clientes_por_nome; i++)
    {
        estrutura->clientes_por_nome[i] = cria_lista();
    }

    for (i = 0; i < estrutura->tamanho_clientes_por_bairro; i++)
    {
        estrutura->clientes_por_bairro[i] = cria_lista();
    }

    return estrutura;
}

void insere_cliente(Estrutura *estrutura, int criterio, Cliente *cliente)
{
    unsigned int indice;

    switch (criterio)
    {
    case 1:
        indice = hash_string(get_nome(cliente), estrutura->tamanho_clientes_por_nome);

        printf("1 - Indice: %d - Criterio: %d \n", indice, criterio);

        insere_cliente_na_lista(estrutura->clientes_por_nome[indice], cliente);

        estrutura->quantidade_clientes_por_nome++;
        break;
    case 2:
        indice = hash_string(get_bairro(cliente), estrutura->tamanho_clientes_por_bairro);

        printf("1 - Indice: %d - Criterio: %d \n", indice, criterio);

        insere_cliente_na_lista(estrutura->clientes_por_bairro[indice], cliente);

        estrutura->quantidade_clientes_por_bairro++;
        break;
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
    case 1:
    {
        if (busca == NULL)
            return lista_filtrada;

        indice_de_busca = hash_string(busca, estrutura->tamanho_clientes_por_nome);

        printf("2 - Indice de busca: %d", indice_de_busca);

        node = get_inicio(estrutura->clientes_por_nome[indice_de_busca]);
        while (node)
        {
            cliente = get_data(node);
            if (strcmp(get_nome(cliente), busca) == 0)
            {
                insere_cliente_na_lista(lista_filtrada, cliente);
            }
            node = get_next(node);
        }
        break;
    }
    case 2:
    {
        if (busca == NULL)
            return lista_filtrada;

        indice_de_busca = hash_string(busca, estrutura->tamanho_clientes_por_bairro);
        node = get_inicio(estrutura->clientes_por_bairro[indice_de_busca]);
        while (node)
        {
            cliente = get_data(node);
            if (strcmp(get_bairro(cliente), busca) == 0)
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
