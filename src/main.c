
/* Bibliotecas padrão */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Bibliotecas incluidas */
#include "../lib/cJSON/cJSON.h"

/* Modulos */
#include "../include/estoque.h"
#include "../include/catalogo.h"
#include "../include/codes.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

ReturnCode code;

void leSolicitacao(char *nome)
{
    FILE *fp = fopen("./release/bin/arquivo.json", "r");
    if (fp == NULL)
    {
        perror("fopen");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL)
    {
        perror("malloc");
        exit(1);
    }
    fread(buffer, size, 1, fp);
    buffer[size] = '\0';
    fclose(fp);
    cJSON *root = cJSON_Parse(buffer);
    free(buffer);
    if (root == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        exit(1);
    }
    cJSON *name = cJSON_GetObjectItem(root, "nome");
    if (name == NULL)
    {
        fprintf(stderr, "Failed to get name\n");
        cJSON_Delete(root);
        exit(1);
    }
    strcpy(nome, name->valuestring);
    cJSON_Delete(root);
    return;
}

void darpreco(float preco)
{
    FILE *fp = fopen("./release/bin/arquivo.json", "r");
    if (fp == NULL)
    {
        perror("fopen");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL)
    {
        perror("malloc");
        exit(1);
    }
    fread(buffer, size, 1, fp);
    buffer[size] = '\0';
    fclose(fp);
    cJSON *root = cJSON_Parse(buffer);
    free(buffer);
    if (root == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Erro: %s\n", error_ptr);
        }
        exit(1);
    }
    cJSON *nome = cJSON_GetObjectItem(root, "nome");
    if (nome == NULL)
    {
        fprintf(stderr, "Falha ao pegar nome\n");
        cJSON_Delete(root);
        exit(1);
    }
    cJSON_ReplaceItemInObject(root, "preco", cJSON_CreateNumber(preco));
    cJSON_ReplaceItemInObject(root, "nome", cJSON_CreateString(""));
    char *new_json_string = cJSON_Print(root);
    fp = fopen("./release/bin/arquivo.json", "w");
    if (fp == NULL)
    {
        perror("fopen");
        exit(1);
    }
    fputs(new_json_string, fp);
    fclose(fp);
    free(new_json_string);
    cJSON_Delete(root);
}

void printnoti(char *nome)
{
    printf(ANSI_COLOR_YELLOW "------------------------------------------------------------\nVoce tem uma solicitacao de compra!\n------------------------------------------------------------" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "\nNome do jogo: %s\n" ANSI_COLOR_RESET, nome);
}

