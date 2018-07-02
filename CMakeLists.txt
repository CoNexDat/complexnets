cmake_minimum_required(VERSION 3.1)
project(complexnets VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(CXX_FLAGS "-Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-long-long -I -fprofile-arcs -ftest-coverage -ggdb3")
set(CMAKE_CXX_FLAGS ${CXX_FLAGS})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Turn on automatic invocation of the MOC
set(CMAKE_AUTOMOC ON)

# Make this a GUI application on Windows
if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# Preprocessor definitions. These ones avoid loading certain modules of mili's library.
add_definitions("-DNO_BITWISE_ENUMS -DNO_PROMOTION_DISABLE -DNO_RANKER")

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets Gui Core REQUIRED)

# Generate code from ui files
qt5_wrap_ui(UI_HEADERS src/gui/forms/mainwindow.ui)
set_property(SOURCE ${UI_HEADERS} PROPERTY SKIP_AUTOMOC ON)

# Group files into categories
#[[
  Note that all src & headers are left with original paths (no variables)
  as for CLion to manage file rename & move actions.
]]
## --------------------- CORE --------------------- ##
set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/core)
set(CORE_DIR_SRC ${CORE_DIR}/src)
set(CORE_DIR_HEADERS ${CORE_DIR}/inc)

set(CORE_SRC
        src/core/src/GraphGenerator.cpp
        src/core/src/GraphWriter.cpp)

set(CORE_HEADERS
        src/core/inc/WeightedBetweenness.h
        src/core/inc/IShellIndex.h
        src/core/inc/TraverserForward.h
        src/core/inc/DirectedDegreeDistribution.h
        src/core/inc/DirectedVertexAspect.h
        src/core/inc/IntegerDistribution.h
        src/core/inc/GraphFactory.h
        src/core/inc/PropertyMap.h
        src/core/inc/AdjacencyListVertex.h
        src/core/inc/GraphWriter.h
        src/core/inc/IDegreeDistribution.h
        src/core/inc/WeightedVertexAspect.h
        src/core/inc/ConnectivityVerifier.h
        src/core/inc/IClusteringCoefficient.h
        src/core/inc/DirectedGraphAspect.h
        src/core/inc/TraverserOrdered.h
        src/core/inc/NearestNeighborsDegree.h
        src/core/inc/WeightedNearestNeighborsDegree.h
        src/core/inc/GraphGenerator.h
        src/core/inc/Betweenness.h
        src/core/inc/IBetweenness.h
        src/core/inc/Boxplotentry.h
        src/core/inc/WeightedGraphFactory.h
        src/core/inc/WeightedClusteringCoefficient.h
        src/core/inc/WeightedGraphReader.h
        src/core/inc/ShellIndex.h
        src/core/inc/GraphExceptions.h
        src/core/inc/IGraphFactory.h
        src/core/inc/DirectedNearestNeighborsDegree.h
        src/core/inc/INearestNeighborsDegree.h
        src/core/inc/DirectedClusteringCoefficient.h
        src/core/inc/MaxClique.h
        src/core/inc/DirectedGraphFactory.h
        src/core/inc/ClusteringCoefficient.h
        src/core/inc/DegreeDistribution.h
        src/core/inc/IGraphReader.h
        src/core/inc/IMaxClique.h
        src/core/inc/AdjacencyListGraph.h
        src/core/inc/IWeightedBetweenness.h
        src/core/inc/TraverserBFS.h
        src/core/inc/WeightedGraphAspect.h
        src/core/inc/StrengthDistribution.h
        src/core/inc/MolloyReedGraphReader.h
        src/core/inc/GraphReader.h
        src/core/inc/typedefs.h)


set(CORE_ALL ${CORE_SRC} ${CORE_HEADERS})

## --------------------- GUI --------------------- ##

set(GUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/gui)
set(GUI_DIR_SRC ${GUI_DIR}/src)
set(GUI_DIR_HEADERS ${GUI_DIR}/inc)

set(GUI_SRC
        src/gui/src/mainwindow.cpp
        src/gui/src/GnuplotConsole.cpp
        src/gui/src/GraphLoadingValidationDialog.cpp
        )

set(GUI_HEADERS
        src/gui/inc/mainwindow.h
        src/gui/inc/GnuplotConsole.h
        src/gui/inc/GraphLoadingValidationDialog.h
        src/gui/inc/LogBinningPolicy.h
        src/gui/inc/GrapherUtils.h
        )

set(GUI_ALL ${GUI_SRC} ${GUI_HEADERS})

## --------------------- CMD --------------------- ##
set(CMD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/cmd)
set(CMD_DIR_SRC ${CMD_DIR}/src)
set(CMD_DIR_HEADERS ${CMD_DIR}/inc)

