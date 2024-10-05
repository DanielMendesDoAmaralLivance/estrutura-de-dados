typedef struct Requisicao_ Requisicao;

Requisicao *cria_requisicao(
    char *nome_parametro,
    int inscricao_parametro,
    char *procedimentoParametro);
char *get_nome(Requisicao *requisicao);
int get_inscricao(Requisicao *requisicao);
char *get_procedimento(Requisicao *requisicao);
Requisicao *get_proximo_elemento(Requisicao *requisicao);
void set_proximo_elemento(Requisicao *requisicao_a_receber_proximo_elemento, Requisicao *proximo_elemento);
