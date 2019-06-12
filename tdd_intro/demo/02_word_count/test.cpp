/*
Given a phrase, count the occurrences of each word in that phrase. Ignore whitespaces and punctual symbols
For example for the input "olly olly in come free please please let it be in such manner olly"
olly: 3
in: 2
come: 1
free: 1
please: 2
let: 1
it: 1
be: 1
manner: 1
such: 1
*/

//Test plan
//
// Cut string line into vector of words
//
//1. Send one word, result vector of one string
//2. Send two words with space, result vector of 2 strings
//3. Send two words with ,  == 2 string vector
//4. Send three words with . == 3 string vector
//5. Send 2 words . and space result 2 string vector
//
// Calculate words and add it to map
//
//1. Send olly get olly : 1 whitespace
//2. Send pig olly restult pig : 1  olly : 1
//3. Send olly olly result olly:2
//4. send olly pig olly blue result olly:2   pig:1 blue:1
//5. send blue olly pig olly olly blue result olly:3   pig:1 blue:2

#include <gtest/gtest.h>
#include <string>
#include <map>
#include <vector>

std::vector<std::string> cutToWords(std::string str) {
    std::vector<std::string> punctualSymbols = {" ", ",", "."};
    std::vector<std::string> returnVector;
    size_t index = std::string::npos;
    do {

        for (auto punctual: punctualSymbols) {
            index = str.find(punctual);
            if (index != std::string::npos)
                break;
        }
        if (index != std::string::npos) {
            returnVector.push_back(str.substr(0, index));
            str = str.substr(index + 1);
        } else {
            returnVector.push_back(str);
            str = "";
        }
    } while (str != "");
    return returnVector;
}

TEST(cutString, oneWordToVector) {
    std::string str = "developer";
    std::vector<std::string> strVector = {"developer"};
    ASSERT_EQ(cutToWords(str), strVector );
}

TEST(cutString, twoWordsToVectorSpace) {
    std::string str = "developer pizza";
    std::vector<std::string> strVector = {"developer", "pizza"};
    ASSERT_EQ(cutToWords(str), strVector );
}

TEST(cutString, twoWordsToVectorComa) {
    std::string str = "developer,pizza";
    std::vector<std::string> strVector = {"developer", "pizza"};
    ASSERT_EQ(cutToWords(str), strVector );
}

TEST(cutString, threeWordsToVectorpoint) {
    std::string str = "developer.pizza.ocean";
    std::vector<std::string> strVector = {"developer", "pizza", "ocean"};
    ASSERT_EQ(cutToWords(str), strVector );
}

