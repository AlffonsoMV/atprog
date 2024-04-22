project(NQueens)

set(HEADER_FILES
        Board.h
        Solver.h
        Solvers/BacktrackingSolver.h
)

set(SOURCE_FILES
        Board.cpp
        Solvers/BacktrackingSolver.cpp
)

add_library(NQueens_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})