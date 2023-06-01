#include "estoque.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
 * @brief Insere um novo jogo no estoque
 *
 * @param estoque Ponteiro para o estoque
 * @param nome Nome do jogo
 * @param quantidade quantidade a ser adicionada
 *
 * Primeiro a função aloca memória para o estoque,
 * depois aloca memória para o nome do jogo
 * e copia o nome passado como parâmetro para o nome do jogo.
 * Também adiciona a data de a quantidade de jogos.
 *
 * TODO: inserir com quantidade 10
 * TODO: nao deixar inserir quando já estiver no estoque
 * imprimir erro mandando usar a função compra
 *
 * @return Estoque* Ponteiro para o estoque
 *
 */
Estoque *insereJogoEstoque(Estoque *estoque_antigo, char *nome)
{
    // TODO: ????? if (quantitade < 1) aqn
    //  {
    //      printf("\033[31mA quantidade mínima deve ser 1!\033[0m]");
    //      return estoque_antigo;
    //  }
    //  TODO: talvez checar se jogo já existe no estoque
    Estoque *estoque = (Estoque *)malloc(sizeof(Estoque));             // aloca memória para o estoque
    estoque->nome = (char *)malloc(sizeof(char) * (strlen(nome) + 1)); // +1 para o \0
    strcpy(estoque->nome, nome);                                       // copia o nome para o estoque
    estoque->quantidade = 10;                                          // incializa com 10
    estoque->prox = estoque_antigo;                                    // o próximo é o estoque anterior

    printf("\033[32mJogo inserido com sucesso! (+10 unindades)\033[0m\n");
    return estoque;
}

/**
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
 */
void imprimeEstoque(Estoque *estoque)
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
        printf("\x1b[34mQuantidade: %d\n\n\x1b[0m", aux->quantidade);
        aux = aux->prox;
    }
    printf("\x1b[32m******** Fim da impressao *******\n\n\x1b[0m");
}

/**
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
 */
void liberaEstoque(Estoque *estoque)
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
 */
Estoque *buscaJogoEstoque(Estoque *estoque, char *nome)
{
    Estoque *aux = estoque;
    while (aux != NULL && strcmp(aux->nome, nome) != 0)
    {
        aux = aux->prox;
    }
    return aux;
}

/**
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
 */
Estoque *removeJogoEstoque(Estoque *estoque, char *nome)
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
    if (ant == NULL) // é o primeiro jogo do estoque
    {
        estoque = aux->prox;
    }
    else // não é o primeiro jogo do estoque
    {
        ant->prox = aux->prox;
    }
    free(aux->nome);
    free(aux);
    return estoque;
}

/**
 * @brief Vende um jogo do estoque
 *
 * @param estoque
 * @param nome
 * @return Estoque*
 */
bool vendeJogoEstoque(Estoque *estoque, char *nome, int quantidade)
{
    Estoque *jogo = buscaJogoEstoque(estoque, nome);
    if (jogo == NULL || jogo->quantidade < 1) // Ordem importa para não causar segfault
    {
        printf("Nao ha unidades disponiveis para venda!");
        return false;
    }

    jogo->quantidade -= quantidade;
    if (quantidade == 1)
        printf("-1 unidade de %s", jogo->nome);
    else
        printf("-%d unidades de %s", jogo->quantidade, jogo->nome);
    return true;
}

/**
 * @brief Compra unidades de um jogo para o estoque
 *
 * @param estoque
 * @param nome
 * @return Estoque*
 */
bool compraJogoEstoque(Estoque *estoque, char *nome, int quantidade)
{
    Estoque *jogo = buscaJogoEstoque(estoque, nome);
    if (jogo == NULL)
    {
        printf("Jogo nao esta no estoque, para adicionar use a funcao inserir");
        return false;
    }

    jogo->quantidade += quantidade;
    if (quantidade == 1)
        printf("+1 unidade de %s", jogo->nome);
    else
        printf("+%d unidades de %s", jogo->quantidade, jogo->nome);
    return true;
}

/**
 * @brief Retorna o quantidade do estoque
 *
 * @param estoque Ponteiro para o estoque
 * @return int Tamanho do estoque
 *
 * 1: cria um ponteiro auxiliar para percorrer o estoque.
 * 2: enquanto o auxiliar não for nulo, incrementa a quantidade e o auxiliar recebe o próximo jogo.
 * 3: retorna o quantidade.
 *
 */
int quantidadeJogosEstoque(Estoque *estoque)
{
    int quantidade = 0;
    Estoque *aux = estoque;
    while (aux != NULL)
    {
        quantidade += aux->quantidade;
        aux = aux->prox;
    }
    return quantidade;
}
