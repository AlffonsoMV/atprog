project(NQueens)

set(HEADER_FILES
        Board.h
        Solver.h
        Solvers/BacktrackingSolver.h
)

set(SOURCE_FILES
        Board.cpp
        Solvers/BacktrackingSolver.cpp
        Solvers/GeneticSolver.cpp
        Solvers/SimulatedAnnealingSolver.h
        Solvers/SimulatedAnnealingSolver.cpp
        Solvers/MinConflictsSolver.cpp
)

add_library(NQueens_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})