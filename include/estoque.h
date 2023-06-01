#include <stdbool.h>

/**
 * @brief Estrutura de um estoque \n
 * Guarda um nome (malloc) e uma quantidade \n
 * Internamente uma lista encadeada ERRADOOO!!!!!! TODO: arrumar
 */
typedef struct estoque
{
    struct estoque *prox;
    char *nome;
    int quantidade;
} Estoque;

/**
 * @brief Cria um novo estoque
 *
 *
 * @param nome
 * @param quantidade
 * @return Estoque*
 */
Estoque *criaEstoque(void);

/**
 * @brief Insere um novo jogo no estoque
 *
 * @param estoque
 * @param nome
 * @param quantidade
 * @return Estoque*
 */
Estoque *insereJogoEstoque(Estoque *estoque_antigo, char *nome);

/**
 * @brief Imprime o estoque
 *
 * @param estoque
 */
void imprimeEstoque(Estoque *estoque);

/**
 * @brief Libera a memória alocada pelo estoque
 *
 * @param estoque
 */
void liberaEstoque(Estoque *estoque);

/**
 * @brief Busca um jogo no estoque
 *
 * @param estoque
 * @param nome
 * @return Estoque*
 */
Estoque *buscaJogoEstoque(Estoque *estoque, char *nome);

/**
 * @brief Remove um jogo do estoque
 *
 * @param estoque
 * @param nome
 * @return Estoque*
 */
Estoque *removeJogoEstoque(Estoque *estoque, char *nome);

/**
 * @brief Vende um jogo do estoque
 *
 * @param estoque
 * @param nome
 * @return Estoque*
 */
bool vendeJogoEstoque(Estoque *estoque, char *nome, int quantidade);

/**
 * @brief Compra um jogo para o estoque
 *
 * @param estoque
 * @param nome
 * @return Estoque*
 */
bool compraJogoEstoque(Estoque *estoque, char *nome, int quantidade);

/**
 * @brief Retorna a quantidade de jogos no estoque
 *
 * @param estoque
 * @return int
 */
int quantidadeJogosEstoque(Estoque *estoque);
