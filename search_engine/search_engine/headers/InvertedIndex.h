#pragma once
#include <vector>
#include <map>
#include <string>
#include <mutex>

struct Entry {
    size_t doc_id;
    size_t count;
    // Данный оператор необходим для проведения тестовых сценариев
    bool operator ==(const Entry& other) const
    {
        return (doc_id == other.doc_id && count == other.count);
    }
    bool operator >(const Entry& other) const
    {
        return count > other.count;
    }
    bool operator <(const Entry& other) const
    {
        return count < other.count;
    }
};

class InvertedIndex
{
public:
    InvertedIndex() = default;

    InvertedIndex(InvertedIndex const &other);

/**
* Обновить или заполнить базу документов, по которой будем совершать
поиск
* @param texts_input содержимое документов
*/
    void UpdateDocumentBase(std::vector<std::string> input_docs);
/**
* Метод определяет количество вхождений слова word в загруженной базе
документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов
*/
    std::vector<Entry> GetWordCount(const std::string& word);
private:
    std::vector<std::string> docs; // список содержимого документов
    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный словарь
    std::mutex mutex_freq;
};