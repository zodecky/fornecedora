// REFAZER COMENT FUNCOES
/************************************************************
 *                          EXTERNOS                        *
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************
 *                         MODULOS                          *
 ************************************************************/
#include "../include/codes.h"
#include "../include/estoque.h"

/************************************************************
 *                         STRUCTS                          *
 ************************************************************/

/**
 * @brief Estrutura de um estoque \n
 * Guarda um nome (malloc) e uma quantidade \n
 * Internamente uma lista encadeada \n
 */
typedef struct estoque
{
    struct estoque *prox;
    int quantidade;
    char *nome;
} Estoque;

/************************************************************
 *                         GLOBAIS                          *
 ************************************************************/

static Estoque *g_estoque; // estoque global

/************************************************************
 *                         FUNÇÕES                          *
 ************************************************************/

/****************************************************
 * @brief Cria um novo estoque
 *
 * A função retorna NULL, para que ao inserir um jogo
 * ele aponte para um ponteiro nulo do "tipo" estoque.
 *muuint
 * @return Estoque*
 *
 * Caso 1: retorna null
 *
 *****************************************************/
ReturnCode criaEstoque(void)
{
    g_estoque = NULL;
    return ok;
}

/****************************************************
 * @brief Insere um novo jogo no estoque
 *
 * @param estoque Ponteiro para o estoque
 * @param nome Nome do jogo
 * @param quantidade Quantidade de jogos
 *
 * Primeiro a função aloca memória para o estoque,
 * depois aloca memória para o nome do jogo
 * e copia o nome passado como parâmetro para o nome do jogo.
 * Também adiciona a data de lançamento.
 *
 * @return ok, erro_alocacao, formato_invalido_quantidade_negativa
 *
 *****************************************************/
ReturnCode insereJogoEstoque(char *nome, int quantidade)
{
    if (quantidade < 0)
    {
        return formato_invalido_quantidade_negativa;
    }

    Estoque *estoque = (Estoque *)malloc(sizeof(Estoque));             // aloca memória para o estoque
    estoque->nome = (char *)malloc(sizeof(char) * (strlen(nome) + 1)); // +1 para o \0

    if (estoque == NULL || estoque->nome == NULL) // checa se a alocação foi bem sucedida
    {
        return erro_alocacao;
    }

    strcpy(estoque->nome, nome);      // copia o nome para o estoque
    estoque->quantidade = quantidade; // copia a data para o estoque
    estoque->prox = g_estoque;        // o próximo é o estoque anterior

    g_estoque = estoque;
    return ok;
}

/****************************************************
 * @brief Imprime o estoque
 *
 * A função percorre o estoque e imprime o nome e a data de lançamento
 * de cada jogo.
 *
 * @note A função não retorna nada, apenas imprime.
 *
 * @param estoque Ponteiro para o estoque
 *
 * 1: cria um ponteiro auxiliar para percorrer o estoque.
 * 2: enquanto o auxiliar não for nulo, imprime o nome e a data de lançamento.
 * 3: o auxiliar recebe o próximo jogo. (atualiza o ponteiro auxiliar)
 *
 *
 * Caso 1: O estoque está vazio -> imprime que o estoque está vazio.
 * Caso 2: O estoque não está vazio -> imprime o estoque.
 *****************************************************/
ReturnCode imprimeEstoque(void)
{
    Estoque *aux = g_estoque;
    if (aux == NULL)
    {
        printf("\x1b[31mO estoque esta vazio!\n\x1b[0m");
        return ok_vazio;
    }

    printf("\x1b[32m******** Imrpimindo o estoque *******\n\n\x1b[0m");
    while (aux != NULL)
    {
        printf("\x1b[34mNome: %s\n\x1b[0m", aux->nome);
        printf("\x1b[34mQuantidade: %d\n\n\x1b[0m", aux->quantidade);
        aux = aux->prox;
    }
    printf("\x1b[32m******** Fim da impressao *******\n\n\x1b[0m");
    return ok;
}

/****************************************************
 * @brief Libera a memória alocada pelo estoque
 *
 * A função percorre o estoque e libera a memória alocada
 * para cada jogo.
 *
 * @note A função não retorna nada, apenas libera a memória.
 *
 * 1: cria um ponteiro auxiliar para percorrer o estoque.
 * 2: enquanto o auxiliar não for nulo, libera o nome e o estoque.
 * 3: o auxiliar recebe o próximo jogo. (atualiza o ponteiro auxiliar)
 *
 * @param estoque Ponteiro para o estoque
 *****************************************************/
ReturnCode liberaEstoque(void)
{
    Estoque *aux = g_estoque;
    while (aux != NULL)
    {
        Estoque *aux2 = aux->prox;
        free(aux->nome);
        free(aux);
        aux = aux2;
    }
    return ok;
}

