#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "estrutura.h"
#include "lista.h"
#include "cliente.h"
#include "node.h"

#define HASH_TABLE_TAM_INICIAL 11
#define FATOR_CARGA_MAX 0.75f

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

float get_fator_carga(int quantidade_na_hash_table, int tamanho_da_hash_table)
{
    return (float)quantidade_na_hash_table / tamanho_da_hash_table;
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

void rehash_clientes(Estrutura *estrutura, Lista **hash_table_antiga, Lista **hash_table_nova, int tamanho_antigo, int tamanho_novo)
{
    for (int i = 0; i < tamanho_antigo; i++)
    {
        Node *node = get_inicio(hash_table_antiga[i]);
        while (node)
        {
            Cliente *cliente = get_data(node);
            unsigned int indice = hash_string(get_nome(cliente), tamanho_novo);
            insere_cliente_na_lista(hash_table_nova[indice], cliente);
            node = get_next(node);
        }
        free(hash_table_antiga[i]);
    }
}

void redimensionar(Estrutura *estrutura, int criterio)
{
    int tamanho_novo;
    Lista **hash_table_nova;
    int tamanho_antigo;
    Lista **hash_table_antiga;

    if (criterio == 1)
    {
        hash_table_antiga = estrutura->clientes_por_nome;
        tamanho_antigo = estrutura->tamanho_clientes_por_nome;
    }
    else if (criterio == 2)
    {
        hash_table_antiga = estrutura->clientes_por_bairro;
        tamanho_antigo = estrutura->tamanho_clientes_por_bairro;
    }

    tamanho_novo = (tamanho_antigo) * 2;
    hash_table_nova = cria_lista_de_lista(tamanho_novo);
    if (hash_table_nova == NULL)
    {
        printf("Erro ao redimensionar hash_table\n");
        exit(1);
    }

    inicializar_hash_table(hash_table_nova, tamanho_novo);
    rehash_clientes(estrutura, hash_table_antiga, hash_table_nova, tamanho_antigo, tamanho_novo);

    free(hash_table_antiga);

    if (criterio == 1)
    {
        estrutura->clientes_por_nome = hash_table_nova;
        estrutura->tamanho_clientes_por_nome = tamanho_novo;
    }
    else if (criterio == 2)
    {
        estrutura->clientes_por_bairro = hash_table_nova;
        estrutura->tamanho_clientes_por_bairro = tamanho_novo;
    }
}

void insere_cliente(Estrutura *estrutura, int criterio, Cliente *cliente)
{
    unsigned int indice;
    float fator_de_carga_inicial;

    switch (criterio)
    {
    case 1:
        fator_de_carga_inicial = get_fator_carga(estrutura->quantidade_clientes_por_nome, estrutura->tamanho_clientes_por_nome);

        if (fator_de_carga_inicial > FATOR_CARGA_MAX)
        {
            printf("Fator de carga muito alto (%.2f). Aumentando a capacidade da tabela.\n", fator_de_carga_inicial);
            redimensionar(estrutura, criterio);
            printf("Redimensionamento feito com sucesso. Fator de carga atual: %.2f\n", get_fator_carga(estrutura->quantidade_clientes_por_nome, estrutura->tamanho_clientes_por_nome));
        }

        indice = hash_string(get_nome(cliente), estrutura->tamanho_clientes_por_nome);

        insere_cliente_na_lista(estrutura->clientes_por_nome[indice], cliente);

        estrutura->quantidade_clientes_por_nome++;

        break;
    case 2:
        fator_de_carga_inicial = get_fator_carga(estrutura->quantidade_clientes_por_bairro, estrutura->tamanho_clientes_por_bairro);

        if (fator_de_carga_inicial > FATOR_CARGA_MAX)
        {
            printf("Fator de carga muito alto (%.2f). Aumentando a capacidade da tabela.\n", fator_de_carga_inicial);
            redimensionar(estrutura, criterio);
            printf("Redimensionamento feito com sucesso. Fator de carga atual: %.2f\n", get_fator_carga(estrutura->quantidade_clientes_por_bairro, estrutura->tamanho_clientes_por_bairro));
        }

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
    case 1:
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
    case 2:
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
