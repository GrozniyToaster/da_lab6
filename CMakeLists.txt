cmake_minimum_required(VERSION 3.0.0)
project(calculator VERSION 0.1.0)

#set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_executable(calculator main.cpp big_integer.cpp big_integer_tools.cpp)
target_compile_options(calculator PRIVATE -Wall -Wextra)


add_executable( TestCalculator big_integer.cpp big_integer_tools.cpp test/GTestCalc.cpp)
target_link_libraries( TestCalculator ${GTEST_LIBRARIES} Threads::Threads )


enable_testing()
add_test(TestCalculator "./TestCalculator")