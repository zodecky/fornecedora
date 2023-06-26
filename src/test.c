/* Example file for using µnit.
 *
 * µnit is MIT-licensed, but for this file and this file alone:
 *
 * To the extent possible under law, the author(s) of this file have
 * waived all copyright and related or neighboring rights to this
 * work.  See <https://creativecommons.org/publicdomain/zero/1.0/> for
 * details.
 *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../include/catalogo.h"
#include "../include/estoque.h"
#include "../include/codes.h"
#include "munit.h"

/* This is just to disable an MSVC warning about conditional
 * expressions being constant, which you shouldn't have to do for your
 * code.  It's only here because we want to be able to do silly things
 * like assert that 0 != 1 for our demo. */
#if defined(_MSC_VER)
#pragma warning(disable : 4127)
#endif

// disable warning -Wmissing-field-initializers
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#endif

/* Tests are functions that return void, and take a single void*
 * parameter.  We'll get to what that parameter is later. */
static MunitResult
test_criaCatalogo(const MunitParameter params[], void *data)
{
  ReturnCode code = criaCatalogo();

  if (code == ok)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_insereJogo_ok(const MunitParameter params[], void *data)
{

  ReturnCode code = insereJogoCatalogo("filme1", 9, 12, 2003, 33.40);

  if (code == ok)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_insereJogo_formato_invalido_dia_entre_1_e_31(const MunitParameter params[], void *data)
{

  ReturnCode code = insereJogoCatalogo("filme2", 32, 12, 2003, 33.40);

  if (code == formato_invalido_dia_entre_1_e_31)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_insereJogo_formato_invalido_mes_entre_1_e_12(const MunitParameter params[], void *data)
{

  ReturnCode code = insereJogoCatalogo("filme3", 9, 13, 2003, 33.40);

  if (code == formato_invalido_mes_entre_1_e_12)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_insereJogo_formato_invalido_ano_maior_que_0(const MunitParameter params[], void *data)
{

  ReturnCode code = insereJogoCatalogo("filme4", 9, 12, -2003, 33.40);

  if (code == formato_invalido_ano_maior_que_0)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_insereJogo_formato_invalido_fevereiro_tem_28_dias(const MunitParameter params[], void *data)
{

  ReturnCode code = insereJogoCatalogo("filme5", 30, 2, 2003, 33.40);

  if (code == formato_invalido_fevereiro_tem_28_dias)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_insereJogo_formato_invalido_meses_4_6_9_11_nao_possuem_dia_31(const MunitParameter params[], void *data)
{

  ReturnCode code = insereJogoCatalogo("filme6", 31, 4, 2003, 33.40);

  if (code == formato_invalido_meses_4_6_9_11_nao_possuem_dia_31)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_insereJogo_formato_invalido_dia_29_de_fevereiro_somente_existe_em_anos_bissextos(const MunitParameter params[], void *data)
{

  ReturnCode code = insereJogoCatalogo("filme7", 29, 2, 2003, 33.40);

  if (code == formato_invalido_dia_29_de_fevereiro_somente_existe_em_anos_bissextos)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_removeJogoCatalogo_ok(const MunitParameter params[], void *data)
{
  insereJogoCatalogo("filme1", 9, 12, 2003, 33.40);
  ReturnCode code = removeJogoCatalogo("filme1");

  if (code == ok)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_removeJogoCatalogo_err_jogo_nao_encontrado(const MunitParameter params[], void *data)
{
  ReturnCode code = removeJogoCatalogo("filme1");

  if (code == ok_jogo_nao_encontrado)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_imprimeCatalogo_ok(const MunitParameter params[], void *data)
{

  insereJogoCatalogo("filme3", 9, 12, 2003, 33.40);
  freopen("/dev/null", "w", stdout);
  ReturnCode code = imprimeCatalogo();
  freopen("/dev/tty", "w", stdout);

  if (code == ok)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_imprimeCatalogo_ok_vazio(const MunitParameter params[], void *data)
{

  removeJogoCatalogo("filme1");
  freopen("/dev/null", "w", stdout);
  ReturnCode code = imprimeCatalogo();
  freopen("/dev/tty", "w", stdout);

  if (code == ok_vazio)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_buscaJogoCatalogo_ok(const MunitParameter params[], void *data)
{
  int dia, mes, ano;
  float preco;
  insereJogoCatalogo("filme7", 9, 12, 2003, 33.40);
  ReturnCode code = buscaJogoCatalogo("filme7", &dia, &mes, &ano, &preco);

  int temp = preco * 100;

  if (code == ok && dia == 9 && mes == 12 && ano == 2003, temp == 3340)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_buscaJogoCatalogo_err_jogo_nao_encontrado(const MunitParameter params[], void *data)
{
  int *dia, *mes, *ano;
  float *preco;

  ReturnCode code = buscaJogoCatalogo("banana", &dia, &mes, &ano, &preco);

  if (code == ok_jogo_nao_encontrado)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_tamanhoCatalogo_ok(const MunitParameter params[], void *data)
{
  int tamanho;
  insereJogoCatalogo("filme8", 9, 12, 2003, 33.40);
  ReturnCode code = tamanhoCatalogo(&tamanho);

  if (code == ok)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_tamanhoCatalogo_ok_vazio(const MunitParameter params[], void *data)
{
  int tamanho;
  removeJogoCatalogo("filme8");
  ReturnCode code = tamanhoCatalogo(&tamanho);

  if (code == ok_vazio)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

// o mesmo, mas para estoque.c

static MunitResult
test_criaEstoque_ok(const MunitParameter params[], void *data)
{
  ReturnCode code = criaEstoque();

  if (code == ok)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_insereJogoEstoque_ok(const MunitParameter params[], void *data)
{
  ReturnCode code = insereJogoEstoque("filme1", 4);

  if (code == ok)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_insereJogoEstoque_err_quantidade_negativa(const MunitParameter params[], void *data)
{
  ReturnCode code = insereJogoEstoque("filme1", -4);

  if (code == formato_invalido_quantidade_negativa)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_removeJogoEstoque_ok(const MunitParameter params[], void *data)
{
  insereJogoEstoque("filme1", 4);
  ReturnCode code = removeJogoEstoque("filme1");

  if (code == ok)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_removeJogoEstoque_err_jogo_nao_encontrado(const MunitParameter params[], void *data)
{
  ReturnCode code = removeJogoEstoque("filme1");

  if (code == ok_jogo_nao_encontrado)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_imprimeEstoque_ok(const MunitParameter params[], void *data)
{

  insereJogoEstoque("filme3", 4);
  freopen("/dev/null", "w", stdout);
  ReturnCode code = imprimeEstoque();
  freopen("/dev/tty", "w", stdout);

  if (code == ok)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_imprimeEstoque_ok_vazio(const MunitParameter params[], void *data)
{

  removeJogoEstoque("filme1");
  freopen("/dev/null", "w", stdout);
  ReturnCode code = imprimeEstoque();
  freopen("/dev/tty", "w", stdout);

  if (code == ok_vazio)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_buscaJogoEstoque_ok(const MunitParameter params[], void *data)
{
  int quantidade;
  insereJogoEstoque("filme7", 4);
  ReturnCode code = buscaJogoEstoque("filme7", &quantidade);

  if (code == ok && quantidade == 4)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_buscaJogoEstoque_err_jogo_nao_encontrado(const MunitParameter params[], void *data)
{
  int *quantidade;
  ReturnCode code = buscaJogoEstoque("banana", &quantidade);

  if (code == ok_jogo_nao_encontrado)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_tamanhoEstoque_ok(const MunitParameter params[], void *data)
{
  int tamanho;

  insereJogoEstoque("filme8", 4);
  ReturnCode code = tamanhoEstoque(&tamanho);

  if (code == ok && tamanho == 1)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

static MunitResult
test_tamanhoEstoque_ok_vazio(const MunitParameter params[], void *data)
{
  int tamanho;
  removeJogoEstoque("filme8");
  ReturnCode code = tamanhoEstoque(&tamanho);

  if (code == ok_vazio)
    return MUNIT_OK;
  else
    return MUNIT_FAIL;
}

/* Creating a test suite is pretty simple.  First, you'll need an
 * array of tests: */
static MunitTest test_suite_tests[] = {
    {(char *)"/criaCatalogo", test_criaCatalogo, MUNIT_TEST_OPTION_NONE},
    {(char *)"/insJgCat/ok", test_insereJogo_ok, MUNIT_TEST_OPTION_NONE},
    {(char *)"/insJgCat/err_dia_entre_1_e_31", test_insereJogo_formato_invalido_dia_entre_1_e_31, MUNIT_TEST_OPTION_NONE},
    {(char *)"/insJgCat/err_mes_entre_1_e_12", test_insereJogo_formato_invalido_mes_entre_1_e_12, MUNIT_TEST_OPTION_NONE},
    {(char *)"/insJgCat/err_ano_maior_que_0", test_insereJogo_formato_invalido_ano_maior_que_0, MUNIT_TEST_OPTION_NONE},
    {(char *)"/insJgCat/err_fevereiro_tem_28_dias", test_insereJogo_formato_invalido_fevereiro_tem_28_dias, MUNIT_TEST_OPTION_NONE},
    {(char *)"/insJgCat/err_m_4_6_9_11_n_pos_dia_31", test_insereJogo_formato_invalido_meses_4_6_9_11_nao_possuem_dia_31, MUNIT_TEST_OPTION_NONE},
    {(char *)"/insJgCat/err_dia_29_de_fev_ano_bi", test_insereJogo_formato_invalido_dia_29_de_fevereiro_somente_existe_em_anos_bissextos, MUNIT_TEST_OPTION_NONE},
    {(char *)"/remJgCat/ok", test_removeJogoCatalogo_ok, MUNIT_TEST_OPTION_NONE},
    {(char *)"/remJgCat/err_jogo_nao_encontrado", test_removeJogoCatalogo_err_jogo_nao_encontrado, MUNIT_TEST_OPTION_NONE},
    {(char *)"/impCat/ok", test_imprimeCatalogo_ok, MUNIT_TEST_OPTION_NONE},
    {(char *)"/impCat/ok_vazio", test_imprimeCatalogo_ok_vazio, MUNIT_TEST_OPTION_NONE},
    {(char *)"/buscaJgCat/ok", test_buscaJogoCatalogo_ok, MUNIT_TEST_OPTION_NONE},
    {(char *)"/buscaJgCat/err_jogo_nao_encontrado", test_buscaJogoCatalogo_err_jogo_nao_encontrado, MUNIT_TEST_OPTION_NONE},
    {(char *)"/tamCat/ok", test_tamanhoCatalogo_ok, MUNIT_TEST_OPTION_NONE},
    {(char *)"/tamCat/ok_vazio", test_tamanhoCatalogo_ok_vazio, MUNIT_TEST_OPTION_NONE},
    {(char *)"/criaEstoque", test_criaEstoque_ok, MUNIT_TEST_OPTION_NONE},
    {(char *)"/insJgEst/ok", test_insereJogoEstoque_ok, MUNIT_TEST_OPTION_NONE},
    {(char *)"/insJgEst/err_quantidade_negativa", test_insereJogoEstoque_err_quantidade_negativa, MUNIT_TEST_OPTION_NONE},
    {(char *)"/remJgEst/ok", test_removeJogoEstoque_ok, MUNIT_TEST_OPTION_NONE},
    {(char *)"/remJgEst/ok_jogo_nao_encontrado", test_removeJogoEstoque_err_jogo_nao_encontrado, MUNIT_TEST_OPTION_NONE},
    {(char *)"/buscaJgEst/ok", test_buscaJogoEstoque_ok, MUNIT_TEST_OPTION_NONE},
    {(char *)"/buscaJgEst/ok_jogo_nao_encontrado", test_buscaJogoEstoque_err_jogo_nao_encontrado, MUNIT_TEST_OPTION_NONE},
    {(char *)"/tamEst/ok", test_tamanhoEstoque_ok, MUNIT_TEST_OPTION_NONE},
    {(char *)"/tamEst/ok_vazio", test_tamanhoEstoque_ok_vazio, MUNIT_TEST_OPTION_NONE},
    {(char *)"/impEst/ok", test_imprimeEstoque_ok, MUNIT_TEST_OPTION_NONE},
    {(char *)"impEst/ok_vazio", test_imprimeEstoque_ok_vazio, MUNIT_TEST_OPTION_NONE},

    MUNIT_TEST_OPTION_NONE};

/* Now we'll actually declare the test suite.  You could do this in
 * the main function, or on the heap, or whatever you want. */
static const MunitSuite test_suite = {
    (char *)"",
    test_suite_tests,
    /* In addition to containing test cases, suites can contain other
     * test suites.  This isn't necessary in this example, but it can be
     * a great help to projects with lots of tests by making it easier
     * to spread the tests across many files.  This is where you would
     * put "other_suites" (which is commented out above). */
    NULL,
    /* An interesting feature of µnit is that it supports automatically
     * running multiple iterations of the tests.  This is usually only
     * interesting if you make use of the PRNG to randomize your tests
     * cases a bit, or if you are doing performance testing and want to
     * average multiple runs.  0 is an alias for 1. */
    1,
    MUNIT_SUITE_OPTION_NONE};

/* This is only necessary for EXIT_SUCCESS and EXIT_FAILURE, which you
 * *should* be using but probably aren't (no, zero and non-zero don't
 * always mean success and failure).  I guess my point is that nothing
 * about µnit requires it. */
#include <stdlib.h>

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
  /* Finally, we'll actually run our test suite!  That second argument
   * is the user_data parameter which will be passed either to the
   * test or (if provided) the fixture setup function. */
  return munit_suite_main(&test_suite, (void *)"µnit", argc, argv);
}
