#include <gtest/gtest.h>
#include <string>

/*
 * The program should answer "Fizz" if the input number is multiple of 3, Buzz - if you specify
 *  a number which is multiple of 5,
 * and FizzBuzz - if the number is a multiple of 3 and 5. In other cases the program should
 * not answer. So, the conditions are:
 * a multiple of 3 = Fizz
 * a multiple of 5 = Buzz
 * a multiple of 15 = FizzBuzz
 * any other number = <nothing>
*/

std::string FizzBuzz(int n)
{
    std::string result = "";

    if (n%3 == 0)
        result += "Fizz";
    if (n%5 == 0)
        result += "Buzz";

    return result;
}

TEST(testFizzBuzz, ReturnFizzWhenNumber3)
{
    ASSERT_EQ(FizzBuzz(3), "Fizz");
}

TEST(testFizzBuzz, ReturnFizzWhenNumber6)
{
    ASSERT_EQ(FizzBuzz(6), "Fizz");
}

TEST(testFizzBuzz, ReturnBuzzWhenNumber5)
{
    ASSERT_EQ(FizzBuzz(5), "Buzz");
}

TEST(testFizzBuzz, ReturnFizzBuzzWhen15)
{
    ASSERT_EQ(FizzBuzz(15), "FizzBuzz");
}

TEST(testFizzBuzz, returnEmptyWhenNotDivisibleeBy3or5)
{
    ASSERT_EQ(FizzBuzz(322), "");
}