#include "codes.h"

/****************************************************
 * @brief Cria um novo catálogo
 *
 * @return ok
 ****************************************************/
ReturnCode criaCatalogo(void);

/****************************************************
 * @brief Insere um novo jogo no catálogo
 *
 * @param nome Nome do jogo
 * @param dia Dia de lançamento do jogo
 * @param mes Mês de lançamento do jogo
 * @param ano Ano de lançamento do jogo
 * @param preco Preço do jogo
 *
 * @return ok, erro_alocacao, formato_invalido_dia_entre_1_e_31, formato_invalido_mes_entre_1_e_12, formato_invalido_ano_maior_que_0, formato_invalido_fevereiro_tem_28_dias, formato_invalido_meses_4_6_9_11_nao_possuem_dia_31, formato_invalido_dia_29_de_fevereiro_somente_existe_em_anos_bissextos
 *****************************************************/
ReturnCode insereJogoCatalogo(char *nome, int dia, int mes, int ano, float preco);

/****************************************************
 * @brief Imprime o catálogo: nome, data de lançamento e preço
 *
 * @return ok, ok_vazio
 ****************************************************/
ReturnCode imprimeCatalogo(void);

/****************************************************
 * @brief Libera a memória alocada pelo catálogo
 *
 * @return ok, ou causa segfault -> (se foi chamado free() antes da hora)
 ****************************************************/
ReturnCode liberaCatalogo(void);

/****************************************************
 * @brief Busca um jogo no catálogo
 *
 * @param nome Nome do jogo
 * @param dia Ponteiro para o dia de lançamento do jogo
 * @param mes Ponteiro para o mês de lançamento do jogo
 * @param ano Ponteiro para o ano de lançamento do jogo
 * @param preco Ponteiro para o preço do jogo
 *
 * @return ok, ok_jogo_nao_encontrado
 ****************************************************/
ReturnCode buscaJogoCatalogo(char *nome, int *dia, int *mes, int *ano, float *preco);

/****************************************************
 * @brief Remove um jogo do catálogo
 *
 * @param nome Nome do jogo
 *
 * @return ok, ok_jogo_nao_encontrado
 ****************************************************/
ReturnCode removeJogoCatalogo(char *nome);

/****************************************************
 * @brief Retorna o tamanho do catálogo
 *
 * @param rettamanho Ponteiro para o tamanho
 *
 * @return ok, ok_vazio
 ****************************************************/
ReturnCode tamanhoCatalogo(int *rettamanho);
