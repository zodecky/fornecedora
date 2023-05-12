#include "catalogo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Cria um novo catálogo
 *
 * A função retorna NULL, para que ao inserir um jogo
 * ele aponte para um ponteiro nulo do "tipo" catálogo.
 *
 * @return Catalogo*
 */
Catalogo *criaCatalogo(void)
{
    return NULL;
}

/**
 * @brief Insere um novo jogo no catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @param nome Nome do jogo
 * @param data Data de lançamento do jogo
 *
 * Primeiro a função aloca memória para o catálogo,
 * depois aloca memória para o nome do jogo
 * e copia o nome passado como parâmetro para o nome do jogo.
 * Também adiciona a data de lançamento.
 *
 * @return Catalogo* Ponteiro para o catálogo
 *
 */
Catalogo *insereJogoCatalogo(Catalogo *catalogo_antigo, char *nome, Data data)
{
    Catalogo *catalogo = (Catalogo *)malloc(sizeof(Catalogo));          // aloca memória para o catálogo
    catalogo->nome = (char *)malloc(sizeof(char) * (strlen(nome) + 1)); // +1 para o \0
    strcpy(catalogo->nome, nome);                                       // copia o nome para o catálogo
    catalogo->data_lancamento = data;                                   // copia a data para o catálogo
    catalogo->prox = catalogo_antigo;                                   // o próximo é o catalogo anterior
    return catalogo;
}

/**
 * @brief Imprime o catálogo
 *
 * A função percorre o catálogo e imprime o nome e a data de lançamento
 * de cada jogo.
 *
 * @note A função não retorna nada, apenas imprime.
 *
 * @param catalogo Ponteiro para o catálogo
 *
 * 1: cria um ponteiro auxiliar para percorrer o catálogo.
 * 2: enquanto o auxiliar não for nulo, imprime o nome e a data de lançamento.
 * 3: o auxiliar recebe o próximo jogo. (atualiza o ponteiro auxiliar)
 *
 *
 * Caso 1: O catálogo está vazio -> imprime que o catálogo está vazio.
 * Caso 2: O catálogo não está vazio -> imprime o catálogo.
 */
void imprimeCatalogo(Catalogo *catalogo)
{
    Catalogo *aux = catalogo;
    printf("******** Imrpimindo o catalogo *******\n\n");
    while (aux != NULL)
    {
        printf("Nome: %s\n", aux->nome);
        printf("Lancamento: %d/%d/%d\n\n", aux->data_lancamento.dia, aux->data_lancamento.mes, aux->data_lancamento.ano);
        aux = aux->prox;
    }
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
 * @param catalogo Ponteiro para o catálogo
 */
void liberaCatalogo(Catalogo *catalogo)
{
    Catalogo *aux = catalogo;
    while (aux != NULL)
    {
        Catalogo *aux2 = aux->prox;
        free(aux->nome);
        free(aux);
        aux = aux2;
    }
}

/**
 * @brief Busca um jogo no catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @param nome Nome do jogo
 * @return Catalogo* Ponteiro para o jogo encontrado
 *
 * 1: cria um ponteiro auxiliar para percorrer o catálogo.
 * 2: enquanto o auxiliar não for nulo e o nome do jogo for diferente do nome do jogo do auxiliar, o auxiliar recebe o próximo jogo.
 * 3: retorna o auxiliar.
 *
 * Caso 1: o jogo não foi encontrado, retorna NULL.
 * Caso 2: o jogo foi encontrado, retorna o ponteiro para o jogo.
 */
Catalogo *buscaJogoCatalogo(Catalogo *catalogo, char *nome)
{
    Catalogo *aux = catalogo;
    while (aux != NULL && strcmp(aux->nome, nome) != 0)
    {
        aux = aux->prox;
    }
    return aux;
}

/**
 * @brief Remove um jogo do catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @param nome Nome do jogo
 * @return Catalogo* Ponteiro para o catálogo
 *
 * 1: cria um ponteiro auxiliar para percorrer o catálogo.
 * 2: enquanto o auxiliar não for nulo e o nome do jogo for diferente do nome do jogo do auxiliar, o auxiliar recebe o próximo jogo.
 * 3: se o auxiliar for nulo, retorna o catálogo.
 * 4: se o auxiliar for o primeiro jogo do catálogo, o catálogo recebe o próximo jogo.
 * 5: se o auxiliar não for o primeiro jogo do catálogo, o anterior ao auxiliar recebe o próximo jogo do auxiliar.
 * 6: libera a memória alocada para o nome e para o catálogo.
 * 7: retorna o catálogo.
 *
 */
Catalogo *removeJogoCatalogo(Catalogo *catalogo, char *nome)
{
    Catalogo *aux = catalogo;
    Catalogo *ant = NULL;
    while (aux != NULL && strcmp(aux->nome, nome) != 0)
    {
        ant = aux;
        aux = aux->prox;
    }
    if (aux == NULL)
    {
        return catalogo;
    }
    if (ant == NULL)
    {
        catalogo = aux->prox;
    }
    else
    {
        ant->prox = aux->prox;
    }
    free(aux->nome);
    free(aux);
    return catalogo;
}

/**
 * @brief Retorna o tamanho do catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @return int Tamanho do catálogo
 *
 * 1: cria um ponteiro auxiliar para percorrer o catálogo.
 * 2: enquanto o auxiliar não for nulo, incrementa o tamanho e o auxiliar recebe o próximo jogo.
 * 3: retorna o tamanho.
 *
 */
int tamanhoCatalogo(Catalogo *catalogo)
{
    int tamanho = 0;
    Catalogo *aux = catalogo;
    while (aux != NULL)
    {
        tamanho++;
        aux = aux->prox;
    }
    return tamanho;
}
