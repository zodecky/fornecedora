#include <stdio.h>
#include <stdlib.h>
#include "catalogo.h"
#include "munit.h"

static MunitResult
test_compare(const MunitParameter params[], void *data)
{
    Catalogo *catalogo = criaCatalogo();

    // munit_assert_ptr_equal(catalogo, (Catalogo *)NULL);

    catalogo = insereJogoCatalogo(catalogo, "Jogo 1", (Data){1, 1, 2200});

    Catalogo *test = (Catalogo *)munit_malloc(sizeof(Catalogo));
    test->nome = (char *)munit_malloc(sizeof(char) * (strlen("Jogo 1") + 1));
    strcpy(test->nome, "Jogo 1");
    test->data_lancamento = (Data){1, 1, 2200};
    test->prox = NULL;

    return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    {/* The name is just a unique human-readable way to identify the
      * test. You can use it to run a specific test if you want, but
      * usually it's mostly decorative. */
     (char *)"Cria Catalogo",
     /* You probably won't be surprised to learn that the tests are
      * functions. */
     test_compare,
     /* Finally, there is a bitmask for options you can pass here.  You
      * can provide either MUNIT_TEST_OPTION_NONE or 0 here to use the
      * defaults. */
     MUNIT_TEST_OPTION_NONE,
     NULL}};
/* Usually this is written in a much more compact format; all these
 * comments kind of ruin that, though.  Here is how you'll usually
 * see entries written: */

static const MunitSuite test_suite = {
    /* This string will be prepended to all test names in this suite;
     * for example, "/example/rand" will become "/µnit/example/rand".
     * Note that, while it doesn't really matter for the top-level
     * suite, NULL signal the end of an array of tests; you should use
     * an empty string ("") instead. */
    (char *)"",
    /* The first parameter is the array of test suites. */
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
    /* Just like MUNIT_TEST_OPTION_NONE, you can provide
     * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
    MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
    /* Finally, we'll actually run our test suite!  That second argument
     * is the user_data parameter which will be passed either to the
     * test or (if provided) the fixture setup function. */
    return munit_suite_main(&test_suite, (void *)"µnit", argc, argv);
}