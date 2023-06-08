#include <unity.h>

#include "Global.h"
#include "Message.h"
#include "Error.h"

void setUp()
{
}

void tearDown()
{
    restartError();
    restartMessage();
}

void test_add_error_simple()
{
    addError(ERROR_PARSE_NUMBER, "error while parse command with number");

    TEST_ASSERT_EQUAL(ERROR_PARSE_NUMBER, error.errorCode);
    TEST_ASSERT_EQUAL(0, error.printfError);
    TEST_ASSERT_EQUAL_STRING("error while parse command with number", error.errorMessage);
}

void test_add_error_no_message()
{
    addError(ERROR_PARSE_NUMBER, "");
    TEST_ASSERT_EQUAL(ERROR_PARSE_NUMBER, error.errorCode);
    TEST_ASSERT_EQUAL(0, error.printfError);
    TEST_ASSERT_EQUAL_STRING("", error.errorMessage);
}

void test_add_error_null_message()
{
    addError(ERROR_PARSE_NUMBER, nullptr);
    TEST_ASSERT_EQUAL(ERROR_INPUT, error.errorCode);
    TEST_ASSERT_EQUAL(0, error.printfError);
    TEST_ASSERT_EQUAL_STRING("addError | wrong input (0)", error.errorMessage);
}

void test_add_error_long_message()
{
    addError(ERROR_PARSE_NUMBER, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    TEST_ASSERT_EQUAL(ERROR_PARSE_NUMBER, error.errorCode);
    TEST_ASSERT_EQUAL(0, error.printfError);
    char expected[ERROR_MESSAGE_SIZE];

    memset(expected, 'a', ERROR_MESSAGE_SIZE);
    expected[ERROR_MESSAGE_SIZE - 1] = '\0';

    TEST_ASSERT_EQUAL_STRING(expected, error.errorMessage);
}

void test_add_error_too_many_args()
{
    addError(ERROR_PARSE_NUMBER, "%d %d %d", 1, 2, 3, 4);
    TEST_ASSERT_EQUAL(0, error.printfError);
    TEST_ASSERT_EQUAL(ERROR_PARSE_NUMBER, error.errorCode);
    TEST_ASSERT_EQUAL_STRING("1 2 3", error.errorMessage);
}

void test_add_error_not_enough_args()
{
    addError(ERROR_PARSE_NUMBER, "%d %d %d", 1, 2);
    TEST_ASSERT_EQUAL(ERROR_PARSE_NUMBER, error.errorCode);
    TEST_ASSERT_EQUAL(0, error.printfError);
    TEST_ASSERT(strstr(error.errorMessage, "1 2") != nullptr);
}

void test_restart_error()
{
    addError(ERROR_PARSE_NUMBER, "error while parse command with number");
    TEST_ASSERT_EQUAL(ERROR_PARSE_NUMBER, error.errorCode);
    TEST_ASSERT_EQUAL(0, error.printfError);
    TEST_ASSERT_EQUAL_STRING("error while parse command with number", error.errorMessage);

    restartError();
    TEST_ASSERT_EQUAL(NONE, error.errorCode);
    TEST_ASSERT_EQUAL(0, error.printfError);
    TEST_ASSERT_EQUAL_STRING("", error.errorMessage);
}

void run_error_test()
{
    RUN_TEST(test_add_error_simple);
    RUN_TEST(test_add_error_no_message);
    RUN_TEST(test_add_error_null_message);
    RUN_TEST(test_add_error_long_message);
    RUN_TEST(test_add_error_too_many_args);
    RUN_TEST(test_add_error_not_enough_args);
}

#include "Message.h"
#include "Global.h"

void test_add_message_simple()
{
    addMessage("This is message");
    TEST_ASSERT_EQUAL(1, messages.numOfMessages);
    TEST_ASSERT_EQUAL_STRING("This is message", messages.messages[0]);
}

void test_add_message_no_message()
{
    addMessage("");
    TEST_ASSERT_EQUAL(1, messages.numOfMessages);
    TEST_ASSERT_EQUAL_STRING("", messages.messages[0]);
}

void test_add_message_null_message()
{
    addMessage(nullptr);
    TEST_ASSERT_EQUAL(ERROR_INPUT, error.errorCode);
    TEST_ASSERT_EQUAL_STRING("addMessage | wrong input fmt == nullptr", error.errorMessage);
    TEST_ASSERT_EQUAL(0, messages.numOfMessages);
}

void test_add_message_long_message()
{
    addMessage("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    char expected[ERROR_MESSAGE_SIZE];
    memset(expected, 'a', ERROR_MESSAGE_SIZE);
    expected[ERROR_MESSAGE_SIZE - 1] = '\0';

    TEST_ASSERT_EQUAL(1, messages.numOfMessages);
    TEST_ASSERT_EQUAL_STRING(expected, messages.messages[0]);
}

void test_add_message_too_many_args()
{
    addMessage("%d %d %d", 1, 2, 3, 4);
    TEST_ASSERT_EQUAL(1, messages.numOfMessages);
    TEST_ASSERT_EQUAL_STRING("1 2 3", messages.messages[0]);
}

void test_add_message_not_enough_args()
{
    addMessage("%d %d %d", 1, 2);
    TEST_ASSERT_EQUAL(1, messages.numOfMessages);
    TEST_ASSERT(strstr(messages.messages[0], "1 2") != nullptr);
}

void test_add_message_overflow_error()
{
    for (int i = 0; i < MESSAGE_NUM + 1; ++i)
        addMessage("%d", i);

    TEST_ASSERT_EQUAL(ERROR_MESSAGE_OVERFLOW, error.errorCode);
    TEST_ASSERT_EQUAL_STRING("addMessage | message overflow: %d", error.errorMessage);
    TEST_ASSERT_EQUAL(MESSAGE_NUM, messages.numOfMessages);
    char expected[MESSAGE_SIZE] = "\0";
    for (int i = 0; i < MESSAGE_NUM; ++i)
    {
        itoa(i, expected, 10);
        TEST_ASSERT_EQUAL_STRING(expected, messages.messages[i]);
    }
}

void test_restart_message()
{
    for (int i = 0; i < MESSAGE_NUM; ++i)
        addMessage("%d", i);

    TEST_ASSERT_EQUAL(MESSAGE_NUM, messages.numOfMessages);
    char expected[MESSAGE_SIZE] = "\0";
    for (int i = 0; i < MESSAGE_NUM; ++i)
    {
        itoa(i, expected, 10);
        TEST_ASSERT_EQUAL_STRING(expected, messages.messages[i]);
    }

    restartMessage();

    TEST_ASSERT_EQUAL(0, messages.numOfMessages);
    for (int i = 0; i < MESSAGE_NUM; ++i)
        TEST_ASSERT_EQUAL_STRING("", messages.messages[i]);
}

void run_message_test()
{
    RUN_TEST(test_add_message_simple);
    RUN_TEST(test_add_message_no_message);
    RUN_TEST(test_add_message_null_message);
    RUN_TEST(test_add_message_long_message);
    RUN_TEST(test_add_message_too_many_args);
    RUN_TEST(test_add_message_not_enough_args);
    RUN_TEST(test_add_message_overflow_error);
    RUN_TEST(test_restart_message);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    run_error_test();
    run_message_test();
    UNITY_END();
    return 0;
}
