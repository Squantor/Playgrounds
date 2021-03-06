/*
The MIT License (MIT)

Copyright (c) 2018 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "minunit.h"
#include "cmdline.h"

void test_setup(void) {
}

void test_teardown(void) {
	/* Nothing */
}

char commandHelp[] = "help\n";

MU_TEST(testParseHelpCommand)
{
    mu_assert(cmdlineParse(commandHelp) == noError, "cmdlineParse should return noError");
}

char commandTest[] = "test 0x100 1024\n";

MU_TEST(testParseTestCommand)
{
    mu_assert(cmdlineParse(commandTest) == noError, "cmdlineParse should return noError");
}

char positiveIntArg[] = "123";
char negativeIntArg[] = "-123";
char hexArg[] = "0xC4f3BaB3";

MU_TEST(testParseHex)
{
    int output;
    mu_assert(cmdlineParseHex(hexArg, &output) == noError, "cmdlineParseHex should return noError");
    mu_assert_int_eq(0xC4f3BaB3, output);
}

MU_TEST(testParsePositiveInt)
{
    int output;
    mu_assert(cmdlineParseInt(positiveIntArg, &output) == noError, "cmdlineParseInt should return noError");
    mu_assert_int_eq(123, output);
}

MU_TEST(testParseNegativeInt)
{
    int output;
    mu_assert(cmdlineParseInt(negativeIntArg, &output) == noError, "cmdlineParseInt should return noError");
    mu_assert_int_eq(-123, output);
}

MU_TEST_SUITE(test_suite) 
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(testParsePositiveInt);
    MU_RUN_TEST(testParseNegativeInt);
    MU_RUN_TEST(testParseHex);
    MU_RUN_TEST(testParseTestCommand);
    MU_RUN_TEST(testParseHelpCommand);
}

int main(int argc, char *argv[]) 
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
