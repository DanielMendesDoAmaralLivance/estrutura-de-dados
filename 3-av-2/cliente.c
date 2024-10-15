#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cliente.h"

struct Cliente_
{
    char nome[41];
    char bairro[41];
    int pessoas;
    bool criancas;
    double renda;
};

Cliente *cria_cliente(char *param_nome, char *param_bairro, int param_pessoas, bool param_criancas, double param_renda)
{
    Cliente *cliente = (Cliente *)malloc(sizeof(struct Cliente_));

    if (cliente == NULL)
    {
        printf("Nao foi possivel alocar memoria para Cliente.\n");
        exit(1);
    }

    strcpy(cliente->nome, param_nome);
    strcpy(cliente->bairro, param_bairro);
    cliente->pessoas = param_pessoas;
    cliente->criancas = param_criancas;
    cliente->renda = param_renda;

    return cliente;
}

char *get_nome(Cliente *cliente)
{
    return cliente->nome;
}

char *get_bairro(Cliente *cliente)
{
    return cliente->bairro;
}

int get_pessoas(Cliente *cliente)
{
    return cliente->pessoas;
}

bool get_criancas(Cliente *cliente)
{
    return cliente->criancas;
}

double get_renda(Cliente *cliente)
{
    return cliente->renda;
}
