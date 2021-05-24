cmake_minimum_required(VERSION 3.16)
project(cal-proj)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest-master)
add_subdirectory(${GOOGLETEST_PATH})

# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp-master)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

# Build pbPlots
set(PBPLOTS_PATH lib/pbPlots-master)
include_directories(${PBPLOTS_PATH})

# Add the source files of each TP class
#file(GLOB TEST CONFIGURE_DEPENDS
#        "test.cpp"
#        "src/Point.cpp" "src/Position.cpp" "src/Graph.h" "src/GraphViewerLoader.cpp" "src/GraphViewerLoader.h"
#        "test/PositionTest.cpp" "test/PointTest.cpp" "test/GraphTest.cpp" "test/GraphViewerLoaderTest.cpp" "test/GraphGenerator.h"
#        )

file(GLOB MAIN CONFIGURE_DEPENDS
        "main.cpp"
        "src/*.cpp"
        )

add_executable(test
        test.cpp
        src/Point.cpp src/Position.cpp src/Graph.cpp src/GraphViewerLoader.cpp
        test/PositionTest.cpp test/PointTest.cpp test/GraphTest.cpp test/GraphViewerLoaderTest.cpp
        test/GraphGenerator.cpp test/GraphViewerTest.cpp src/GraphLoader.cpp src/GraphLoader.h test/GraphLoaderTest.cpp test/ChristofidesTest.cpp
        lib/pbPlots-master/pbPlots.cpp
        lib/pbPlots-master/pbPlots.h
        lib/pbPlots-master/supportLib.cpp
        lib/pbPlots-master/supportLib.h)

add_executable(main
        ${MAIN})

target_link_libraries(test gtest_main gmock_main graphviewer)
target_link_libraries(main graphviewer)