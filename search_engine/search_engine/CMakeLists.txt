cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SRC_FILE src/main.cpp src/ConverterJSON.cpp src/InvertedIndex.cpp src/SearchServer.cpp)
set(HEADERS_FILE headers/ConverterJSON.h headers/InvertedIndex.h headers/SearchServer.h)


add_executable(search_engine
        ${SRC_FILE} ${HEADERS_FILE}
)


target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)


target_include_directories(search_engine
    PUBLIC src
           headers
)