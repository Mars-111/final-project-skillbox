#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "ConverterJSON.h"

using json = nlohmann::json;

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(ConverterJSON, GetTextDocuments)
{
    std::ifstream fs("C:\\develop\\C++ CLion\\search_engine_new\\res\\config.json");
    json js = json::parse(fs);
    fs.close();
    std::vector<std::string> res = {"1", "2", "3", "", "", "", "", "", "", ""};

    EXPECT_TRUE(ConverterJSON::GetTextDocuments(js) == res);
}

TEST(ConverterJSON, GetTextDocumentsNoTread) //ВЫИГРЫВАЕТ ПО СКОРОСТИ И НАДЕЖНОСТИ
{
    std::ifstream fs("C:\\develop\\C++ CLion\\search_engine_new\\res\\config.json");
    json js = json::parse(fs);
    fs.close();
    std::vector<std::string> res = {
            "london is the capital of great britain",
            "paris is the capital of france",
            "berlin is the capital of germany",
            "rome is the capital of italy",
            "madrid is the capital of spain",
            "lisboa is the capital of portugal",
            "bern is the capital of switzerland",
            "moscow is the capital of russia",
            "kiev is the capital of ukraine",
            "minsk is the capital of belarus"
    };

    EXPECT_TRUE(ConverterJSON::GetTextDocuments(js) == res);
}

TEST(ConverterJSON, GetResponsesLimit)
{
    std::ifstream fs("C:\\develop\\C++ CLion\\search_engine_new\\res\\config.json");
    json js = json::parse(fs);
    fs.close();

    EXPECT_TRUE(ConverterJSON::GetResponsesLimit(js) == 5);
}

TEST(ConverterJSON, GetRequests)
{
    std::ifstream fs("C:\\develop\\C++ CLion\\search_engine_new\\res\\requests.json");
    json js = json::parse(fs);
    fs.close();
    std::vector<std::string> res = {"some words1..", "some words2..", "some words3..", "some words4.."};

    EXPECT_TRUE(ConverterJSON::GetRequests(js) == res);
}

TEST(ConverterJSON, putAnswers)
{
    std::string path = "C:\\develop\\C++ CLion\\search_engine_new\\tests\\tst_ConverterJSON\\answers.json";
    std::vector<std::vector<std::pair<int, double>>> answers_sorted = {{{2, 0.989}, {2, 0.979}, {1, 0.955}}, {{5, 0.987}}, {{1, 0.989}, {4, 0.779}}};
    ConverterJSON::PutAnswers(path, answers_sorted);
    EXPECT_TRUE(true);
}