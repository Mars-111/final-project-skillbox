#include "InvertedIndex.h"

#include <utility>
#include <thread>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>

InvertedIndex::InvertedIndex(InvertedIndex const &other) :
        docs(other.docs), freq_dictionary(other.freq_dictionary)    {   }

void emplaceSortedEntry(std::vector<Entry>& vec, Entry entry)
{
    for (auto it = vec.begin(); it != vec.end(); it++) {
        if (entry.doc_id < it->doc_id)
        {
            vec.emplace(it, entry);
            return;
        }
    }
    vec.emplace_back(entry);
}

std::string strToLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::tolower(c); }
    );
    return s;
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs)
{
    freq_dictionary.clear();

    docs = std::move(input_docs);

    std::vector<std::thread> threads;
    threads.reserve(docs.size());

    for (size_t i = 0; i < docs.size(); i++) {

        threads.emplace_back([this, i]() {

            std::regex regular(R"(\w+)");
            std::map<std::string, size_t> words;
            for (std::sregex_iterator it(docs[i].begin(), docs[i].end(), regular); it != std::sregex_iterator(); it++) {
                std::string str = strToLower(it->str());
                words[str]++;
            }

            for (auto &word : words)
            {
                mutex_freq.lock();
                emplaceSortedEntry(freq_dictionary[word.first], Entry{i, word.second});
                mutex_freq.unlock();
            }
        });
    } 

    for (auto& thread : threads) {
        thread.join();
    }

}

std::vector<std::string> getManyWords(const std::string &words) {
    std::vector<std::string> result;
    result.reserve(2);
    std::regex regular(R"(\w+)");

    for (std::sregex_iterator it(words.begin(), words.end(), regular); it != std::sregex_iterator(); it++) {
        result.push_back(it->str());
    }
    return result;
}

std::vector<Entry> InvertedIndex::GetWordCount(std::string word)
{
    word = strToLower(std::move(word));
    if (word.find(" ") != std::string::npos)
    {
        std::vector<std::string> words = getManyWords(word);
        std::map<size_t, size_t> map_words;

        for (size_t i = 0; i < words.size(); i++)
        {
            for (size_t j = 0; j < freq_dictionary[words[i]].size(); j++)
            {
                map_words[freq_dictionary[words[i]][j].doc_id] += freq_dictionary[words[i]][j].count;
            }
        }
        std::vector<Entry> result;
        result.reserve(map_words.size());
        for (auto it : map_words)
        {
            result.emplace_back(Entry{it.first, it.second});
        }
        return result;
    }

    return freq_dictionary.find(word)!=freq_dictionary.end() ? freq_dictionary[word] : std::vector<Entry>();
}
