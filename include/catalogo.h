/****************************************************
 * @brief Cria um novo catálogo
 *
 * @return ok
 ****************************************************/
ReturnCode criaCatalogo(void *ptr);

/****************************************************
 * @brief Insere um novo jogo no catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @param nome Nome do jogo
 * @param data Data de lançamento do jogo
 * @return ok, erro_alocacao, formato_invalido
 ****************************************************/
ReturnCode insereJogoCatalogo(Catalogo *catalogo_antigo, char *nome, int dia, int mes, int ano);

/****************************************************
 * @brief Imprime o catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 *
 * @return ok, ok_vazio
 ****************************************************/
ReturnCode imprimeCatalogo(Catalogo *catalogo);

/****************************************************
 * @brief Libera a memória alocada pelo catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @return ok, ou causa segfault -> free()
 ****************************************************/
ReturnCode liberaCatalogo(Catalogo *catalogo);

/****************************************************
 * @brief Busca um jogo no catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @param nome Nome do jogo
 * @param returnval Ponteiro para o jogo encontrado
 * @return ok, ok_jogo_nao_encontrado
 ****************************************************/
ReturnCode buscaJogoCatalogo(Catalogo *catalogo, char *nome, void *returnval);

/****************************************************
 * @brief Remove um jogo do catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @param nome Nome do jogo
 * @return ok, ok_jogo_nao_encontrado
 ****************************************************/
ReturnCode removeJogoCatalogo(Catalogo *catalogo, char *nome);

/****************************************************
 * @brief Retorna o tamanho do catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @param rettamanho Ponteiro para o tamanho
 * @return ok, ok_vazio
 ****************************************************/
ReturnCode tamanhoCatalogo(Catalogo *catalogo, int *rettamanho);
