#include "SearchServer.h"
#include <algorithm>




std::vector<std::vector<RelativeIndex>> SearchServer::Search(const std::vector<std::string> &queries_input, size_t max_responses = 5)
{
    std::vector<std::vector<RelativeIndex>> result;
    result.resize(queries_input.size());

    for (size_t i = 0; i < queries_input.size(); i++)
    {
        std::vector<Entry> vec = _index.GetWordCount(queries_input[i]);
        if (vec.empty()) continue;
        //std::sort(vec.begin(), vec.end(), std::greater<Entry>()); //Sort by count
        std::stable_sort(vec.begin(), vec.end(), std::greater<Entry>());
        if (vec.size() > max_responses)
            vec.resize(max_responses);
        size_t maxAbsoluteRelevance = vec[0].count;
        for (auto & j : vec)
        {
            result[i].emplace_back(RelativeIndex{j.doc_id, static_cast<double>(j.count)/static_cast<double>(maxAbsoluteRelevance)});
        }
    }

    return result;
}

std::vector<std::vector<std::pair<int, double>>>
SearchServer::AnswerSearchToPair(std::vector<std::vector<RelativeIndex>> answer_search)
{
    std::vector<std::vector<std::pair<int, double>>> answer;
    answer.resize(answer_search.size());
    for (size_t i = 0; i < answer.size(); ++i) {
        answer[i].resize(answer_search[i].size());
        for (int j = 0; j < answer[i].size(); ++j) {
            answer[i][j] = answer_search[i][j].to_pair();
        }
    }
    return answer;
}