/****************************************************
 * @brief Busca um jogo no estoque
 *
 * @param estoque Ponteiro para o estoque
 * @param nome Nome do jogo
 * @return Estoque* Ponteiro para o jogo encontrado
 *
 * 1: cria um ponteiro auxiliar para percorrer o estoque.
 * 2: enquanto o auxiliar não for nulo e o nome do jogo for diferente do nome do jogo do auxiliar, o auxiliar recebe o próximo jogo.
 * 3: retorna o auxiliar.
 *
 * Caso 1: o jogo não foi encontrado, retorna NULL.
 * Caso 2: o jogo foi encontrado, retorna o ponteiro para o jogo.
 *****************************************************/
ReturnCode buscaJogoEstoque(char *nome, int *quantidade)
{
    Estoque *aux = g_estoque;
    while (aux != NULL && strcmp(aux->nome, nome) != 0) // strcmp depois, para nao causar segfault
    {
        aux = aux->prox;
    }
    if (aux == NULL)
    {
        *dia = -1;
        *mes = -1;
        *ano = -1;
        return ok_jogo_nao_encontrado;
    }
    *quantidade = aux->quantidade;
    return ok;
}

/****************************************************
 * @brief Remove um jogo do estoque
 *
 * @param estoque Ponteiro para o estoque
 * @param nome Nome do jogo
 * @return Estoque* Ponteiro para o estoque
 *
 * 1: cria um ponteiro auxiliar para percorrer o estoque.
 * 2: enquanto o auxiliar não for nulo e o nome do jogo for diferente do nome do jogo do auxiliar, o auxiliar recebe o próximo jogo.
 * 3: se o auxiliar for nulo, retorna o estoque.
 * 4: se o auxiliar for o primeiro jogo do estoque, o estoque recebe o próximo jogo.
 * 5: se o auxiliar não for o primeiro jogo do estoque, o anterior ao auxiliar recebe o próximo jogo do auxiliar.
 * 6: libera a memória alocada para o nome e para o estoque.
 * 7: retorna o estoque.
 *
 *
 * Caso 1: o jogo não foi encontrado, retorna o estoque -> não removeu nada.
 * Caso 2: o jogo foi encontrado e é o primeiro -> remove o primeiro jogo.
 * Caso 3: o jogo foi encontrado e não é o primeiro -> remove o jogo.
 * Caso 4: o jogo foi encontrado e é o último -> remove o último jogo.
 *
 *****************************************************/
ReturnCode removeJogoEstoque(char *nome)
{
    Estoque *aux = g_estoque;
    Estoque *ant = NULL;
    while (aux != NULL && strcmp(aux->nome, nome) != 0)
    {
        ant = aux;
        aux = aux->prox;
    }
    if (aux == NULL) // não encontrou o jogo
    {
        return ok_jogo_nao_encontrado;
    }
    if (ant == NULL) // é o primeiro jogo do estoque
    {
        g_estoque = aux->prox;
    }
    else // não é o primeiro jogo do estoque
    {
        ant->prox = aux->prox;
    }
    free(aux->nome);
    free(aux);
    return ok;
}

ReturnCode vendeJogoEstoque(char *nome, int quantidade)
{
    Estoque *aux = g_estoque;
    while (aux != NULL && strcmp(aux->nome, nome) != 0)
    {
        aux = aux->prox;
    }
    if (aux == NULL) // não encontrou o jogo
    {
        return ok_jogo_nao_encontrado;
    }
    if (aux->quantidade < quantidade)
    {
        return ok_quantidade_insuficiente;
    }
    aux->quantidade -= quantidade;
    return ok;
}

ReturnCode compraJogoEstoque(char *nome, int quantidade)
{
    Estoque *aux = g_estoque;
    while (aux != NULL && strcmp(aux->nome, nome) != 0)
    {
        aux = aux->prox;
    }
    if (aux == NULL) // não encontrou o jogo
    {
        return ok_jogo_nao_encontrado;
    }
    aux->quantidade += quantidade;
    return ok;
}

/****************************************************
 * @brief Retorna o tamanho do estoque
 *
 * @param estoque Ponteiro para o estoque
 * @return int Tamanho do estoque
 *
 * 1: cria um ponteiro auxiliar para percorrer o estoque.
 * 2: enquanto o auxiliar não for nulo, incrementa o tamanho e o auxiliar recebe o próximo jogo.
 * 3: retorna o tamanho.
 *
 *****************************************************/
ReturnCode tamanhoEstoque(int *rettamanho)
{
    *rettamanho = 0;
    Estoque *aux = g_estoque;

    if (aux == NULL)
    {
        return ok_vazio;
    }

    while (aux != NULL)
    {
        *rettamanho = *rettamanho + 1;
        aux = aux->prox;
    }
    return ok;
}
