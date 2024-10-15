#include <stdio.h>
#include "cliente.h"
#include "estrutura.h"
#include "lista.h"
#include "node.h"

void imprime(Cliente *cliente) {
    printf("Nome      ; %40s\nBairro    : %40s\nQ Pessoas : %40d\nCriancas  : %40s\nRenda     : %40.2f\n\n", get_nome(cliente), get_bairro(cliente), get_pessoas(cliente), get_criancas(cliente) == 0 ? "Nao": "Sim", get_renda(cliente));
}

int main() {
/*-------------------------------------------------------------------------------------------------
Criação de dez clientes para inserir na estrutura
-------------------------------------------------------------------------------------------------*/    
    Cliente *cliente[10];
    cliente[0] = cria_cliente("Alberto", "Centro", 3, 1, 4500.00);
    cliente[1] = cria_cliente("Bernardo", "Ingleses", 1, 0, 1800.00);
    cliente[2] = cria_cliente("Amarilis", "Trindade", 2, 0, 2980.00);
    cliente[3] = cria_cliente("Rodolfo", "Centro", 5, 1, 6500.00);
    cliente[4] = cria_cliente("Maria", "Trindade", 2, 1, 15800.00);
    cliente[5] = cria_cliente("Marta", "Trindade", 1, 0, 8000.00);
    cliente[6] = cria_cliente("Vanessa", "Centro", 3, 1, 8300.00);
    cliente[7] = cria_cliente("Gilberto", "Ingleses", 2, 0, 4000.00);
    cliente[8] = cria_cliente("Simone", "Centro", 1, 0, 5000.00);
    cliente[9] = cria_cliente("Antonio", "Trindade", 4, 1, 3500.00);
/*-------------------------------------------------------------------------------------------------
Criação da estrutura vazia
-------------------------------------------------------------------------------------------------*/
    Estrutura *estrutura = cria_estrutura(); 
    int i;
/*-------------------------------------------------------------------------------------------------
População das hashtables com os clientes criados:
1 - inserção na estrutura que usa o nome como chave
2 - inserção na estrutura que usa o bairro como chave
3 - inserção na estrutura que usa como chave a quantidade de pessoas na residência
4 - inserção na estrutura que usa como chave a presença de crianças menores de 5 anos
5 - inserção na estrutura que usa como chave a renda bruta familiar
-------------------------------------------------------------------------------------------------*/
    for(i = 0; i < 10; i++) {
        insere_cliente(estrutura, 1, cliente[i]);
        insere_cliente(estrutura, 2, cliente[i]);
        insere_cliente(estrutura, 3, cliente[i]);
        insere_cliente(estrutura, 4, cliente[i]);
        insere_cliente(estrutura, 5, cliente[i]);
    }
    printf("Inseridos na estrutura ...\n");
/*-------------------------------------------------------------------------------------------------
Recuperação de clientes usando nome como chave de busca
-------------------------------------------------------------------------------------------------*/
    Lista *lista = recupera_cliente(estrutura, 1, 0, "Vanessa");
    if(get_quantidade(lista) > 0) {
        printf("Clientes com nome Vanessa:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado com nome Vanessa!\n");
    }
    printf("-------------------------------------------\n\n");
    lista = recupera_cliente(estrutura, 1, 0, "Arthur");
    if(get_quantidade(lista) > 0) {
        printf("Clientes com nome Arthur:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado com nome Arthur!\n");
    }
    printf("-------------------------------------------\n\n");
/*-------------------------------------------------------------------------------------------------
Recuperação de clientes usando bairro como chave de busca
-------------------------------------------------------------------------------------------------*/
    lista = recupera_cliente(estrutura, 2, 0, "Centro");
    if(get_quantidade(lista) > 0) {
        printf("Cliente do Centro:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado do bairro Centro!\n");
    }
    printf("-------------------------------------------\n\n");
    lista = recupera_cliente(estrutura, 2, 0, "Ingleses");
    if(get_quantidade(lista) > 0) {
        printf("Clientes de Ingleses:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado do bairro Ingleses!\n");
    }
    printf("-------------------------------------------\n\n");
    lista = recupera_cliente(estrutura, 2, 0, "Trindade");
    if(get_quantidade(lista) > 0) {
        printf("Clientes da Trindade:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado do bairro Trindade!\n");
    }
    printf("-------------------------------------------\n\n");
/*-------------------------------------------------------------------------------------------------
Recuperação de clientes usando quantidade de pessoas como chave de busca
-------------------------------------------------------------------------------------------------*/
    lista = recupera_cliente(estrutura, 3, 1, NULL);
    if(get_quantidade(lista) > 0) {
        printf("Clientes com 1 pesswoa na residência:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado com 1 pessoa na residência!\n");
    }
    printf("-------------------------------------------\n\n");
    lista = recupera_cliente(estrutura, 3, 2, NULL);
    if(get_quantidade(lista) > 0) {
        printf("Clientes com 2 pessoas na residência:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado com 2 pessoas na residência!\n");
    }
    printf("-------------------------------------------\n\n");
    lista = recupera_cliente(estrutura, 3, 3, NULL);
    if(get_quantidade(lista) > 0) {
        printf("Clientes com 3 pessoas na residência:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado com 3 pessoas na residência!\n");
    }
    printf("-------------------------------------------\n\n");
    lista = recupera_cliente(estrutura, 3, 4, NULL);
    if(get_quantidade(lista) > 0) {
        printf("Clientes com 4 pessoas na residência:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado com 4 pessoas na residência!\n");
    }
    printf("-------------------------------------------\n\n");
    lista = recupera_cliente(estrutura, 3, 5, NULL);
    if(get_quantidade(lista) > 0) {
        printf("Clientes com 5 ou mais pessoas na redidência:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado com 5 ou mais pessoas na residência!\n");
    }
    printf("-------------------------------------------\n\n");
/*-------------------------------------------------------------------------------------------------
Recuperação de clientes usando a existência de menores de 5 anos como chave de busca
-------------------------------------------------------------------------------------------------*/
    lista = recupera_cliente(estrutura, 4, 0, NULL);
    if(get_quantidade(lista) > 0) {
        printf("Clientes que não possuem menores de 5 anos na residência:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado com 5 ou mais pessoas na residência!\n");
    }
    printf("-------------------------------------------\n\n");
    lista = recupera_cliente(estrutura, 4, 1, NULL);
    if(get_quantidade(lista) > 0) {
        printf("Clientes que possuem menores de 5 anos na residência:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado com 5 ou mais pessoas na residência!\n");
    }
    printf("-------------------------------------------\n\n");
/*-------------------------------------------------------------------------------------------------
Recuperação de clientes usando a faixa de renda bruta como chave de busca
-------------------------------------------------------------------------------------------------*/
    lista = recupera_cliente(estrutura, 5, 1, NULL);
    if(get_quantidade(lista) > 0) {
        printf("Clientes que possuerm renda de até 2000:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado com renda de até 2000!\n");
    }
    printf("-------------------------------------------\n\n");
    lista = recupera_cliente(estrutura, 5, 2, NULL);
    if(get_quantidade(lista) > 0) {
        printf("Clientes que possuerm renda de até 3000:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado com renda de até 3000!\n");
    }
    printf("-------------------------------------------\n\n");
    lista = recupera_cliente(estrutura, 5, 3, NULL);
    if(get_quantidade(lista) > 0) {
        printf("Clientes que possuerm renda de até 5000:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado com renda de até 5000!\n");
    }
    printf("-------------------------------------------\n\n");
    lista = recupera_cliente(estrutura, 5, 4, NULL);
    if(get_quantidade(lista) > 0) {
        printf("Clientes que possuerm renda maior que 5000:\n");
        Node *cursor = get_inicio(lista);
        while(cursor != NULL) {
            imprime(get_data(cursor));
            cursor = get_next(cursor);
        }
    } else {
        printf("Nenhum cliente recuperado com renda suoerior a 5000!\n");
    }
}