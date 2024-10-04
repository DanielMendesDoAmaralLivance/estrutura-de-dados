#include <stdio.h>
#include <stdlib.h> // inclui malloc
#include "tad.h" // Se for módulo do c, use <>, se não, use ""

// Um ponteiro é um apontador, ou indicador, para um endereço de memória.
// Basicamente, ele é uma variável utilizada para conter endereços de memória. E com isso, conseguimos utilizar os ponteiros para atualizar valores destes endereços de forma indireta.

// Os ponteiros podem ser usados com TODOS os tipos de dados da linguagem C.
// O c ignora os espaços no símbolo de ponteiro. Então, são ponteiros:
// int* p; int * p; int *p;

void soma(int a, int b, int *resultado)
{
    printf("O valor da variavel que esta no endereco %p e %d. Atualizando...\n", resultado, *resultado);

    // *resultado -> O valor ao qual o ponteiro aponta.
    *resultado = a + b;
    printf("O valor da variavel que esta no endereco %p agora e %d.\n", resultado, *resultado);
}

int main()
{
    // Por mais que "Daniel" tenha 6 bytes, precisamos alocar 7, pois senão, não sobraria espaço para o caractere nulo. \0
    // Em C, as strings são arrays de char terminados com o caracatere nulo \0.
    // Este caractere nulo é automáticamente inserido.
    // Outra maneira de declarar uma string, seria assim: char string[] = "Daniel". Aqui, automaticamente está reservado o espaço para "Daniel" e para o caractere nulo. O tamanho do array é calculado automaticamente.
    char string[7] = "Daniel";

    // %c\n -> %s é um marcador de posição para vários caracteres (string) e \n quebra a linha.
    printf("Conteudo de string: %s\n", string);
    // %p -> Marcador de posição para um ponteiro.
    // & -> Operador para pegar o endereço de memória (em hexadecimal). OBS: Endereço apenas do primeiro caractere. Explicado mais abaixo.
    printf("Endereco de string: %p\n", &string);

    // *nomeDaVariavel -> Cria um ponteiro.
    // Todo array é um ponteiro.
    // O nome do array já indica a primeira posição na memória para o array, ao passo que as posições subsequentes são calculadas a partir do índice fornecido. É assim que se sabe qual endereço de memória você está tentando acessar no array, através deste cálculo.
    // Não precisamos atribuir ao ponteiro *ponteiroParaString o endereço de string com &string, pois o nome do array já indica endereço do primeiro elemento do array.
    char *ponteiroParaString = string;
    printf("Conteudo de string via ponteiro: %c\n", *ponteiroParaString);
    printf("Endereco de string via ponteiro: %p\n", ponteiroParaString);

    printf("-------------------------------------------------------\n");

    int a = 10;
    int b = 20;
    int resultado = 0;
    printf("Endereco de resultado: %p\n", &resultado);

    // &resultado -> O endereço de resultado.
    // Lá dentro, a função irá atribuir o valor de a + b no endereço onde o ponteiro aponta.
    soma(a, b, &resultado);
    printf("O valor de resultado e: %d\n", resultado);

    printf("-------------------------------------------------------\n");

    int numeros[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *ponteiroNumeros = numeros;

    // Todo array, é um ponteiro, mas um ponteiro constante. Ele não admite aritmética de vetores, pois quem irá lidar com a memória alocada pelo vetor será o próprio compilador, então, ele não nos deixa ter acesso a isso para evitar problemas. Caso utilizemos manipulação de vetores usando um vetor próprio, ele irá nos deixar utilizar a aritmética de ponteiros.

    printf("Percorrendo vetor com indice:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", numeros[i]);
    }

    printf("\nPercorrendo vetor com indice, mas utilizando o ponteiro:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", ponteiroNumeros[i]); // Não precisa do * pois o i já aponta para o endereço de memória especificado, fazendo o cálculo mencionado anteriormente.
    }

    printf("\nPercorrendo vetor com aritmetica de ponteiro utilizando o ponteiro:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", *ponteiroNumeros++); // A cada execução, somamos o número de bytes daquele tipo, e o ponteiro desloca na memória para o próximo elemento do array na memória. OBS: A cada soma, o ponteiro irá receber como novo valor o valor daquele endereço. Isso significa que, ao chamar novamente o ponteiro, ele não irá apontar para o endereço original, pois este foi alterado. Então, cabe a responsabilidade do desenvolvedor liberar memória, ou voltar no array. Por isso, não é possível fazer este ++ utilizando o vetor.
    }

    printf("\nVoltando 10 posicoes utilizando aritmetica de ponteiros:\n");
    ponteiroNumeros -= 10;
    for (int i = 0; i < 10; i++)
    {
        // OBS: *ponteiroNumeros++ incrementa a posição do ponteiro APÓS o valor ser acessado. E não incrementa o valor. Não confundir.
        // É como fazer: *ponteiroNumeros; ponteiroNumeros++; (acessa e incrementa depois).
        printf("%d ", *ponteiroNumeros++);
    }

    printf("\n-------------------------------------------------------\n");

    // Até então, usamos espaços de memória criados pelo próprio compilador. Exemplo: Ao declarar uma string, o compilador separa certinho a quantidade de memória necessária automaticamente.
    // Com malloc e ponteiros, podemos criar isso por conta própria.

    // malloc -> Memory Allocation

    int numerosComMemoriaCompilador[5] = {1, 2, 3, 4, 5};
    int *numerosComMemoriaProgramador = (int *)malloc(sizeof(int) * 5);
    // malloc retorna um ponteiro genérico (void *), então damos o cast para um ponteiro de inteiros.
    // Criamos para o ponteiro 5 endereços subsequentes reservados para int.
    // Exemplo: Se int tem 4 bytes, 5 terá 20 bytes, então alocamos 20 bytes para este ponteiro guardar 5 inteiros.
    // A vantagem disso, é que com as duas variáveis acima temos exatamente a mesma estrutura. Só que, com malloc, temos liberdade para navegar na memória, liberar, etc.

    // Atribui todos os valores do array ao ponteiro.
    for (int i = 0; i < 5; i++)
    {
        *numerosComMemoriaProgramador = numerosComMemoriaCompilador[i];
        numerosComMemoriaProgramador++;
    }
    // Volta.
    numerosComMemoriaProgramador -= 5;

    printf("\nnumerosComMemoriaCompilador:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", numerosComMemoriaCompilador[i]);
    }

    printf("\nnumerosComMemoriaProgramador:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", numerosComMemoriaProgramador[i]);
    }

    printf("\n-------------------------------------------------------\n");

    Person *person = create("Daniel", "+5511982039269");
    // printf("%s", person->name); 
    // Não dá pra fazer isso pois o header não expõe as propriedades do struct. Por isso tem aqueles métodos auxiliares. Tbm é bom para encapsulamento.
    printf("Nome: %s\n", get_nome(person));
    printf("Telefone: %s\n", get_telefone(person));

    return 0;
}
