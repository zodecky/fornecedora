#include <stdio.h>
#include "../catalogo.h"

int main(void)
{
    Catalogo *catalogo = criaCatalogo();
    catalogo = insereJogoCatalogo(catalogo, "Jogo 1", (Data){1, 1, 2000});
    catalogo = insereJogoCatalogo(catalogo, "Jogo 2", (Data){2, 2, 2000});
    catalogo = insereJogoCatalogo(catalogo, "Jogo 3", (Data){3, 3, 2000});
    catalogo = insereJogoCatalogo(catalogo, "Jogo 4", (Data){4, 4, 2000});
    catalogo = insereJogoCatalogo(catalogo, "Jogo 5", (Data){5, 5, 2000});

    imprimeCatalogo(catalogo);

    catalogo = removeJogoCatalogo(catalogo, "Jogo 3");

    imprimeCatalogo(catalogo);

    liberaCatalogo(catalogo);

    imprimeCatalogo(catalogo);
    return 0;
}