#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
#project(Timer)
#
#add_library(Timer SHARED Timer/Timer.h Timer/Timer.cpp)
#target_include_directories(Timer PUBLIC Timer)


add_subdirectory(tst_ConverterJSON)
add_subdirectory(tst_InvertedIndex)
add_subdirectory(tst_SearchServer)