int main(void)
{
    criaCatalogo();
    criaEstoque();
    char comando[20];
    char nome[50];
    int compra = 0;

    while (1)
    {
        leSolicitacao(nome);

        if (strlen(nome))
        {
            printnoti(nome);
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------\nAcessar: (catalogo, estoque, recarregar, sair, " ANSI_COLOR_YELLOW "vender" ANSI_COLOR_CYAN "): " ANSI_COLOR_RESET);
            compra = 1;
        }
        else
        {
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------\nAcessar: (catalogo, estoque, recarregar, sair): " ANSI_COLOR_RESET);
        }
        scanf(" %[^\n]", comando);
        printf(ANSI_COLOR_CYAN "------------------------------------------------------------\n\n" ANSI_COLOR_RESET);

        if (strcmp(comando, "catalogo") == 0)
        {
            while (1)
            {
                leSolicitacao(nome);

                if (strlen(nome))
                {
                    printnoti(nome);
                    printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------\nCatalogo: (insere, busca, remove, imprime, tamanho, voltar, recarregar, sair, " ANSI_COLOR_YELLOW "vender" ANSI_COLOR_CYAN "): " ANSI_COLOR_RESET);
                    compra = 1;
                }
                else
                {
                    printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------\nCatalogo: (insere, busca, remove, imprime, tamanho, voltar, recarregar, sair): " ANSI_COLOR_RESET);
                }

                scanf(" %[^\n]", comando);
                printf(ANSI_COLOR_CYAN "------------------------------------------------------------\n\n" ANSI_COLOR_RESET);
                if (strcmp(comando, "insere") == 0)
                {
                    char nome[50];
                    int dia, mes, ano;
                    float preco;

                    printf(ANSI_COLOR_CYAN "Digite o nome do jogo: " ANSI_COLOR_RESET);
                    scanf(" %[^\n]", nome); // lê até o \n

                    printf(ANSI_COLOR_CYAN "Digite a data de lancamento (DD MM AAAA): " ANSI_COLOR_RESET);
                    scanf("%d %d %d", &dia, &mes, &ano);

                    printf(ANSI_COLOR_CYAN "Digite o preco do jogo (ex: 10.0): " ANSI_COLOR_RESET);
                    scanf("%f", &preco);

                    code = insereJogoCatalogo(nome, dia, mes, ano, preco);

                    if (code == ok)
                    {
                        code = insereJogoEstoque(nome, 10); // quantidade_negativa nunca vai acontecer
                        if (code == ok)
                        {
                            printf(ANSI_COLOR_GREEN "Jogo inserido com sucesso!\n" ANSI_COLOR_RESET);
                        }
                    }

                    else if (code == erro_alocacao)
                        printf("\033[31mErro de alocacao!\033[0m\n");

                    else if (code == formato_invalido_ano_deve_possuir_quatro_digitos)
                        printf("\033[31mUm ano deve possuir quatro digitos!\033[0m\n");

                    else if (code == formato_invalido_dia_29_de_fevereiro_somente_existe_em_anos_bissextos)
                        printf("\033[31mO dia 29 de fevereiro somente existe em anos bissextos\033[0m\n");

                    else if (code == formato_invalido_meses_4_6_9_11_nao_possuem_dia_31)
                        printf("\033[31mOs meses 4, 6, 9 e 11 nao possuem dia 31!\033[0m\n");

                    else if (code == formato_invalido_fevereiro_tem_28_dias)
                        printf("\033[31mFevereiro tem 28 dias, exceto em anos bissextos, que tem 29\033[0m\n");

                    else if (code == formato_invalido_ano_maior_que_0)
                        printf("\033[31mUm ano deve ser maior que 0!\033[0m\n");

                    else if (code == formato_invalido_mes_entre_1_e_12)
                        printf("\033[31mUm mes deve estar entre 1 e 12!\033[0m\n");

                    else if (code == formato_invalido_dia_entre_1_e_31)
                        printf("\033[31mUm dia deve estar entre 1 e 31!\033[0m\n");

                    else
                        printf("\033[31mErro desconhecido!\033[0m\n");
                }
                else if (strcmp(comando, "busca") == 0)
                {
                    char nome[50];
                    int dia, mes, ano;
                    float preco;

                    printf(ANSI_COLOR_CYAN "Digite o nome do jogo: " ANSI_COLOR_RESET);
                    scanf(" %[^\n]", nome); // lê até o \n

                    code = buscaJogoCatalogo(nome, &dia, &mes, &ano, &preco);
                    if (code == ok_jogo_nao_encontrado)
                    {
                        printf(ANSI_COLOR_RED "Jogo nao encontrado!\n" ANSI_COLOR_RESET);
                    }
                    else if (code == ok)
                    {
                        printf(ANSI_COLOR_GREEN "Jogo encontrado: %s\n" ANSI_COLOR_RESET, nome);
                        printf(ANSI_COLOR_GREEN "Data de lancamento: %d/%d/%d\n" ANSI_COLOR_RESET, dia, mes, ano);
                        printf(ANSI_COLOR_GREEN "Preco: %.2f\n" ANSI_COLOR_RESET, preco);
                    }
                    else
                    {
                        printf(ANSI_COLOR_RED "Erro desconhecido ao buscar o jogo!\n" ANSI_COLOR_RESET);
                    }
                }
                else if (strcmp(comando, "remove") == 0)
                {
                    char nome[50];

                    printf(ANSI_COLOR_CYAN "Digite o nome do jogo: " ANSI_COLOR_RESET);
                    scanf(" %[^\n]", nome); // lê até o \n

                    code = removeJogoCatalogo(nome);
                    printf(ANSI_COLOR_GREEN "Jogo removido com sucesso!\n" ANSI_COLOR_RESET);
                }
                else if (strcmp(comando, "imprime") == 0)
                {
                    code = imprimeCatalogo();
                }
                else if (strcmp(comando, "tamanho") == 0)
                {
                    int tamanho;
                    code = tamanhoCatalogo(&tamanho);
                    printf(ANSI_COLOR_GREEN "Numero de jogos no catalogo: %d\n" ANSI_COLOR_RESET, tamanho);
                }
                else if (strcmp(comando, "voltar") == 0)
                {
                    break;
                }
                else if (strcmp(comando, "recarregar") == 0)
                {
                    continue;
                }
                else if (strcmp(comando, "sair") == 0)
                {
                    goto Final;
                }
                else if (compra)
                {
                    if (strcmp(comando, "vender") == 0)
                    {
                        int dia, mes, ano;
                        float preco;

                        buscaJogoCatalogo(nome, &dia, &mes, &ano, &preco);
                        darpreco(preco);
                        // COMPRA
                        compra = 0;
                    }
                }
                else
                {
                    printf(ANSI_COLOR_RED "Comando invalido!\n" ANSI_COLOR_RESET);
                }
            }
        }
        else if (strcmp(comando, "estoque") == 0)
        {
            while (1)
            {
                leSolicitacao(nome);

                if (strlen(nome))
                {
                    printnoti(nome);
                    printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------\nEstoque: (insere, busca, remove, imprime, tamanho, voltar, recarregar, sair, " ANSI_COLOR_YELLOW "vender" ANSI_COLOR_CYAN "): " ANSI_COLOR_RESET);
                    compra = 1;
                }
                else
                {
                    printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------\nEstoque: (insere, busca, remove, imprime, tamanho, voltar, recarregar, sair): " ANSI_COLOR_RESET);
                }
                scanf(" %[^\n]", comando);
                printf(ANSI_COLOR_CYAN "------------------------------------------------------------\n\n" ANSI_COLOR_RESET);
                if (strcmp(comando, "insere") == 0)
                {
                    char nome[50];
                    int quantidade;

                    printf(ANSI_COLOR_CYAN "Digite o nome do jogo: " ANSI_COLOR_RESET);
                    scanf(" %[^\n]", nome); // lê até o \n

                    printf(ANSI_COLOR_CYAN "Digite a quantidade: " ANSI_COLOR_RESET);
                    scanf("%d", &quantidade);

                    code = insereJogoEstoque(nome, quantidade);

                    if (code == ok)
                        printf(ANSI_COLOR_GREEN "Jogo inserido com sucesso!\n" ANSI_COLOR_RESET);

                    else if (code == erro_alocacao)
                        printf("\033[31mErro de alocacao!\033[0m\n");

                    else if (code == formato_invalido_quantidade_negativa)
                        printf("\033[31mA quantidade deve ser maior ou igual a 0!\033[0m\n");

                    else
                        printf("\033[31mErro desconhecido!\033[0m\n");
                }
                else if (strcmp(comando, "busca") == 0)
                {
                    char nome[50];
                    int quantidade;

                    printf(ANSI_COLOR_CYAN "Digite o nome do jogo: " ANSI_COLOR_RESET);
                    scanf(" %[^\n]", nome); // lê até o \n

                    code = buscaJogoEstoque(nome, &quantidade);
                    if (code == ok_jogo_nao_encontrado)
                    {
                        printf(ANSI_COLOR_RED "Jogo nao encontrado!\n" ANSI_COLOR_RESET);
                    }
                    else if (code == ok)
                    {
                        printf(ANSI_COLOR_GREEN "Jogo encontrado: %s\n" ANSI_COLOR_RESET, nome);
                        printf(ANSI_COLOR_GREEN "Quantidade: %d\n" ANSI_COLOR_RESET, quantidade);
                    }
                    else
                    {
                        printf(ANSI_COLOR_RED "Erro desconhecido ao buscar o jogo!\n" ANSI_COLOR_RESET);
                    }
                }
                else if (strcmp(comando, "remove") == 0)
                {
                    char nome[50];

                    printf(ANSI_COLOR_CYAN "Digite o nome do jogo: " ANSI_COLOR_RESET);
                    scanf(" %[^\n]", nome); // lê até o \n

                    code = removeJogoEstoque(nome);
                    printf(ANSI_COLOR_GREEN "Jogo removido com sucesso!\n" ANSI_COLOR_RESET);
                }
                else if (strcmp(comando, "imprime") == 0)
                {
                    code = imprimeEstoque();
                }
                else if (strcmp(comando, "tamanho") == 0)
                {
                    int tamanho;
                    code = tamanhoEstoque(&tamanho);
                    printf(ANSI_COLOR_GREEN "Numero de jogos no estoque: %d\n" ANSI_COLOR_RESET, tamanho);
                }
                else if (strcmp(comando, "voltar") == 0)
                {
                    break;
                }
                else if (strcmp(comando, "recarregar") == 0)
                {
                    continue;
                }
                else if (strcmp(comando, "sair") == 0)
                {
                    goto Final;
                }
                else if (compra)
                {
                    if (strcmp(comando, "vender") == 0)
                    {
                        int dia, mes, ano;
                        float preco;

                        buscaJogoCatalogo(nome, &dia, &mes, &ano, &preco);
                        darpreco(preco);
                        // COMPRA
                        compra = 0;
                    }
                }
                else
                {
                    printf(ANSI_COLOR_RED "Comando invalido!\n" ANSI_COLOR_RESET);
                }
            }
        }
        else if (strcmp(comando, "recarregar") == 0)
        {
            continue;
        }
        else if (strcmp(comando, "sair") == 0)
        {
            break;
        }
        else if (compra)
        {
            if (strcmp(comando, "vender") == 0)
            {
                int dia, mes, ano;
                float preco;

                buscaJogoCatalogo(nome, &dia, &mes, &ano, &preco);
                darpreco(preco);
                // COMPRA
                compra = 0;
            }
        }
        else
        {
            printf(ANSI_COLOR_RED "Comando invalido!\n" ANSI_COLOR_RESET);
        }
    }
Final:
    liberaCatalogo();
    liberaEstoque();
    return 0;
}