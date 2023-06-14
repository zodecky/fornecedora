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
#include "catalogo.h"

/************************************************************
 *                         STRUCTS                          *
 ************************************************************/

/****************************************************
 * @brief Representa uma data
 *
 *
 *****************************************************/
typedef struct data
{
    int dia;
    int mes;
    int ano;
} Data;

/****************************************************
 * @brief Um catálogo de jogos \n
 *
 * Internamente uma lista encadeada \n
 * Guarda um nome (malloc) e uma data\n
 *
 *****************************************************/
typedef struct catalogo
{
    char *nome;
    Data data_lancamento;
    struct catalogo *prox;
} Catalogo;

/************************************************************
 *                         GLOBAIS                          *
 ************************************************************/

Catalogo *g_catalogo; // catálogo global

/************************************************************
 *                         FUNÇÕES                          *
 ************************************************************/

/****************************************************
 * @brief Cria um novo catálogo
 *
 * A função retorna NULL, para que ao inserir um jogo
 * ele aponte para um ponteiro nulo do "tipo" catálogo.
 *muuint
 * @return Catalogo*
 *
 * Caso 1: retorna null
 *
 *****************************************************/
ReturnCode criaCatalogo(void)
{
    g_catalogo = NULL;
    return ok;
}

/****************************************************
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
 *****************************************************/
ReturnCode insereJogoCatalogo(char *nome, int dia, int mes, int ano)
{
    Data data = {dia, mes, ano};

    // checa formato da data
    if (data.dia < 1 || data.dia > 31)
    {
        printf("\033[31mUm dia deve estar entre 1 e 31!\033[0m\n");
        return formato_invalido;
    }
    if (data.mes < 1 || data.mes > 12)
    {
        printf("\033[31mUm mes deve estar entre 1 e 12!\033[0m\n");
        return formato_invalido;
    }
    if (data.ano < 1)
    {
        printf("\033[31mUm ano deve ser maior que 0!\033[0m\n");
        return formato_invalido;
    }

    if (data.mes == 2 && data.dia > 29)
    {
        printf("\033[31mFevereiro tem 28 dias, exceto em anos bissextos, que tem 29\033[0m\n");
        return formato_invalido;
    }
    else if ((data.mes == 4 || data.mes == 6 || data.mes == 9 || data.mes == 11) && data.dia > 30)
    {
        printf("\033[31mOs meses 4, 6, 9 e 11 nao possuem dia 31!\033[0m\n");
        return formato_invalido;
    }

    if (data.ano % 4 != 0 && data.mes == 2 && data.dia > 28)
    {
        // print explica o erro
        printf("\033[31mO dia 28 de fevereiro somente existe em anos bissextos\033[0m\n");
        return formato_invalido;
    }

    // check numero de digitos do ano
    int ck_ano = data.ano;
    int digitos = 0;
    while (ck_ano != 0)
    {
        ck_ano /= 10;
        digitos++;
    }
    if (digitos != 4)
    {
        printf("\033[31mUm ano deve possuir quatro digitos!\033[0m\n");
        return formato_invalido;
    }

    Catalogo *catalogo = (Catalogo *)malloc(sizeof(Catalogo));          // aloca memória para o catálogo
    catalogo->nome = (char *)malloc(sizeof(char) * (strlen(nome) + 1)); // +1 para o \0

    if (catalogo == NULL || catalogo->nome == NULL) // checa se a alocação foi bem sucedida
    {
        printf("\033[31mErro de alocacao!\033[0m\n");
        return erro_alocacao;
    }

    strcpy(catalogo->nome, nome);     // copia o nome para o catálogo
    catalogo->data_lancamento = data; // copia a data para o catálogo
    catalogo->prox = g_catalogo;      // o próximo é o catalogo anterior

    printf("\033[32mJogo inserido com sucesso!\033[0m\n");
    g_catalogo = catalogo;
    return ok;
}

/****************************************************
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
 *****************************************************/
ReturnCode imprimeCatalogo(void)
{
    Catalogo *aux = g_catalogo;
    if (aux == NULL)
    {
        printf("\x1b[31mO catalogo esta vazio!\n\x1b[0m");
        return ok_vazio;
    }

    printf("\x1b[32m******** Imrpimindo o catalogo *******\n\n\x1b[0m");
    while (aux != NULL)
    {
        printf("\x1b[34mNome: %s\n\x1b[0m", aux->nome);
        printf("\x1b[34mLancamento: %d/%d/%d\n\n\x1b[0m", aux->data_lancamento.dia, aux->data_lancamento.mes, aux->data_lancamento.ano);
        aux = aux->prox;
    }
    printf("\x1b[32m******** Fim da impressao *******\n\n\x1b[0m");
    return ok;
}

/****************************************************
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
 *****************************************************/
ReturnCode liberaCatalogo(void)
{
    Catalogo *aux = g_catalogo;
    while (aux != NULL)
    {
        Catalogo *aux2 = aux->prox;
        free(aux->nome);
        free(aux);
        aux = aux2;
    }
    return ok;
}

/****************************************************
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
 *****************************************************/
ReturnCode buscaJogoCatalogo(char *nome, int *dia, int *mes, int *ano)
{
    Catalogo *aux = g_catalogo;
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
    *dia = aux->data_lancamento.dia;
    *mes = aux->data_lancamento.mes;
    *ano = aux->data_lancamento.ano;
    return ok;
}

/****************************************************
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
 *
 * Caso 1: o jogo não foi encontrado, retorna o catálogo -> não removeu nada.
 * Caso 2: o jogo foi encontrado e é o primeiro -> remove o primeiro jogo.
 * Caso 3: o jogo foi encontrado e não é o primeiro -> remove o jogo.
 * Caso 4: o jogo foi encontrado e é o último -> remove o último jogo.
 *
 *****************************************************/
ReturnCode removeJogoCatalogo(char *nome)
{
    Catalogo *aux = g_catalogo;
    Catalogo *ant = NULL;
    while (aux != NULL && strcmp(aux->nome, nome) != 0)
    {
        ant = aux;
        aux = aux->prox;
    }
    if (aux == NULL) // não encontrou o jogo
    {
        return ok_jogo_nao_encontrado;
    }
    if (ant == NULL) // é o primeiro jogo do catálogo
    {
        g_catalogo = aux->prox;
    }
    else // não é o primeiro jogo do catálogo
    {
        ant->prox = aux->prox;
    }
    free(aux->nome);
    free(aux);
    return ok;
}

/****************************************************
 * @brief Retorna o tamanho do catálogo
 *
 * @param catalogo Ponteiro para o catálogo
 * @return int Tamanho do catálogo
 *
 * 1: cria um ponteiro auxiliar para percorrer o catálogo.
 * 2: enquanto o auxiliar não for nulo, incrementa o tamanho e o auxiliar recebe o próximo jogo.
 * 3: retorna o tamanho.
 *
 *****************************************************/
ReturnCode tamanhoCatalogo(int *rettamanho)
{
    *rettamanho = 0;
    Catalogo *aux = g_catalogo;

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
