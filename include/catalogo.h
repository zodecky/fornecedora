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
 * @return Catalogo* Ponteiro para o catálogo criado
 */
Catalogo *criaCatalogo(void);

/**
 * @brief Insere um novo jogo no catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @param nome Nome do jogo
 * @param data Data de lançamento do jogo
 * @return Catalogo* Ponteiro para o catálogo
 */
Catalogo *insereJogoCatalogo(Catalogo *catalogo, char *nome, Data data);

/**
 * @brief Imprime o catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 */
void imprimeCatalogo(Catalogo *catalogo);

/**
 * @brief Libera a memória alocada pelo catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 */
void liberaCatalogo(Catalogo *catalogo);

/**
 * @brief Busca um jogo no catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @param nome Nome do jogo
 * @return Catalogo* Ponteiro para o jogo encontrado
 */
Catalogo *buscaJogoCatalogo(Catalogo *catalogo, char *nome);

/**
 * @brief Remove um jogo do catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @param nome Nome do jogo
 * @return Catalogo* Ponteiro para o catálogo
 */
Catalogo *removeJogoCatalogo(Catalogo *catalogo, char *nome);

/**
 * @brief Retorna o tamanho do catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @return int Tamanho do catálogo
 */
int tamanhoCatalogo(Catalogo *catalogo);
