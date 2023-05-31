#include "estoque.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Cria um novo estoque
 *
 * A função retorna NULL, para que ao inserir um jogo
 * ele aponte para um ponteiro nulo do "tipo" estoque.
 *muuint
 * @return Estoque*
 *
 * Caso 1: retorna null
 */
Estoque *criaEstoque(void)
{
    return NULL;
}

/**
 * @brief Insere um novo jogo no catálogo
 *
 * @param estoque Ponteiro para o catálogo
 * @param nome Nome do jogo
 * @param data Data de lançamento do jogo
 *
 * Primeiro a função aloca memória para o catálogo,
 * depois aloca memória para o nome do jogo
 * e copia o nome passado como parâmetro para o nome do jogo.
 * Também adiciona a data de lançamento.
 *
 * @return Estoque* Ponteiro para o catálogo
 *
 */
Estoque *insereJogoEstoque(Estoque *estoque_antigo, char *nome, int quantitade)
{
    if (quantitade < 1)
    {
        printf("A quantidade mínima deve ser 1!");
        return estoque_antigo;
    }

    Estoque *estoque = (Estoque *)malloc(sizeof(Estoque));             // aloca memória para o catálogo
    estoque->nome = (char *)malloc(sizeof(char) * (strlen(nome) + 1)); // +1 para o \0
    strcpy(estoque->nome, nome);                                       // copia o nome para o catálogo
    estoque->quantidade = esto
    estoque->prox = estoque_antigo;                                   // o próximo é o estoque anterior

    printf("\033[32mJogo inserido com sucesso!\033[0m\n");
    return estoque;
}

/**
 * @brief Imprime o catálogo
 *
 * A função percorre o catálogo e imprime o nome e a data de lançamento
 * de cada jogo.
 *
 * @note A função não retorna nada, apenas imprime.
 *
 * @param estoque Ponteiro para o catálogo
 *
 * 1: cria um ponteiro auxiliar para percorrer o catálogo.
 * 2: enquanto o auxiliar não for nulo, imprime o nome e a data de lançamento.
 * 3: o auxiliar recebe o próximo jogo. (atualiza o ponteiro auxiliar)
 *
 *
 * Caso 1: O catálogo está vazio -> imprime que o catálogo está vazio.
 * Caso 2: O catálogo não está vazio -> imprime o catálogo.
 */
void imprimeCatalogo(Estoque *estoque)
{
    Estoque *aux = estoque;
    if (aux == NULL)
    {
        printf("\x1b[31mO estoque esta vazio!\n\x1b[0m");
        return;
    }

    printf("\x1b[32m******** Imrpimindo o estoque *******\n\n\x1b[0m");
    while (aux != NULL)
    {
        printf("\x1b[34mNome: %s\n\x1b[0m", aux->nome);
        printf("\x1b[34mLancamento: %d/%d/%d\n\n\x1b[0m", aux->data_lancamento.dia, aux->data_lancamento.mes, aux->data_lancamento.ano);
        aux = aux->prox;
    }
    printf("\x1b[32m******** Fim da impressao *******\n\n\x1b[0m");
}

/**
 * @brief Libera a memória alocada pelo catálogo
 *
 * A função percorre o catálogo e libera a memória alocada
 * para cada jogo.
 *
 * @note A função não retorna nada, apenas libera a memória.
 *
 * 1: cria um ponteiro auxiliar para percorrer o catálogo.
 * 2: enquanto o auxiliar não for nulo, libera o nome e o catálogo.
 * 3: o auxiliar recebe o próximo jogo. (atualiza o ponteiro auxiliar)
 *
 * @param estoque Ponteiro para o catálogo
 */
void liberaCatalogo(Estoque *estoque)
{
    Estoque *aux = estoque;
    while (aux != NULL)
    {
        Estoque *aux2 = aux->prox;
        free(aux->nome);
        free(aux);
        aux = aux2;
    }
}

/**
 * @brief Busca um jogo no catálogo
 *
 * @param estoque Ponteiro para o catálogo
 * @param nome Nome do jogo
 * @return Estoque* Ponteiro para o jogo encontrado
 *
 * 1: cria um ponteiro auxiliar para percorrer o catálogo.
 * 2: enquanto o auxiliar não for nulo e o nome do jogo for diferente do nome do jogo do auxiliar, o auxiliar recebe o próximo jogo.
 * 3: retorna o auxiliar.
 *
 * Caso 1: o jogo não foi encontrado, retorna NULL.
 * Caso 2: o jogo foi encontrado, retorna o ponteiro para o jogo.
 */
Estoque *buscaJogoCatalogo(Estoque *estoque, char *nome)
{
    Estoque *aux = estoque;
    while (aux != NULL && strcmp(aux->nome, nome) != 0)
    {
        aux = aux->prox;
    }
    return aux;
}

/**
 * @brief Remove um jogo do catálogo
 *
 * @param estoque Ponteiro para o catálogo
 * @param nome Nome do jogo
 * @return Estoque* Ponteiro para o catálogo
 *
 * 1: cria um ponteiro auxiliar para percorrer o catálogo.
 * 2: enquanto o auxiliar não for nulo e o nome do jogo for diferente do nome do jogo do auxiliar, o auxiliar recebe o próximo jogo.
 * 3: se o auxiliar for nulo, retorna o catálogo.
 * 4: se o auxiliar for o primeiro jogo do catálogo, o catálogo recebe o próximo jogo.
 * 5: se o auxiliar não for o primeiro jogo do catálogo, o anterior ao auxiliar recebe o próximo jogo do auxiliar.
 * 6: libera a memória alocada para o nome e para o catálogo.
 * 7: retorna o catálogo.
 *
 *
 * Caso 1: o jogo não foi encontrado, retorna o catálogo -> não removeu nada.
 * Caso 2: o jogo foi encontrado e é o primeiro -> remove o primeiro jogo.
 * Caso 3: o jogo foi encontrado e não é o primeiro -> remove o jogo.
 * Caso 4: o jogo foi encontrado e é o último -> remove o último jogo.
 *
 */
Estoque *removeJogoCatalogo(Estoque *estoque, char *nome)
{
    Estoque *aux = estoque;
    Estoque *ant = NULL;
    while (aux != NULL && strcmp(aux->nome, nome) != 0)
    {
        ant = aux;
        aux = aux->prox;
    }
    if (aux == NULL) // não encontrou o jogo
    {
        return estoque;
    }
    if (ant == NULL) // é o primeiro jogo do catálogo
    {
        estoque = aux->prox;
    }
    else // não é o primeiro jogo do catálogo
    {
        ant->prox = aux->prox;
    }
    free(aux->nome);
    free(aux);
    return estoque;
}

/**
 * @brief Retorna o tamanho do catálogo
 *
 * @param estoque Ponteiro para o catálogo
 * @return int Tamanho do catálogo
 *
 * 1: cria um ponteiro auxiliar para percorrer o catálogo.
 * 2: enquanto o auxiliar não for nulo, incrementa o tamanho e o auxiliar recebe o próximo jogo.
 * 3: retorna o tamanho.
 *
 */
int tamanhoCatalogo(Estoque *estoque)
{
    int tamanho = 0;
    Estoque *aux = estoque;
    while (aux != NULL)
    {
        tamanho++;
        aux = aux->prox;
    }
    return tamanho;
}
