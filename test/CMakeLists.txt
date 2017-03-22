cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS})

set(GTEST_ROOT "../vendor/googletest/googletest")

set(TEST_SRC
    TestMain.cpp
    BetweennessTest.cpp
    ClusteringCoefficientTest.cpp
    NearestNeighborsDegreeTest.cpp
    DegreeDistributionTest.cpp
    TraverserForwardTest.cpp
    AdjacencyListGraphTest.cpp
    AdjacencyListVertexTest.cpp
    ShellIndexTest.cpp
    WeightedNearestNeighborsDegreeTest.cpp
    WeightedClusteringCoefficientTest.cpp
    TraverserBFSTest.cpp
    TraverserOrderedTest.cpp
    DirectedDegreeDistributionTest.cpp
)

add_subdirectory(${GTEST_ROOT} gtest)

include_directories(../src)
include_directories(${GTEST_ROOT}/include)

add_executable(runUnitTests ${TEST_SRC})

target_link_libraries(runUnitTests gtest gtest_main pthread)

file(COPY TestTrees DESTINATION .)
