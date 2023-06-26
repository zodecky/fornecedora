
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

#define PATH_JSON "./release/bin/arquivo.json"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

ReturnCode code;

void leSolicitacao(char *nome, float *preco, int *quantidade, int *finalizacao)
{
    FILE *fp = fopen(PATH_JSON, "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL)
    {
        printf("Erro ao alocar memoria\n");
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
    cJSON *preco_json = cJSON_GetObjectItem(root, "preco");
    cJSON *quantidade_json = cJSON_GetObjectItem(root, "quantidade");
    cJSON *finalizacao_json = cJSON_GetObjectItem(root, "finalizacao");
    if (name == NULL)
    {
        fprintf(stderr, "Falha ao pegar o nome.\n");
        cJSON_Delete(root);
    }
    strcpy(nome, name->valuestring);
    *preco = preco_json->valuedouble;
    *quantidade = quantidade_json->valueint;
    *finalizacao = finalizacao_json->valueint;
    cJSON_Delete(root);
    return;
}

void darpreco(float preco)
{
    FILE *fp = fopen(PATH_JSON, "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL)
    {
        printf("Erro ao alocar memoria\n");
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
    }
    cJSON_ReplaceItemInObject(root, "preco", cJSON_CreateNumber(preco));
    char *new_json_string = cJSON_Print(root);
    fp = fopen(PATH_JSON, "w");
    if (fp == NULL)
    {
        printf("fopen");
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

void printnotifini(char *nome, float preco, int quantidade)
{
    printf(ANSI_COLOR_YELLOW "------------------------------------------------------------\nVoce tem uma solicitacao de finalizacao de compra!\n------------------------------------------------------------" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "\nNome do jogo: %s\n" ANSI_COLOR_RESET, nome);
    printf(ANSI_COLOR_YELLOW "\nPreco do jogo: %.2f\n" ANSI_COLOR_RESET, preco);
    printf(ANSI_COLOR_YELLOW "\nQuantidade do jogo: %d\n" ANSI_COLOR_RESET, quantidade);
}

ReturnCode inserir_jogo(char *nome)
{
    int dia, mes, ano;
    float preco;

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

    return code;
}

ReturnCode venda(char *nome)
{
    int dia, mes, ano;
    float preco;

    code = buscaJogoCatalogo(nome, &dia, &mes, &ano, &preco);
    if (code != ok)
    {
        printf(ANSI_COLOR_YELLOW "O jogo nao esta no catalogo: Preferencia constatada!\n------------------------------------------------------------\nInserir jogo:\n" ANSI_COLOR_RESET);
    }
    while (code != ok)
    {
        code = inserir_jogo(nome);
        if (code == ok)
        {
            code = buscaJogoCatalogo(nome, &dia, &mes, &ano, &preco);
        }
    }

    darpreco(preco);
    return ok;
}

ReturnCode fin_venda(char *nome, int quantidade)
{
inicio:
    code = vendeJogoEstoque(nome, quantidade);

    if (code == ok_quantidade_insuficiente)
    {
        printf(ANSI_COLOR_RED "Quantidade insuficiente no estoque!\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Comprando +10 jogos...\n" ANSI_COLOR_RESET);
        code = compraJogoEstoque(nome, 10);
        goto inicio;
    }
    else if (code == ok_jogo_nao_encontrado)
    {
        printf(ANSI_COLOR_RED "Jogo nao encontrado!\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Comprando +10 jogos e inserindo no estoque...\n" ANSI_COLOR_RESET);
        insereJogoEstoque(nome, 10);
        goto inicio;
    }
    else if (code == ok)
    {
        printf(ANSI_COLOR_GREEN "Realizando venda...\n" ANSI_COLOR_RESET);
    }
    else
    {
        printf("\033[31mErro desconhecido!\033[0m\n");
        return code;
    }

    FILE *fp = fopen(PATH_JSON, "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL)
    {
        printf("Erro ao alocar memoria\n");
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
    }
    cJSON_ReplaceItemInObject(root, "finalizacao", cJSON_CreateNumber(1));
    char *new_json_string = cJSON_Print(root);
    fp = fopen(PATH_JSON, "w");
    if (fp == NULL)
    {
        printf("fopen");
    }
    fputs(new_json_string, fp);
    fclose(fp);
    free(new_json_string);
    cJSON_Delete(root);
    return ok;
}

int main(void)
{
    criaCatalogo();
    criaEstoque();
    char comando[20];
    char nome[50];
    float preco;
    int quantidade;
    int finalizacao;
    int compra = 0;
    int finalizar = 0;

    while (1)
    {
        leSolicitacao(nome, &preco, &quantidade, &finalizacao);

        if (strlen(nome) && preco < 0 && quantidade < 0 && finalizacao < 0)
        {
            printnoti(nome);
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------\nAcessar: (catalogo, estoque, recarregar, sair, " ANSI_COLOR_YELLOW "vender" ANSI_COLOR_CYAN "): " ANSI_COLOR_RESET);
            compra = 1;
        }
        else if (strlen(nome) && preco > 0 && quantidade > 0 && finalizacao < 0)
        {
            printnotifini(nome, preco, quantidade);
            printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------\nAcessar: (catalogo, estoque, recarregar, sair, " ANSI_COLOR_YELLOW "finalizar" ANSI_COLOR_CYAN "): " ANSI_COLOR_RESET);
            finalizar = 1;
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
                leSolicitacao(nome, &preco, &quantidade, &finalizacao);

                if (strlen(nome) && preco < 0 && quantidade < 0 && finalizacao < 0)
                {
                    printnoti(nome);
                    printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------\nCatalogo: (insere, busca, remove, imprime, tamanho, voltar, recarregar, sair, " ANSI_COLOR_YELLOW "vender" ANSI_COLOR_CYAN "): " ANSI_COLOR_RESET);
                    compra = 1;
                }
                else if (strlen(nome) && preco > 0 && quantidade > 0 && finalizacao < 0)
                {
                    printnotifini(nome, preco, quantidade);
                    printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------\nCatalogo: (insere, busca, remove, imprime, tamanho, voltar, recarregar, sair, " ANSI_COLOR_YELLOW "finalizar" ANSI_COLOR_CYAN "): " ANSI_COLOR_RESET);
                    finalizar = 1;
                }
                else
                {
                    printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------\nCatalogo: (insere, busca, remove, imprime, tamanho, voltar, recarregar, sair): " ANSI_COLOR_RESET);
                }

                scanf(" %[^\n]", comando);
                printf(ANSI_COLOR_CYAN "------------------------------------------------------------\n\n" ANSI_COLOR_RESET);
                if (strcmp(comando, "insere") == 0)
                {
                    printf(ANSI_COLOR_CYAN "Digite o nome do jogo: " ANSI_COLOR_RESET);
                    scanf(" %[^\n]", nome); // lê até o \n

                    inserir_jogo(nome);
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
                else if (strcmp(comando, "vender") == 0)
                {
                    if (compra)
                    {
                        code = venda(nome);
                        if (code == ok)
                        {
                            printf(ANSI_COLOR_YELLOW "\nPreco enviado para locadora!\n");
                            compra = 0;
                        }
                    }
                    else
                    {
                        printf(ANSI_COLOR_RED "Comando invalido!\n" ANSI_COLOR_RESET);
                    }
                }
                else if (strcmp(comando, "finalizar") == 0)
                {
                    if (finalizar)
                    {
                        code = fin_venda(nome, quantidade);
                        if (code == ok)
                        {
                            printf(ANSI_COLOR_YELLOW "\nVenda finalizada!\n");
                            finalizar = 0;
                        }
                    }
                    else
                    {
                        printf(ANSI_COLOR_RED "Comando invalido!\n" ANSI_COLOR_RESET);
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
                leSolicitacao(nome, &preco, &quantidade, &finalizacao);

                if (strlen(nome) && preco < 0 && quantidade < 0 && finalizacao < 0)
                {
                    printnoti(nome);
                    printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------\nEstoque: (insere, busca, remove, imprime, tamanho, voltar, recarregar, sair, " ANSI_COLOR_YELLOW "vender" ANSI_COLOR_CYAN "): " ANSI_COLOR_RESET);
                    compra = 1;
                }
                else if (strlen(nome) && preco > 0 && quantidade > 0 && finalizacao < 0)
                {
                    printnotifini(nome, preco, quantidade);
                    printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------\nEstoque: (insere, busca, remove, imprime, tamanho, voltar, recarregar, sair, " ANSI_COLOR_YELLOW "finalizar" ANSI_COLOR_CYAN "): " ANSI_COLOR_RESET);
                    finalizar = 1;
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
                else if (strcmp(comando, "vender") == 0)
                {
                    if (compra)
                    {
                        code = venda(nome);
                        if (code == ok)
                        {
                            printf(ANSI_COLOR_YELLOW "\nPreco enviado para locadora!\n");
                            compra = 0;
                        }
                    }
                    else
                    {
                        printf(ANSI_COLOR_RED "Comando invalido!\n" ANSI_COLOR_RESET);
                    }
                }
                else if (strcmp(comando, "finalizar") == 0)
                {
                    if (finalizar)
                    {
                        code = fin_venda(nome, quantidade);
                        if (code == ok)
                        {
                            printf(ANSI_COLOR_YELLOW "\nVenda finalizada!\n");
                            finalizar = 0;
                        }
                    }
                    else
                    {
                        printf(ANSI_COLOR_RED "Comando invalido!\n" ANSI_COLOR_RESET);
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
        else if (strcmp(comando, "vender") == 0)
        {
            if (compra)
            {
                code = venda(nome);
                if (code == ok)
                {
                    printf(ANSI_COLOR_YELLOW "\nPreco enviado para locadora!\n");
                    compra = 0;
                }
            }
            else
            {
                printf(ANSI_COLOR_RED "Comando invalido!\n" ANSI_COLOR_RESET);
            }
        }
        else if (strcmp(comando, "finalizar") == 0)
        {
            if (finalizar)
            {
                code = fin_venda(nome, quantidade);
                if (code == ok)
                {
                    printf(ANSI_COLOR_YELLOW "\nVenda finalizada!\n");
                    finalizar = 0;
                }
            }
            else
            {
                printf(ANSI_COLOR_RED "Comando invalido!\n" ANSI_COLOR_RESET);
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