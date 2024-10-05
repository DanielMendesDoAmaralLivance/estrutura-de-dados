typedef struct Estrutura_ Estrutura;

Estrutura *create();
void inserir(Estrutura *estrutura, Requisicao *requisicao);
Requisicao *remover(Estrutura *estrutura);
void libera(Requisicao *requisicao);
int get_size(Estrutura *estrutura);