set(CMD_SRC
        src/cmd/src/cmdline.cpp
        src/cmd/src/cmdmessages.cpp
        src/cmd/src/ProgramState.cpp
        )

set(CMD_HEADERS
        src/cmd/inc/cmdline.h
        src/cmd/inc/cmdmessages.h
        src/cmd/inc/ProgramState.h
        )

set(CMD_ALL ${CMD_SRC} ${CMD_HEADERS})
## --------------------- LIB: MILI --------------------- ##
set(LIBS_DIR lib)

set(LIB_MILI_DIR ${LIBS_DIR}/mili)
set(LIB_MILI
        ${LIB_MILI_DIR}/auto_array.h
        ${LIB_MILI_DIR}/coroutines.h
        ${LIB_MILI_DIR}/ranker.h
        ${LIB_MILI_DIR}/prepos_caller.h
        ${LIB_MILI_DIR}/promotion_disable.h
        ${LIB_MILI_DIR}/compile_assert.h
        ${LIB_MILI_DIR}/invariants.h
        ${LIB_MILI_DIR}/mili.h
        ${LIB_MILI_DIR}/prepos_printer.h
        ${LIB_MILI_DIR}/non_copyable.h
        ${LIB_MILI_DIR}/template_info.h
        ${LIB_MILI_DIR}/delete_container.h
        ${LIB_MILI_DIR}/container_utils.h
        ${LIB_MILI_DIR}/bitwise_enums.h
        ${LIB_MILI_DIR}/binary_streams.h
        ${LIB_MILI_DIR}/generic_exception.h
        ${LIB_MILI_DIR}/prepos_null.h
        ${LIB_MILI_DIR}/ranker_inline.h
        ${LIB_MILI_DIR}/loop_unrolling.h
        ${LIB_MILI_DIR}/type_mapper.h
        ${LIB_MILI_DIR}/raii.h
        ${LIB_MILI_DIR}/stream_utils.h
        ${LIB_MILI_DIR}/prepos_mutex.h
        ${LIB_MILI_DIR}/arith_utils.h
        ${LIB_MILI_DIR}/fast_list.h
        ${LIB_MILI_DIR}/metaprogramming_utils.h
        ${LIB_MILI_DIR}/properties.h
        ${LIB_MILI_DIR}/factory.h
        ${LIB_MILI_DIR}/string_utils.h
        ${LIB_MILI_DIR}/variants_set.h
        ${LIB_MILI_DIR}/random_gen.h
        )

set(LIBS_ALL ${LIB_MILI})

# Build an executable target called `complexnets`
add_executable(complexnets src/main.cpp ${CORE_ALL} ${GUI_ALL} ${CMD_ALL} ${LIBS_ALL} ${UI_HEADERS})

# Include all the necessary header directories for the `complexnets` target (only for compile time).
target_include_directories(complexnets PRIVATE ${CORE_DIR_HEADERS} ${GUI_DIR_HEADERS} ${CMD_DIR_HEADERS} ${LIBS_DIR})

# Add the Qt5 Widgets for linking
target_link_libraries(complexnets PRIVATE Qt5::Widgets Qt5::Gui Qt5::Core)

# ================================ Test executable target ================================ #

set(GTEST_ROOT vendor/googletest/googletest)

set(TEST_SRC
        test/TestMain.cpp
        test/AdjacencyListGraphTest.cpp
        test/AdjacencyListVertexTest.cpp
        test/BetweennessTest.cpp
        test/ClusteringCoefficientTest.cpp
        test/DegreeDistributionTest.cpp
        test/DirectedDegreeDistributionTest.cpp
        test/NearestNeighborsDegreeTest.cpp
        test/PropertyMapTest.cpp
        test/ShellIndexTest.cpp
        test/TraverserBFSTest.cpp
        test/TraverserForwardTest.cpp
        test/TraverserOrderedTest.cpp
        test/WeightedClusteringCoefficientTest.cpp
        test/WeightedNearestNeighborsDegreeTest.cpp
        test/DirectedClusteringCoefficientTest.cpp)

add_subdirectory(${GTEST_ROOT} gtest)

add_executable(runUnitTests ${TEST_SRC})

# Include all the necessary header directories for the `complexnets` target (only for compile time).
target_include_directories(runUnitTests PRIVATE
        ${CORE_DIR_HEADERS} ${GUI_DIR_HEADERS} ${CMD_DIR_HEADERS} ${LIBS_DIR} ${GTEST_ROOT}/include
        )

# Add the necessary libraries for linking
target_link_libraries(runUnitTests gtest gtest_main pthread)

file(COPY test/TestTrees DESTINATION .)
