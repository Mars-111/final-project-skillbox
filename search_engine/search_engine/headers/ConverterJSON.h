#pragma once
#include <vector>
#include <string>
#include "nlohmann/json.hpp"



class ConverterJSON {

public:
    ConverterJSON() = default;
    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    * в config.json
    */
    static std::vector<std::string> GetTextDocuments(nlohmann::json& config);
    static std::vector<std::string> GetTextDocumentsTread(nlohmann::json& config);
    /**
    * Метод считывает поле max_responses для определения предельного
    * количества ответов на один запрос
    * @return
    */
    static int GetResponsesLimit(nlohmann::json& config);
    /**
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
    static std::vector<std::string> GetRequests(nlohmann::json& requests);
    /**
    * Положить в файл answers.json результаты поисковых запросов
    */
    static void PutAnswers(std::string path_to_answers, const std::vector<std::vector<std::pair<int, double>>>& answers_sorted);
};
