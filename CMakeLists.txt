cmake_minimum_required(VERSION 3.4)
project(Tp7_Initial)

set(CMAKE_OSX_ARCHITECTURES "x86_64")
list(APPEND CMAKE_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
set(CMAKE_CXX_STANDARD 11)

find_package(Imagine REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(NQueens_run ${SOURCE_FILES})
target_link_libraries(NQueens_run Imagine::Graphics)
target_link_libraries(NQueens_run Imagine::Images)

include_directories(src)
add_subdirectory(src)

target_link_libraries(NQueens_run NQueens_lib)

add_subdirectory(Google_tests)
