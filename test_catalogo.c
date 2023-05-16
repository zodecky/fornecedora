#include <stdio.h>
#include <stdlib.h>
#include "catalogo.h"
#include "munit.h"

int main(void)
{
    Catalogo *catalogo = criaCatalogo();

    munit_assert_ptr_null(catalogo);

    catalogo = insereJogoCatalogo(catalogo, "Jogo 1", (Data){1, 1, 2200});

    Catalogo *test = (Catalogo *)munit_malloc(sizeof(Catalogo));
    test->nome = (char *)munit_malloc(sizeof(char) * (strlen("Jogo 1") + 1));
    strcpy(catalogo->nome, "Jogo 1");
    catalogo->data_lancamento = (Data){1, 1, 2200};
    catalogo->prox = NULL;

    munit_assert_memory_equal(sizeof(Catalogo), catalogo, test);

    return 0;
}
