/*
Bob answers 'Sure.' if you ask him a question. (? in the end)
He answers 'Whoa, chill out!' if you yell at him. (! in the end)
He says 'Fine. Be that way!' if you address him without actually saying anything.
He answers 'Whatever.' to anything else.
*/
#include <gtest/gtest.h>
#include <string>

static const char* s_whateverAnswer = "Whatever.";
static const char* s_sureAnswer = "Sure.";
static const char* s_fineAnswer = "Fine. Be that way!";
static const char* s_chillOutAnswer = "Whoa, chill out!";
char getLastSymbolForNonEmptyString(const std::string& str)
{
    return str.at(str.size() - 1);
}

std::string sayBob(const std::string& query)
{
    std::string result;
    if (query.empty())
    {
        result = s_fineAnswer;
    }
    else if (getLastSymbolForNonEmptyString(query) == '!')
    {
        result = s_chillOutAnswer;
    }
    else if (getLastSymbolForNonEmptyString(query) == '?')
    {
        result = s_sureAnswer;
    }
    else
    {
        result = s_whateverAnswer;
    }

    return result;
}

TEST(test_Bob, onQuestionsBobAnswersSure)
{
    ASSERT_EQ(sayBob("How are you?"), s_sureAnswer);
}

TEST(test_Bob, onYellAtBobAnswerIsChillOut)
{
    ASSERT_EQ(sayBob("WTF!"), s_chillOutAnswer);
}

TEST(test_Bob, onSayNothingAnswerShouldBeFine)
{
    ASSERT_EQ(sayBob(""), s_fineAnswer);
}

TEST(test_Bob, whatIsYourNameAnswersSure)
{
    ASSERT_EQ(sayBob("What is your name?"), s_sureAnswer);
}

TEST(test_Bob, claimSignAnswerChillOut)
{
    ASSERT_EQ(sayBob("!"), s_chillOutAnswer);
}

TEST(test_Bob, questionMarkAnswerSure)
{
    ASSERT_EQ(sayBob("?"), s_sureAnswer);
}

TEST(test_Bob, simpleSentenceBobAnswersWhatever)
{
    ASSERT_EQ(sayBob("hey bob."), s_whateverAnswer);
}