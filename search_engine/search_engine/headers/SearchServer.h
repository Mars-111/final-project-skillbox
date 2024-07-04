#pragma once
#include "InvertedIndex.h"


struct RelativeIndex {
    size_t doc_id;
    double rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
    std::pair<int, double> to_pair()
    {
        return std::pair<int, double>(static_cast<int>(doc_id), rank);
    }
};

class SearchServer {
public:
/**
* @param idx в конструктор класса передаётся ссылка на класс
InvertedIndex,
* чтобы SearchServer мог узнать частоту слов встречаемых в
запросе
*/
    SearchServer(InvertedIndex& idx) : _index(idx) { };
/**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла
requests.json
* @return возвращает отсортированный список релевантных ответов для
заданных запросов
*/
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input, size_t max_responses);

    static std::vector<std::vector<std::pair<int, double>>> answer_search_to_pair(std::vector<std::vector<RelativeIndex>> answer_search);
private:
    InvertedIndex _index;
};
