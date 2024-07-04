cmake_minimum_required(VERSION 3.14)

project(search_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(libraries/nlohmann_json)

add_subdirectory(search_engine)
add_subdirectory(tests)