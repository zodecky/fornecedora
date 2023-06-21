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
 * @return ok, erro_alocacao, formato_invalido_quantidade_negativa
 ****************************************************/
ReturnCode insereJogoEstoque(char *nome, int quantidade);

/****************************************************
 * @brief Imprime o estoque ou uma mensagem de estoque vazio
 *
 * @return ReturnCode ok, ok_vazio
 ****************************************************/
ReturnCode imprimeEstoque(void);
ReturnCode liberaEstoque(void);
ReturnCode buscaJogoEstoque(char *nome, int *quantidade);
ReturnCode removeJogoEstoque(char *nome);
ReturnCode vendeJogoEstoque(char *nome, int quantidade);
ReturnCode compraJogoEstoque(char *nome, int quantidade);
ReturnCode tamanhoEstoque(int *rettamanho);