#include <unity.h>

#include "Error.h"
#include "Global.h"

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_add_error_simple()
{
    addError(ERROR_PARSE_NUMBER, "error while parse command with number");

    TEST_ASSERT_EQUAL(ERROR_PARSE_NUMBER, error.errorCode);
    TEST_ASSERT_EQUAL_STRING("error while parse command with number", error.errorMessage);
}

void test_add_error_no_message()
{
    addError(ERROR_PARSE_NUMBER, "");
    TEST_ASSERT_EQUAL(ERROR_PARSE_NUMBER, error.errorCode);
    TEST_ASSERT_EQUAL_STRING("", error.errorMessage);
}

void test_add_error_null_message()
{
    addError(ERROR_PARSE_NUMBER, nullptr);
    TEST_ASSERT_EQUAL(ERROR_INPUT, error.errorCode);
    TEST_ASSERT_EQUAL_STRING("addError | wrong input (0)", error.errorMessage);
}

void test_add_error_long_message()
{
    addError(ERROR_PARSE_NUMBER, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    TEST_ASSERT_EQUAL(ERROR_PARSE_NUMBER, error.errorCode);
    char expected[ERROR_MESSAGE_SIZE];

    memset(expected, 'a', ERROR_MESSAGE_SIZE);
    expected[ERROR_MESSAGE_SIZE - 1] = '\0';

    TEST_ASSERT_EQUAL_STRING(expected, error.errorMessage);
}

void test_add_error_too_many_args()
{
    addError(ERROR_PARSE_NUMBER, "%d %d %d", 1, 2, 3, 4);
    TEST_ASSERT_EQUAL(ERROR_PARSE_NUMBER, error.errorCode);
    TEST_ASSERT_EQUAL_STRING("1 2 3", error.errorMessage);
}

void test_add_error_not_enough_args()
{
    addError(ERROR_PARSE_NUMBER, "%d %d %d", 1, 2);
    TEST_ASSERT_EQUAL(ERROR_PARSE_NUMBER, error.errorCode);
    TEST_ASSERT_EQUAL_STRING("1 2 0", error.errorMessage);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_add_error_simple);
    RUN_TEST(test_add_error_no_message);
    RUN_TEST(test_add_error_null_message);
    RUN_TEST(test_add_error_long_message);
    RUN_TEST(test_add_error_too_many_args);
    RUN_TEST(test_add_error_not_enough_args);
    UNITY_END();

    return 0;
}