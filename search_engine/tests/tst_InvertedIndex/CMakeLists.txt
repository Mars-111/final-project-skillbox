cmake_minimum_required(VERSION 3.14)
project(tst_InvertedIndex)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

##include ConverterJSON
set(FILE_CONVERTERJSON
        "../../search_engine/src/InvertedIndex.cpp"
        "../../search_engine/headers/InvertedIndex.h"
)
##

add_executable(
        tst_InvertedIndex
        tst_InvertedIndex.cpp
        ${FILE_CONVERTERJSON}
)

##include ConverterJSON
target_include_directories(tst_InvertedIndex PUBLIC "../../search_engine/src" "../../search_engine/headers")
##

target_link_libraries(
        tst_InvertedIndex
        GTest::gtest_main
        nlohmann_json::nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(tst_InvertedIndex)