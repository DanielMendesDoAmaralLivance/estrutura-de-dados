#include <stdbool.h>

typedef struct Cliente_ Cliente;

Cliente *cria_cliente(char *param_nome, char *param_bairro, int param_pessoas, bool param_criancas, double param_renda);
char *get_nome(Cliente *cliente);
char *get_bairro(Cliente *cliente);
int get_pessoas(Cliente *cliente);
bool get_criancas(Cliente *cliente);
double get_renda(Cliente *cliente);
