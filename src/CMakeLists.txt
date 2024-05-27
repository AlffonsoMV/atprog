project(NQueens)

set(HEADER_FILES
        Board.h
        Solver.h
        Solvers/BacktrackingSolver.h
        Solvers/SimulatedAnnealingSolver.h
        Solvers/GeneticSolver.h
        Solvers/MinConflictsSolver.h
)

set(SOURCE_FILES
        Board.cpp
        Solvers/BacktrackingSolver.cpp
        Solvers/GeneticSolver.cpp
        Solvers/SimulatedAnnealingSolver.cpp
        Solvers/MinConflictsSolver.cpp
)

add_library(NQueens_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
