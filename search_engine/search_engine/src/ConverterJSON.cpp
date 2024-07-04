#include "ConverterJSON.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>

std::vector<std::string> ConverterJSON::GetTextDocuments(nlohmann::json &config)
{
    if (!config.contains("files")) throw std::invalid_argument("config file is empty. [files field not found]");

    std::vector<std::string> result;
    int config_size = config["files"].size();
    result.reserve(config_size);

    for (int i = 0; i < config_size; i++)
    {
        result.emplace_back();

        std::ifstream file(config["files"][i], std::ios::binary); //мьютекс надо
        if (!file.is_open()) //МОЖНО ЕЩЕ ДОБАВИТЬ ПРОВЕРКУ НА ФАИЛ И БАД
        {
            std::cout<<config["files"][i].get<std::string>()<<". does not exist. This file is ignored.\n";
        }
        else
        {
            std::stringstream buffer;
            buffer << file.rdbuf();
            result[i] = buffer.str();
            //std::getline(file, result[i]);
        }
        file.close();
    }

    return result;
}

std::vector<std::string> ConverterJSON::GetTextDocumentsTread(nlohmann::json& config)
{
    if (!config.contains("files")) throw std::invalid_argument("config file is empty.");

    std::mutex result_mutex;
    std::vector<std::string> result;
    std::vector<std::thread> thread;
    size_t config_size = config["files"].size();
    result.reserve(config_size);
    thread.reserve(config_size);

    for (size_t i = 0; i < config_size; i++)
    {
        thread.emplace_back([&result, config, &result_mutex](size_t i)
        {
            result_mutex.lock();
            result.emplace_back();
            result_mutex.unlock();
            std::ifstream file(config["files"][i], std::ios::binary); //мьютекс надо
            if (!file.is_open()) //МОЖНО ЕЩЕ ДОБАВИТЬ ПРОВЕРКУ НА ФАИЛ И БАД
            {
                std::cout<<config["files"][i].get<std::string>()<<"does not exist. This file is ignored.";
            }
            else
            {
                std::getline(file, result[i]);
            }
            file.close();
        }, i);
        //thread[i].detach();
    }

    for (auto& i : thread) {
        if (i.joinable())
            i.join(); //ERROR
    }

    return result;
} //ДОБАВИТЬ МНОГОПОТОЧНОСТЬ

int ConverterJSON::GetResponsesLimit(nlohmann::json &config)
{
    if (!config.contains("config") && !config["config"].contains("max_responses"))
        throw std::invalid_argument("config file is empty");
    return config["config"]["max_responses"].get<int>();
}

std::vector<std::string> ConverterJSON::GetRequests(nlohmann::json &requests)
{
    if (!requests.contains("requests")) throw std::invalid_argument("requests file is empty");
    std::vector<std::string> res;
    size_t requests_size = requests["requests"].size();
    res.reserve(requests_size);
    for (size_t i = 0; i < requests_size; i++)
    {
        res.push_back(requests["requests"][i].get<std::string>());
    }
    return res;
}

std::string get_number_for_putAnswers(unsigned int num)
{
    if (num < 10)
        return "00"+ std::to_string(num);
    else if (num < 99)
        return "0" + std::to_string(num);
    return std::to_string(num);
}

void ConverterJSON::PutAnswers(std::string path_to_answers, const std::vector<std::vector<std::pair<int, double>>>& answers_sorted)
{
    nlohmann::json json_answers;
    for (size_t i = 0; i < answers_sorted.size(); i++)
    {
        json_answers["answers"]["request" + get_number_for_putAnswers(i)]["result"] = static_cast<bool>(answers_sorted[i].size()); //Если answers_sorted[i].size() == 0, то false
        if (answers_sorted[i].size() == 1)
        {
            json_answers["answers"]["request" + get_number_for_putAnswers(i)]["docid"] = answers_sorted[i][0].first;
            json_answers["answers"]["request" + get_number_for_putAnswers(i)]["rank"] = answers_sorted[i][0].second;
        }
        else
        {
            for (int j = 0; j < answers_sorted[i].size(); j++)
            {
                json_answers["answers"]["request" + get_number_for_putAnswers(i)]["relevance"][j] =
                        {{"docid", answers_sorted[i][j].first},{"rank", answers_sorted[i][j].second}};
            }
        }

    }
    std::ofstream f(path_to_answers, std::ios::binary);
    f.write(json_answers.dump(4).c_str(), json_answers.dump(4).size());
    f.close();
}

void ConverterJSON::CheckValidConfig(nlohmann::json &config)
{
    if (!config.contains("config")) throw std::invalid_argument("config file is empty.");
    if (!config.contains("files")) throw std::invalid_argument("config file is empty.");
    if (!config["config"].contains("name")) throw std::invalid_argument("config file does not have a 'name' field.");
    if (!config["config"].contains("version")) throw std::invalid_argument("config file does not have a 'version' field.");
    if (!config["config"].contains("max_responses")) throw std::invalid_argument("config file does not have a 'max_responses' field.");

    if (config["config"]["max_responses"].get<int>() < 0) throw std::invalid_argument("max_responses < 0.");
}

void ConverterJSON::CheckValidRequests(nlohmann::json &requests)
{
    if (!requests.contains("requests")) throw std::invalid_argument("requests file is empty.");
}

std::string ConverterJSON::GetConfigName(nlohmann::json &config) {
    if (!config.contains("config")) throw std::invalid_argument("config file is empty.");
    if (!config["config"].contains("name")) throw std::invalid_argument("config file does not have a 'name' field.");
    return config["config"]["name"].get<std::string>();
}

std::string ConverterJSON::GetConfigVersion(nlohmann::json &config) {
    if (!config.contains("config")) throw std::invalid_argument("config file is empty.");
    if (!config["config"].contains("version")) throw std::invalid_argument("config file does not have a 'version' field.");
    return config["config"]["version"].get<std::string>();
}
