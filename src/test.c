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
#include "catalogo.h"
#include "munit.h"

/* This is just to disable an MSVC warning about conditional
 * expressions being constant, which you shouldn't have to do for your
 * code.  It's only here because we want to be able to do silly things
 * like assert that 0 != 1 for our demo. */
#if defined(_MSC_VER)
#pragma warning(disable : 4127)
#endif

/* Tests are functions that return void, and take a single void*
 * parameter.  We'll get to what that parameter is later. */
static MunitResult
test_compare(const MunitParameter params[], void *data)
{
  Catalogo *catalogo = criaCatalogo();

  munit_assert_ptr_equal(catalogo, (Catalogo *)NULL);

  catalogo = insereJogoCatalogo(catalogo, "Jogo 1", (Data){1, 1, 2200});

  Catalogo *test = (Catalogo *)munit_malloc(sizeof(Catalogo));
  test->nome = (char *)munit_malloc(sizeof(char) * (strlen("Jogo 1") + 1));
  strcpy(test->nome, "Jogo 1");
  test->data_lancamento = (Data){1, 1, 2200};
  test->prox = NULL;

  return MUNIT_OK;
}

static MunitResult
test_rand(const MunitParameter params[], void *user_data)
{
  int random_int;
  double random_dbl;
  munit_uint8_t data[5];

  (void)params;
  (void)user_data;

  /* One thing missing from a lot of unit testing frameworks is a
   * random number generator.  You can't just use srand/rand because
   * the implementation varies across different platforms, and it's
   * important to be able to look at the seed used in a failing test
   * to see if you can reproduce it.  Some randomness is a fantastic
   * thing to have in your tests, I don't know why more people don't
   * do it...
   *
   * µnit's PRNG is re-seeded with the same value for each iteration
   * of each test.  The seed is retrieved from the MUNIT_SEED
   * envirnment variable or, if none is provided, one will be
   * (pseudo-)randomly generated. */

  /* If you need an integer in a given range */
  random_int = munit_rand_int_range(128, 4096);
  munit_assert_int(random_int, >=, 128);
  munit_assert_int(random_int, <=, 4096);

  /* Or maybe you want a double, between 0 and 1: */
  random_dbl = munit_rand_double();
  munit_assert_double(random_dbl, >=, 0.0);
  munit_assert_double(random_dbl, <=, 1.0);

  /* Of course, you want to be able to reproduce bugs discovered
   * during testing, so every time the tests are run they print the
   * random seed used.  When you want to reproduce a result, just put
   * that random seed in the MUNIT_SEED environment variable; it even
   * works on different platforms.
   *
   * If you want this to pass, use 0xdeadbeef as the random seed and
   * uncomment the next line of code.  Note that the PRNG is not
   * re-seeded between iterations of the same test, so this will only
   * work on the first iteration. */
  /* munit_assert_uint32(munit_rand_uint32(), ==, 1306447409); */

  /* You can also get blobs of random memory: */
  munit_rand_memory(sizeof(data), data);

  return MUNIT_OK;
}

/* This test case shows how to accept parameters.  We'll see how to
 * specify them soon.
 *
 * By default, every possible variation of a parameterized test is
 * run, but you can specify parameters manually if you want to only
 * run specific test(s), or you can pass the --single argument to the
 * CLI to have the harness simply choose one variation at random
 * instead of running them all. */
