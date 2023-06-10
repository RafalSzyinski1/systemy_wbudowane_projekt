#include <unity.h>

#include "Global.h"
#include "Message.h"
#include "Error.h"
#include "Parser.h"
#include "MCommand.h"
#include "GCommand.h"

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
    addError(ERROR_CHECKSUM, "error while parse command with number");

    TEST_ASSERT_EQUAL(ERROR_CHECKSUM, error.errorCode);
    TEST_ASSERT_EQUAL(0, error.printfError);
    TEST_ASSERT_EQUAL_STRING("error while parse command with number", error.errorMessage);
}

void test_add_error_no_message()
{
    addError(ERROR_CHECKSUM, "");
    TEST_ASSERT_EQUAL(ERROR_CHECKSUM, error.errorCode);
    TEST_ASSERT_EQUAL(0, error.printfError);
    TEST_ASSERT_EQUAL_STRING("", error.errorMessage);
}

void test_add_error_null_message()
{
    addError(ERROR_CHECKSUM, nullptr);
    TEST_ASSERT_EQUAL(ERROR_INPUT, error.errorCode);
    TEST_ASSERT_EQUAL(0, error.printfError);
    TEST_ASSERT_EQUAL_STRING("addError | wrong input (0)", error.errorMessage);
}

void test_add_error_long_message()
{
    addError(ERROR_CHECKSUM, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    TEST_ASSERT_EQUAL(ERROR_CHECKSUM, error.errorCode);
    TEST_ASSERT_EQUAL(0, error.printfError);
    char expected[ERROR_MESSAGE_SIZE];

    memset(expected, 'a', ERROR_MESSAGE_SIZE);
    expected[ERROR_MESSAGE_SIZE - 1] = '\0';

    TEST_ASSERT_EQUAL_STRING(expected, error.errorMessage);
}

void test_add_error_too_many_args()
{
    addError(ERROR_CHECKSUM, "%d %d %d", 1, 2, 3, 4);
    TEST_ASSERT_EQUAL(0, error.printfError);
    TEST_ASSERT_EQUAL(ERROR_CHECKSUM, error.errorCode);
    TEST_ASSERT_EQUAL_STRING("1 2 3", error.errorMessage);
}

void test_add_error_not_enough_args()
{
    addError(ERROR_CHECKSUM, "%d %d %d", 1, 2);
    TEST_ASSERT_EQUAL(ERROR_CHECKSUM, error.errorCode);
    TEST_ASSERT_EQUAL(0, error.printfError);
    TEST_ASSERT(strstr(error.errorMessage, "1 2") != nullptr);
}

void test_restart_error()
{
    addError(ERROR_CHECKSUM, "error while parse command with number");
    TEST_ASSERT_EQUAL(ERROR_CHECKSUM, error.errorCode);
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

void test_parseCommandWithFloat()
{
    float result = 0.0;
    TEST_ASSERT_EQUAL(0, parseCommandWithFloat("G1 X100.0 E0.6*68", "G", &result));
    TEST_ASSERT_EQUAL(1, (int)result);
    TEST_ASSERT_EQUAL(0, parseCommandWithFloat("G1 X100.0 E0.6*68", "X", &result));
    TEST_ASSERT_EQUAL_FLOAT(100.0, result);
    TEST_ASSERT_EQUAL(0, parseCommandWithFloat("G1 X100.0 E0.6*68", "E", &result));
    TEST_ASSERT_EQUAL_FLOAT(0.6, result);
    TEST_ASSERT_EQUAL(2, parseCommandWithFloat("G X Y Z", "G", &result));
    TEST_ASSERT_EQUAL(2, parseCommandWithFloat("G X Y Z", "X", &result));
    TEST_ASSERT_EQUAL(2, parseCommandWithFloat("G X Y Z", "Y", &result));
    TEST_ASSERT_EQUAL(2, parseCommandWithFloat("G X Y Z", "Z", &result));

    TEST_ASSERT_EQUAL(0, parseCommandWithFloat("G1 X100.0 E0.6*68", "G", nullptr));

    TEST_ASSERT_EQUAL(-1, parseCommandWithFloat("G1 X100.0 E0.6*68", nullptr, nullptr));
    TEST_ASSERT_EQUAL(ERROR_INPUT, error.errorCode);
}

void test_deleteComments()
{
    char command[] = "G1 X100.0 E0.6*68; its G1 command";
    deleteComments(command);
    TEST_ASSERT_EQUAL_STRING("G1 X100.0 E0.6*68", command);
    char command2[] = ";no command";
    deleteComments(command2);
    TEST_ASSERT_EQUAL_STRING("", command2);
    char command3[] = "G1 X100.0 E0.6*68";
    deleteComments(command3);
    TEST_ASSERT_EQUAL_STRING("G1 X100.0 E0.6*68", command);
}

void test_calculateChecksum()
{
    TEST_ASSERT_EQUAL(15, calculateChecksum("N-1 M110*15"));
    TEST_ASSERT_EQUAL(58, calculateChecksum("N0 T0*58"));
    TEST_ASSERT_EQUAL(0, calculateChecksum(""));
    TEST_ASSERT_EQUAL(0, calculateChecksum(nullptr));
}

void test_parseCheckSum()
{
    TEST_ASSERT_EQUAL(0, parseCheckSum("N-1 M110*15"));
    TEST_ASSERT_EQUAL(0, parseCheckSum("N0 T0*58"));
    TEST_ASSERT_EQUAL(0, parseCheckSum(""));
    TEST_ASSERT_EQUAL(0, parseCheckSum(nullptr));

    TEST_ASSERT_EQUAL(-1, parseCheckSum("N0 T0*"));
    TEST_ASSERT_EQUAL(NONE, error.errorCode);
    TEST_ASSERT_EQUAL(-1, parseCheckSum("N0 T0*57"));
    TEST_ASSERT_EQUAL(ERROR_CHECKSUM, error.errorCode);
    error.errorCode = NONE;
    TEST_ASSERT_EQUAL(-1, parseCheckSum("N0 T0*59"));
    TEST_ASSERT_EQUAL(ERROR_CHECKSUM, error.errorCode);
    error.errorCode = NONE;
    TEST_ASSERT_EQUAL(-1, parseCheckSum("N0 T0*-1"));
    TEST_ASSERT_EQUAL(ERROR_CHECKSUM, error.errorCode);
}

void test_NCommand()
{
    parserState.lastNumberLine = -1;
    parserState.mState = MNone;
    float params[PARAM_COUNT];
    for (size_t i = G; i < PARAM_COUNT; ++i)
        params[i] = NAN;

    params[N] = -1;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    TEST_ASSERT_EQUAL(-1, parserState.lastNumberLine);
    params[N] = 0;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    TEST_ASSERT_EQUAL(-1, parserState.lastNumberLine);
    params[N] = 8;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    TEST_ASSERT_EQUAL(-1, parserState.lastNumberLine);
    params[N] = -1;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    TEST_ASSERT_EQUAL(-1, parserState.lastNumberLine);

    parserState.mState = M110;

    params[N] = -1;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    TEST_ASSERT_EQUAL(-1, parserState.lastNumberLine);
    params[N] = 0;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    TEST_ASSERT_EQUAL(0, parserState.lastNumberLine);
    params[N] = 1;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    TEST_ASSERT_EQUAL(1, parserState.lastNumberLine);
    params[N] = 2;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    TEST_ASSERT_EQUAL(2, parserState.lastNumberLine);

    params[N] = 3;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    TEST_ASSERT_EQUAL(3, parserState.lastNumberLine);

    params[N] = NAN;
    params[M] = 105;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    params[G] = 1;
    params[M] = NAN;
    TEST_ASSERT_EQUAL(0, NCommand(params));

    params[N] = 4;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    params[N] = 5;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    params[G] = 0;

    params[N] = 0;
    TEST_ASSERT_EQUAL(-1, NCommand(params));
    TEST_ASSERT_EQUAL(ERROR_NLINE, error.errorCode);

    params[M] = 110;
    MCommand(params);
    params[M] = NAN;
    error.errorCode = NONE;

    params[N] = -1;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    TEST_ASSERT_EQUAL(-1, parserState.lastNumberLine);
    params[N] = 0;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    TEST_ASSERT_EQUAL(0, parserState.lastNumberLine);
    params[N] = 1;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    TEST_ASSERT_EQUAL(1, parserState.lastNumberLine);
    params[N] = 2;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    TEST_ASSERT_EQUAL(2, parserState.lastNumberLine);

    params[N] = 3;
    TEST_ASSERT_EQUAL(0, NCommand(params));
    TEST_ASSERT_EQUAL(3, parserState.lastNumberLine);
    params[N] = 0;
    TEST_ASSERT_EQUAL(-1, NCommand(params));
    TEST_ASSERT_EQUAL(ERROR_NLINE, error.errorCode);
    error.errorCode = NONE;
}

void test_TCommand()
{
    float params[PARAM_COUNT];
    for (size_t i = G; i < PARAM_COUNT; ++i)
        params[i] = NAN;

    params[T] = T0;
    TEST_ASSERT_EQUAL(0, TCommand(params));
    params[N] = -1;
    TEST_ASSERT_EQUAL(0, TCommand(params));
    params[T] = 1;
    TEST_ASSERT_EQUAL(-1, TCommand(params));
    TEST_ASSERT_EQUAL(ERROR_TOOL, error.errorCode);
    error.errorCode = NONE;
    params[X] = 100;
    TEST_ASSERT_EQUAL(0, TCommand(params));
    params[T] = T0;
    TEST_ASSERT_EQUAL(0, TCommand(params));
}

void run_parser_test()
{
    RUN_TEST(test_parseCommandWithFloat);
    RUN_TEST(test_deleteComments);
    RUN_TEST(test_calculateChecksum);
    RUN_TEST(test_parseCheckSum);
    RUN_TEST(test_NCommand);
    RUN_TEST(test_TCommand);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    // run_error_test();
    // run_message_test();
    run_parser_test();
    UNITY_END();
    return 0;
}
