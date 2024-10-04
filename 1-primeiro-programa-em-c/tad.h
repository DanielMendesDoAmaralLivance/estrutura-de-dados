// Este é o header.
// As assinaturas são incluídas no código principal.
// Em seguida, as implmenetações são também.

// codigo.c -> Arquivo de código em c, que será compilado.
// header.h -> Arquivo de header que expõe assinaturas. Interface.
// codigo.c sem main() -> Arquivo de código em c, que não pode ser executado diretamente. Módulo.
// object.o -> Módulo.
// assembly.s -> Arquivo .c que não passou por todas as etapas de compilação.

// Compilar módulo: gcc -c modulo.c
// Compilar módulo no programa principal: gcc programa.c modulo.o -o nome
// Compilar programa principal sem antes compilar o módulo (não recomendável, é bom ir por etapas para entender se der erro): gcc programa.c modulo.c -o nome

// Adiciona um alias para Person_ que será Person
typedef struct Person_ Person;

Person* create(char* nomeParametro, char* telefoneParametro);
char* get_nome(Person *p);
char* get_telefone(Person *p);