static MunitResult
test_parameters(const MunitParameter params[], void *user_data)
{
  const char *foo;
  const char *bar;

  (void)user_data;

  /* The "foo" parameter is specified as one of the following values:
   * "one", "two", or "three". */
  foo = munit_parameters_get(params, "foo");
  /* Similarly, "bar" is one of "four", "five", or "six". */
  bar = munit_parameters_get(params, "bar");
  /* "baz" is a bit more complicated.  We don't actually specify a
   * list of valid values, so by default NULL is passed.  However, the
   * CLI will accept any value.  This is a good way to have a value
   * that is usually selected randomly by the test, but can be
   * overridden on the command line if desired. */
  /* const char* baz = munit_parameters_get(params, "baz"); */

  /* Notice that we're returning MUNIT_FAIL instead of writing an
   * error message.  Error messages are generally preferable, since
   * they make it easier to diagnose the issue, but this is an
   * option.
   *
   * Possible values are:
   *  - MUNIT_OK: Sucess
   *  - MUNIT_FAIL: Failure
   *  - MUNIT_SKIP: The test was skipped; usually this happens when a
   *    particular feature isn't in use.  For example, if you're
   *    writing a test which uses a Wayland-only feature, but your
   *    application is running on X11.
   *  - MUNIT_ERROR: The test failed, but not because of anything you
   *    wanted to test.  For example, maybe your test downloads a
   *    remote resource and tries to parse it, but the network was
   *    down.
   */

  if (strcmp(foo, "one") != 0 &&
      strcmp(foo, "two") != 0 &&
      strcmp(foo, "three") != 0)
    return MUNIT_FAIL;

  if (strcmp(bar, "red") != 0 &&
      strcmp(bar, "green") != 0 &&
      strcmp(bar, "blue") != 0)
    return MUNIT_FAIL;

  return MUNIT_OK;
}

/* The setup function, if you provide one, for a test will be run
 * before the test, and the return value will be passed as the sole
 * parameter to the test function. */
static void *
test_compare_setup(const MunitParameter params[], void *user_data)
{
  (void)params;

  munit_assert_string_equal(user_data, "µnit");
  return (void *)(uintptr_t)0xdeadbeef;
}

/* To clean up after a test, you can use a tear down function.  The
 * fixture argument is the value returned by the setup function
 * above. */
static void
test_compare_tear_down(void *fixture)
{
  munit_assert_ptr_equal(fixture, (void *)(uintptr_t)0xdeadbeef);
}

static char *foo_params[] = {
    (char *)"one", (char *)"two", (char *)"three", NULL};

static char *bar_params[] = {
    (char *)"red", (char *)"green", (char *)"blue", NULL};

static MunitParameterEnum test_params[] = {
    {(char *)"foo", foo_params},
    {(char *)"bar", bar_params},
    {(char *)"baz", NULL},
    {NULL, NULL},
};

/* Creating a test suite is pretty simple.  First, you'll need an
 * array of tests: */
static MunitTest test_suite_tests[] = {
    {/* The name is just a unique human-readable way to identify the
      * test. You can use it to run a specific test if you want, but
      * usually it's mostly decorative. */
     (char *)"/example/compare",
     /* You probably won't be surprised to learn that the tests are
      * functions. */
     test_compare,
     /* If you want, you can supply a function to set up a fixture.  If
      * you supply NULL, the user_data parameter from munit_suite_main
      * will be used directly.  If, however, you provide a callback
      * here the user_data parameter will be passed to this callback,
      * and the return value from this callback will be passed to the
      * test function.
      *
      * For our example we don't really need a fixture, but lets
      * provide one anyways. */
     test_compare_setup,
     /* If you passed a callback for the fixture setup function, you
      * may want to pass a corresponding callback here to reverse the
      * operation. */
     test_compare_tear_down,
     /* Finally, there is a bitmask for options you can pass here.  You
      * can provide either MUNIT_TEST_OPTION_NONE or 0 here to use the
      * defaults. */
     MUNIT_TEST_OPTION_NONE,
     NULL},
    /* Usually this is written in a much more compact format; all these
     * comments kind of ruin that, though.  Here is how you'll usually
     * see entries written: */
    {(char *)"/example/rand", test_rand, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    /* To tell the test runner when the array is over, just add a NULL
     * entry at the end. */
    {(char *)"/example/parameters", test_parameters, NULL, NULL, MUNIT_TEST_OPTION_NONE, test_params},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* If you wanted to have your test suite run other test suites you
 * could declare an array of them.  Of course each sub-suite can
 * contain more suites, etc. */
/* static const MunitSuite other_suites[] = { */
/*   { "/second", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE }, */
/*   { NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE } */
/* }; */

/* Now we'll actually declare the test suite.  You could do this in
 * the main function, or on the heap, or whatever you want. */
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
