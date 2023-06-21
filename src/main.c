
/* Bibliotecas padrão */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// #include <sqlite3.h>

/* Modulos */
#include "../include/estoque.h"
#include "../include/catalogo.h"
#include "../include/codes.h"

// /**
//  * @brief Cria a tabela catalogo no banco de dados, caso não exista
//  *
//  * @param db
//  * @return true (sucesso) or false (falha)
//  */
// bool cria_tabela(sqlite3 *db)
// {
//     char *sql = "CREATE TABLE IF NOT EXISTS catalogo("
//                 "nome TEXT NOT NULL PRIMARY KEY,"
//                 "dia INTEGER NOT NULL,"
//                 "mes INTEGER NOT NULL,"
//                 "ano INTEGER NOT NULL);";

//     char *mensagem;
//     int rc = sqlite3_exec(db, sql, NULL, 0, &mensagem);

//     if (rc != SQLITE_OK)
//     {
//         fprintf(stderr, "Erro ao criar a tabela: %s\n", sqlite3_errmsg(db));
//         sqlite3_free(mensagem);
//         return false;
//     }

//     return true;
// }

// bool salva_no_db(sqlite3 *db, Catalogo *catalogo)
// {
//     char *sql = "INSERT INTO catalogo (nome, dia, mes, ano) VALUES (?, ?, ?, ?);";

//     sqlite3_stmt *stmt;
//     int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

//     if (rc != SQLITE_OK)
//     {
//         fprintf(stderr, "Erro na funcao prepare do banco de dados: %s\n", sqlite3_errmsg(db));
//         return false;
//     }

//     while (catalogo != NULL)
//     {
//         sqlite3_bind_text(stmt, 1, catalogo->nome, -1, SQLITE_STATIC);
//         sqlite3_bind_int(stmt, 2, catalogo->data_lancamento.dia);
//         sqlite3_bind_int(stmt, 3, catalogo->data_lancamento.mes);
//         sqlite3_bind_int(stmt, 4, catalogo->data_lancamento.ano);

//         rc = sqlite3_step(stmt);
//         if (rc != SQLITE_DONE)
//         {
//             fprintf(stderr, "Erro na insercao no banco de dados: %s\n", sqlite3_errmsg(db));
//             return false;
//         }

//         catalogo = catalogo->prox;
//     }

//     sqlite3_finalize(stmt);
//     return true;
// }

// Catalogo *carrega_do_db(sqlite3 *db, Catalogo *catalogo)
// {
//     char *sql = "SELECT * FROM catalogo;";

//     sqlite3_stmt *stmt;
//     int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

//     if (rc != SQLITE_OK)
//     {
//         fprintf(stderr, "Erro ao preparar o statement: %s\n", sqlite3_errmsg(db));
//         return NULL;
//     }

//     while (1)
//     {
//         rc = sqlite3_step(stmt);
//         if (rc == SQLITE_DONE)
//         {
//             break;
//         }
//         else if (rc != SQLITE_ROW)
//         {
//             fprintf(stderr, "Erro ao executar o statement: %s\n", sqlite3_errmsg(db));
//             return false;
//         }

//         char *nome = (char *)sqlite3_column_text(stmt, 0);
//         int dia = sqlite3_column_int(stmt, 1);
//         int mes = sqlite3_column_int(stmt, 2);
//         int ano = sqlite3_column_int(stmt, 3);

//         // printf("%s %d %d %d\n", nome, dia, mes, ano);

//         Data data = {dia, mes, ano};
//         catalogo = insereJogoCatalogo(catalogo, nome, data);
//     }

//     sqlite3_finalize(stmt);
//     return catalogo;
// }

// /* limpa db */
// bool limpa_db(sqlite3 *db)
// {
//     char *sql = "DELETE FROM catalogo;";

//     char *mensagem;
//     int rc = sqlite3_exec(db, sql, NULL, 0, &mensagem);

//     if (rc != SQLITE_OK)
//     {
//         fprintf(stderr, "Erro ao limpar a tabela: %s\n", sqlite3_errmsg(db));
//         sqlite3_free(mensagem);
//         return false;
//     }

//     return true;
// }

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

ReturnCode code;

