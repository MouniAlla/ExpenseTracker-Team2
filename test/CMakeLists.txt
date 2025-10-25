# test/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(../include)
include_directories(../src)

# Create test executables
add_executable(expense_tracker_tests
    test_main.cpp
)

add_executable(expense_store_tests
    test_expense_store.cpp
)

# Set output directory
set_target_properties(expense_tracker_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test
)

set_target_properties(expense_store_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test
)
