cmake_minimum_required(VERSION 3.17)
project(cluster_improving C)

set(CMAKE_C_STANDARD 99)
set(GCC_COVERAGE_COMPILE_FLAGS "-ansi -Wall -Wextra -Werror -pedantic-errors" )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
add_executable(cluster_improving main.c Utility.c Utility.h vector.c vector.h Algorithm2.c Algorithm2.h B.c B.h Common.c Common.h ModularityGroupsDivision.c ModularityGroupsDivision.h SparseMatrix.c SparseMatrix.h Stack.c)