int main()
{
    // /* INICIALIZAR DB */
    // sqlite3 *db;
    // int rc = sqlite3_open("catalogo.db", &db);
    // if (rc != SQLITE_OK)
    // {
    //     fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
    //     sqlite3_close(db);
    //     return 1;
    // }

    // /* CRIAR TABELA */
    // if (!cria_tabela(db))
    // {
    //     fprintf(stderr, "Erro ao criar a tabela!\n");
    //     sqlite3_close(db);
    //     return 1;
    // }

    criaCatalogo();
    char comando[20];

    while (1)
    {
        printf(ANSI_COLOR_CYAN "\n------------------------------------------------------------\nDigite um comando (insere, busca, remove, imprime, tamanho, sair, limpa (bd), salva, carrega)): " ANSI_COLOR_RESET);
        scanf(" %[^\n]", comando);
        printf(ANSI_COLOR_CYAN "------------------------------------------------------------\n\n" ANSI_COLOR_RESET);

        if (strcmp(comando, "insere") == 0)
        {
            char nome[50];
            int dia, mes, ano;

            printf(ANSI_COLOR_CYAN "Digite o nome do jogo: " ANSI_COLOR_RESET);
            scanf(" %[^\n]", nome); // lê até o \n

            printf(ANSI_COLOR_CYAN "Digite a data de lancamento (DD MM AAAA): " ANSI_COLOR_RESET);
            scanf("%d %d %d", &dia, &mes, &ano);

            code = insereJogoCatalogo(nome, dia, mes, ano);

            if (code == ok)
                printf(ANSI_COLOR_GREEN "Jogo inserido com sucesso!\n" ANSI_COLOR_RESET);

            else if (code == erro_alocacao)
                printf("\033[31mErro de alocacao!\033[0m\n");

            else if (code == formato_invalido_ano_deve_possuir_quatro_digitos)
                printf("\033[31mUm ano deve possuir quatro digitos!\033[0m\n");

            else if (code == formato_invalido_dia_28_de_fevereiro_somente_existe_em_anos_bissextos)
                printf("\033[31mO dia 28 de fevereiro somente existe em anos bissextos\033[0m\n");

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

            printf(ANSI_COLOR_CYAN "Digite o nome do jogo: " ANSI_COLOR_RESET);
            scanf(" %[^\n]", nome); // lê até o \n

            code = buscaJogoCatalogo(nome, &dia, &mes, &ano);
            if (code == ok_jogo_nao_encontrado)
            {
                printf(ANSI_COLOR_RED "Jogo nao encontrado!\n" ANSI_COLOR_RESET);
            }
            else if (code == ok)
            {
                printf(ANSI_COLOR_GREEN "Jogo encontrado: %s\n" ANSI_COLOR_RESET, nome);
                printf(ANSI_COLOR_GREEN "Data de lancamento: %d/%d/%d\n" ANSI_COLOR_RESET, dia, mes, ano);
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
        // else if (strcmp(comando, "salva") == 0)
        // {
        //     if (!salva_no_db(db, catalogo))
        //     {
        //         fprintf(stderr, ANSI_COLOR_RED "Erro ao salvar no banco de dados!\n" ANSI_COLOR_RESET);
        //     }
        //     else
        //     {
        //         printf("\033[1;32mCatalogo salvo com sucesso!\n" ANSI_COLOR_RESET);
        //     }
        // }
        // else if (strcmp(comando, "carrega") == 0)
        // {
        //     catalogo = carrega_do_db(db, catalogo);
        //     if (catalogo == NULL)
        //     {
        //         fprintf(stderr, ANSI_COLOR_RED "Erro ao carregar do banco de dados!\n" ANSI_COLOR_RESET);
        //     }
        //     else
        //     {
        //         printf(ANSI_COLOR_GREEN "Catalogo carregado com sucesso!\n" ANSI_COLOR_RESET);
        //     }
        // }
        // else if (strcmp(comando, "limpa") == 0)
        // {
        //     if (!limpa_db(db))
        //     {
        //         fprintf(stderr, ANSI_COLOR_RED "Erro ao limpar o banco de dados!\n" ANSI_COLOR_RESET);
        //     }
        //     else
        //     {
        //         printf(ANSI_COLOR_GREEN "Catalogo limpo com sucesso!\n" ANSI_COLOR_RESET);
        //     }
        // }
        else if (strcmp(comando, "sair") == 0)
        {
            break;
        }
        else
        {
            printf(ANSI_COLOR_RED "Comando invalido!\n" ANSI_COLOR_RESET);
        }
    }

    liberaCatalogo();
    return 0;
}