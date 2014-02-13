cmake_minimum_required(VERSION 2.8)

set(test_src TestMain.cpp 
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
)

INCLUDE_DIRECTORIES(../src)

add_executable(tests ${test_src})

add_definitions(-fprofile-arcs -ftest-coverage)

target_link_libraries (tests gtest gtest_main pthread -fprofile-arcs)

