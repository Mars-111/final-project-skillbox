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

    try {
        std::ifstream ifs_config(path_to_res + "config.json");
        std::ifstream ifs_requests(path_to_res + "requests.json");

        if (!ifs_config.is_open()) {
            throw std::invalid_argument("config file is missing");
        }
        if (!ifs_requests.is_open()) {
            throw std::invalid_argument("requests file is missing");
        }

        nlohmann::json config = nlohmann::json::parse(ifs_config);
        nlohmann::json requests = nlohmann::json::parse(ifs_requests);

        ifs_config.close();
        ifs_requests.close();



        std::cout<<"---"<<ConverterJSON::GetConfigName(config)<<" "<<ConverterJSON::GetConfigVersion(config)<<"---\n";



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


    } catch(std::invalid_argument& e) {
        std::cerr<<e.what()<<'\n';
        return 0;
    } catch(...) {
        std::cerr<<"Unknown error\n";
        return 0;
    }

    std::cout<<"Success\n";
    system("pause");

    return 0;
}