# final-project-skillbox
Дипломная работа курса Skillbox. 

## Содержание
- [Установка](#Установка)
- [Использование](#Использование)
- [Требования](#Требования)
- [Команда проекта](#команда-проекта)

## Установка
Для утановки search engine вам необходимо:

1. Соберать проект с помощью CMake.
2. создать папку "res" с файлами внутри:
  * config.json
  * requests.json
    Примеры содержимого config.json и requests.json вы можете найти в папке res в проекте или же в [Использование](#Использование).
3. Переместить папку res в один каталог с собранным search_engine.exe

У вас должно получиться:

![Итог](https://github.com/Mars-111/final-project-skillbox/blob/main/for_readme.png)

После выполнения этих 3 пунтов вы можете взаимодействовать с прогрммой.

## Использование

Перед использованием, убедитесь что вы выполнили [Установка](#Установка).

Пример описания файла config.json:
```json
{
  "config": {
    "name": "SkillboxSearchEngine",
    "version": "0.1",
    "max_responses": 5
  },
  "files": [
    "../resources/file001.txt",
    "../resources/file002.txt",
    "../resources/file003.txt",
    "../resources/file004.txt"
  ]
}
```

Подробнее разберём каждое поле файла config.json:
* config — общая информация, без которой приложение не запускается. Если это
поле отсутствует, то при старте программа выбросит исключение и
выведит в текстовую консоль ошибку config file is empty. Если отсутствует сам
файл config.json, то програма выбросит исключение config
file is missing.
* name — поле с названием поискового движка. Оно может быть любым.
* version — поле с номером версии поискового движка.
* max_responses — поле, определяющее максимальное количество ответов на
один запрос.
* files содержит пути к файлам, по которым осуществляется поиск.
Внутри списка files лежат пути к файлам.

Пример описания файла config.json:
```json
{
  "requests": [
    "some words..",
    "some words..",
    "some words..",
    "some words.."
  ]
}
```

Подробнее разберём каждое поле файла requests.json:
* requests состоит из списка запросов, которые необходимо обработать
поисковым движком. Поле содержит не более 1000 запросов, каждый из
которых включает от одного до десяти слов.




### Требования
Для установки и запуска проекта, необходим CMake версией не ниже 3.14.


## Команда проекта

- [Арсений Фильков](https://t.me/Senya4445)
