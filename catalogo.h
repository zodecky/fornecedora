/**
 * @brief Representa uma data
 */
typedef struct data
{
    int dia;
    int mes;
    int ano;
} Data;

/**
 * @brief Um catálogo de jogos \n
 *
 * Internamente uma lista encadeada \n
 * Guarda um nome (malloc) e uma data\n
 *
 */
typedef struct catalogo
{
    char *nome;
    Data data_lancamento;
    struct catalogo *prox;
} Catalogo;

/**
 * @brief Cria um novo catálogo
 *
 * @param nome Nome do catálogo
 * @return Catalogo* Ponteiro para o catálogo criado
 */
Catalogo *criaCatalogo(char *nome);

/**
 * @brief Insere um novo jogo no catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @param nome Nome do jogo
 * @param data Data de lançamento do jogo
 * @return Catalogo* Ponteiro para o catálogo
 */