cmake_minimum_required(VERSION 3.15)

project(leetcode-cpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

if(DEFINED LEETCODE_PROBLEM_ID)
  message(STATUS "Building problem = ${LEETCODE_PROBLEM_ID}")
else()
  message(FATAL_ERROR "LEETCODE_PROBLEM_ID not defined")
endif()

add_executable(${PROJECT_NAME} "src/${LEETCODE_PROBLEM_ID}.cpp")
