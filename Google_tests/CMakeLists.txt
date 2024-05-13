project(Google_tests)
add_subdirectory(lib)

set(CMAKE_OSX_ARCHITECTURES "x86_64")
list(APPEND CMAKE_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
set(CMAKE_CXX_STANDARD 11)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(Google_Tests_run UtilsTests.cpp SolversTests.cpp)

# linking Google_Tests_run with which will be tested
target_link_libraries(Google_Tests_run NQueens_lib)
target_link_libraries(Google_Tests_run gtest gtest_main)
