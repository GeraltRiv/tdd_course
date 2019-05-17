/*
Given a year, report if it is a leap year.

The tricky thing here is that a leap year in the Gregorian calendar occurs:

on every year that is evenly divisible by 4
  except every year that is evenly divisible by 100
    unless the year is also evenly divisible by 400

For example, 1997 is not a leap year, but 1996 is. 1900 is not a leap year, but 2000 is.

If your language provides a method in the standard library that does this look-up, pretend it doesn't exist and implement it yourself.
*/

#include <gtest/gtest.h>

bool isYearLeap(int year) {
    if (year%4 == 0 && year%100 != 0)
        return true;
    else
        return false;
}

TEST(leapYear, testYear1999NotALeap) {
    ASSERT_EQ(isYearLeap(1999), false);
}

TEST(leapYear, testYear2000ALeap) {
    ASSERT_EQ(isYearLeap(2000), true);
}

TEST(leapYear, testYear2020ALeap) {
    ASSERT_EQ(isYearLeap(2020), true);
}

TEST(leapYear, testYear1800NotALeap) {
    ASSERT_EQ(isYearLeap(1800), false);
}
