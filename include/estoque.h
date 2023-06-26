#include "codes.h"

/****************************************************
 * @brief Cria o estoque
 *
 * @return ok
 ****************************************************/
ReturnCode criaEstoque(void);

/****************************************************
 * @brief Insere jogo no estoque
 *
 * @param nome nome do jogo
 * @param quantidade quantidade do jogo
 *
 * @return ok, erro_alocacao, formato_invalido_quantidade_negativa
 ****************************************************/
ReturnCode insereJogoEstoque(char *nome, int quantidade);

/****************************************************
 * @brief Imprime o estoque ou uma mensagem de estoque vazio
 *
 * @return ok, ok_vazio
 ****************************************************/
ReturnCode imprimeEstoque(void);

/****************************************************
 * @brief Libera memória do estoque
 *
 * @return ok
 ****************************************************/
ReturnCode liberaEstoque(void);

/****************************************************
 * @brief Busca jogo no estoque e passa a quantidade por referência
 *
 * @param nome nome do jogo
 * @param quantidade ponteiro para quantidade do jogo
 *
 * @return ok, ok_jogo_nao_encontrado
 ****************************************************/
ReturnCode buscaJogoEstoque(char *nome, int *quantidade);

/****************************************************
 * @brief Remove jogo no estoque
 *
 * @param nome nome do jogo
 *
 * @return ok, ok_jogo_nao_encontrado
 ****************************************************/
ReturnCode removeJogoEstoque(char *nome);

/****************************************************
 * @brief Vende jogo no estoque
 *
 * @param nome nome do jogo
 * @param quantidade quantidade do jogo
 *
 * @return ok, ok_jogo_nao_encontrado, ok_quantidade_insuficiente
 ****************************************************/
ReturnCode vendeJogoEstoque(char *nome, int quantidade);

/****************************************************
 * @brief Compra jogo no estoque
 *
 * @param nome nome do jogo
 * @param quantidade quantidade do jogo
 *
 * @return ok, erro_alocacao, formato_invalido_quantidade_negativa
 ****************************************************/
ReturnCode compraJogoEstoque(char *nome, int quantidade);

/****************************************************
 * @brief Retorna o tamanho do estoque
 *
 * @param rettamanho tamanho do estoque
 *
 * @return ok, erro_alocacao, formato_invalido_quantidade_negativa
 ****************************************************/
ReturnCode tamanhoEstoque(int *rettamanho);