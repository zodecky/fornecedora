
/* Bibliotecas padrão */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sqlite3.h>

/* Modulos */
#include "../include/estoque.h"
#include "../include/catalogo.h"

/**
 * @brief Cria a tabela catalogo no banco de dados, caso não exista
 *
 * @param db
 * @return true (sucesso) or false (falha)
 */
bool cria_tabela(sqlite3 *db)
{
    char *sql = "CREATE TABLE IF NOT EXISTS catalogo("
                "nome TEXT NOT NULL PRIMARY KEY,"
                "dia INTEGER NOT NULL,"
                "mes INTEGER NOT NULL,"
                "ano INTEGER NOT NULL);";

    char *mensagem;
    int rc = sqlite3_exec(db, sql, NULL, 0, &mensagem);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erro ao criar a tabela: %s\n", sqlite3_errmsg(db));
        sqlite3_free(mensagem);
        return false;
    }

    return true;
}

bool salva_no_db(sqlite3 *db, Catalogo *catalogo)
{
    char *sql = "INSERT INTO catalogo (nome, dia, mes, ano) VALUES (?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erro ao preparar o statement: %s\n", sqlite3_errmsg(db));
        return false;
    }

    while (catalogo != NULL)
    {
        sqlite3_bind_text(stmt, 1, catalogo->nome, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, catalogo->data_lancamento.dia);
        sqlite3_bind_int(stmt, 3, catalogo->data_lancamento.mes);
        sqlite3_bind_int(stmt, 4, catalogo->data_lancamento.ano);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE)
        {
            fprintf(stderr, "Erro ao executar o statement: %s\n", sqlite3_errmsg(db));
            return false;
        }

        catalogo = catalogo->prox;
    }

    sqlite3_finalize(stmt);
    return true;
}

Catalogo *carrega_do_db(sqlite3 *db, Catalogo *catalogo)
{
    char *sql = "SELECT * FROM catalogo;";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erro ao preparar o statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    while (1)
    {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE)
        {
            break;
        }
        else if (rc != SQLITE_ROW)
        {
            fprintf(stderr, "Erro ao executar o statement: %s\n", sqlite3_errmsg(db));
            return false;
        }

        char *nome = (char *)sqlite3_column_text(stmt, 0);
        int dia = sqlite3_column_int(stmt, 1);
        int mes = sqlite3_column_int(stmt, 2);
        int ano = sqlite3_column_int(stmt, 3);

        printf("%s %d %d %d\n", nome, dia, mes, ano);

        Data data = {dia, mes, ano};
        catalogo = insereJogoCatalogo(catalogo, nome, data);
    }

    sqlite3_finalize(stmt);
    return catalogo;
}

/* limpa db */
bool limpa_db(sqlite3 *db)
{
    char *sql = "DELETE FROM catalogo;";

    char *mensagem;
    int rc = sqlite3_exec(db, sql, NULL, 0, &mensagem);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erro ao limpar a tabela: %s\n", sqlite3_errmsg(db));
        sqlite3_free(mensagem);
        return false;
    }

    return true;
}

int main()
{
    /* INICIALIZAR DB */
    sqlite3 *db;
    int rc = sqlite3_open("catalogo.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    /* CRIAR TABELA */
    if (!cria_tabela(db))
    {
        fprintf(stderr, "Erro ao criar a tabela!\n");
        sqlite3_close(db);
        return 1;
    }

    Catalogo *catalogo = criaCatalogo();
    char comando[20];

    while (1)
    {
        printf("Digite um comando (insere, busca, remove, imprime, tamanho, sair, limpa (bd), salva, carrega)): ");
        scanf(" %[^\n]", comando);

        if (strcmp(comando, "insere") == 0)
        {
            char nome[50];
            int dia, mes, ano;

            printf("Digite o nome do jogo: ");
            scanf(" %[^\n]", nome); // lê até o \n

            printf("Digite a data de lancamento (DD MM AAAA): ");
            scanf("%d %d %d", &dia, &mes, &ano);

            Data data = {dia, mes, ano};
            catalogo = insereJogoCatalogo(catalogo, nome, data);
        }
        else if (strcmp(comando, "busca") == 0)
        {
            char nome[50];

            printf("Digite o nome do jogo: ");
            scanf(" %[^\n]", nome); // lê até o \n

            Catalogo *jogo = buscaJogoCatalogo(catalogo, nome);
            if (jogo == NULL)
            {
                printf("Jogo nao encontrado!\n");
            }
            else
            {
                printf("Jogo encontrado: %s\n", jogo->nome);
            }
        }
        else if (strcmp(comando, "remove") == 0)
        {
            char nome[50];

            printf("Digite o nome do jogo: ");
            scanf(" %[^\n]", nome); // lê até o \n

            catalogo = removeJogoCatalogo(catalogo, nome);
            printf("Jogo removido com sucesso!\n");
        }
        else if (strcmp(comando, "imprime") == 0)
        {
            imprimeCatalogo(catalogo);
        }
        else if (strcmp(comando, "tamanho") == 0)
        {
            int tamanho = tamanhoCatalogo(catalogo);
            printf("Tamanho do catalogo: %d\n", tamanho);
        }
        else if (strcmp(comando, "salva") == 0)
        {
            if (!salva_no_db(db, catalogo))
            {
                fprintf(stderr, "Erro ao salvar no banco de dados!\n");
            }
            else
            {
                printf("Catalogo salvo com sucesso!\n");
            }
        }
        else if (strcmp(comando, "carrega") == 0)
        {
            catalogo = carrega_do_db(db, catalogo);
            if (catalogo == NULL)
            {
                fprintf(stderr, "Erro ao carregar do banco de dados!\n");
            }
            else
            {
                printf("Catalogo carregado com sucesso!\n");
            }
        }
        else if (strcmp(comando, "limpa") == 0)
        {
            if (!limpa_db(db))
            {
                fprintf(stderr, "Erro ao limpar o banco de dados!\n");
            }
            else
            {
                printf("Catalogo limpo com sucesso!\n");
            }
        }
        else if (strcmp(comando, "sair") == 0)
        {
            break;
        }
        else
        {
            printf("Comando invalido!\n");
        }
    }

    liberaCatalogo(catalogo);
    return 0;
}
