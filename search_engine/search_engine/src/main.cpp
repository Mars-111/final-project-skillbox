#include <iostream>
#include "nlohmann/json.hpp"
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <regex>

const std::string path_to_res = "res/";

int main()
{

    std::ifstream ifs_config(path_to_res + "config.json");
    std::ifstream ifs_requests(path_to_res + "requests.json");
    if (!ifs_config.is_open())
        throw std::invalid_argument("config file is missing");
    if (!ifs_requests.is_open())
        throw std::invalid_argument("requests file is missing");

    nlohmann::json config = nlohmann::json::parse(ifs_config);
    nlohmann::json requests = nlohmann::json::parse(ifs_requests);

    ifs_config.close();
    ifs_requests.close();


    InvertedIndex inv;
    inv.UpdateDocumentBase(ConverterJSON::GetTextDocuments(config));

    SearchServer ss(inv);
    auto final_search =
            SearchServer::AnswerSearchToPair(
                    ss.Search(ConverterJSON::GetRequests(requests),
                              ConverterJSON::GetResponsesLimit(config))
            );


    ConverterJSON::PutAnswers(
            path_to_res + "answers.json",
            final_search
    );


    return 0;
}