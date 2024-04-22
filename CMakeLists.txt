cmake_minimum_required(VERSION 3.4)
project(Tp7_Initial)

set(CMAKE_OSX_ARCHITECTURES "x86_64")
list(APPEND CMAKE_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
set(CMAKE_CXX_STANDARD 11)

find_package(Imagine REQUIRED COMPONENTS Graphics)

add_executable( Tron
    main.cpp snake.cpp utils.cpp
    utils.h snake.h
                consts.h
                board.h
                )
target_link_libraries(Tron Imagine::Graphics)
