#include <stdlib.h>
#include <string.h>
#include "tad.h"

// Um tipo abstrato de dados é um conjunto de dados e as operações que podem ser feitas sobre eles.
// Exemplo:
// chat, int, float, double, struct. Etc.

// Estrutura de dados homogênea -> Abriga valores de apenas um tipo. Exemplo: Array de int
// Estrutura de dados heterogênea -> Abriga valores de mais de um tipo. Exemplo: Struct

// Não precisa do _ no final. É convenção da linguagem para diferenciar do typedef (alias)
struct Person_ {
    char nome[20];
    char telefone[15];
}; // Poderia colocar o alias aqui, mas como já precisamos mesmo de um header, então já deixa no .h

// Semelhante a um construtor.
// Retorna um ponteiro, pois, será usado no main().
// Quando o main chama um struct que está declarado em um módulo separado, o compilador não tem a definição de quanto de memória será necessário para alocar para o struct, então dá um erro.
// Para corrigir este erro, ele exige que você faça usando ponteiro, pois aí, com ponteiros, você que se vire para gerenciar a memória. Então, por isso aqui retornamos um ponteiro.
// Os parâmetros não estão com char[] pois não é possível fazer isso por parâmetro. Então, declaramos com ponteiro também.
Person* create(char* nomeParametro, char* telefoneParametro) {
    // Cria um ponteiro com a quantidade de memória necessária:
    Person *person = (Person *) malloc(sizeof(struct Person_)); // OBS: Daria certo para fazer assim: Person person; Person *ponteiroPerson = &person. Mas aí, você gasta o dobro de variáveis. :P

    if(person != NULL) { // Verificar se o ponteiro é nulo, para caso o malloc não consiga alocar a memória suficiente devido memória sobrecarregada, etc.
        // Formas de acessar um membro de um struct ponteiro.
        // Precisa dessa função pois strings em C são array, e não dá pra atribuir um array em outro.
        // Essa função não leva em conta se o destino possui capacidade de memória alocada para copiar a string.
        strcpy(person -> nome, nomeParametro);
        strcpy((*person).telefone, telefoneParametro);
    }

    return person;
}

// Arrays dentro de um struct não pode ser retornado como ponteiro.
// Veja bem, quando você passar um Person por valor, uma cópia em outro local da memória é criada e alocada nesta função. Se você está retornando um ponteiro para este valor, isto é, você está retornando o endereço de p.nome, não vai dar certo, pois este endereço de memória é temporário, vivo somente durante a execução da função. 
// Por isso, você tem que passar o endereço da sua Person original, e o resultado devolvido será o endereço do array original. Só assim será possível nesse caso, se a devolução for um ponteiro.
// char* get_nome(Person p) {               <- essa função dá erro de compilação pelo motivo acima.
//     return p.nome;
// }

char* get_nome(Person *p) {
    return p->nome;
}

char* get_telefone(Person *p) {
    return p->telefone;
}
