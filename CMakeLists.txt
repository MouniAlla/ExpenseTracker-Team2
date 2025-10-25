# cpp/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(ExpenseTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(expense_tracker_v2
    src/main.cpp
    src/expense_store.cpp
)

# Add test subdirectory
add_subdirectory(test)
