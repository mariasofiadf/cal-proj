cmake_minimum_required(VERSION 3.17)
project(cal-proj)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest-master)
add_subdirectory(${GOOGLETEST_PATH})

# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

# Add the source files of each TP class
#file(GLOB TEST CONFIGURE_DEPENDS
#        "test.cpp"
#        "src/Point.cpp" "src/Position.cpp" "src/Graph.h" "src/GraphViewerLoader.cpp" "src/GraphViewerLoader.h"
#        "test/PositionTest.cpp" "test/PointTest.cpp" "test/GraphTest.cpp" "test/GraphViewerLoaderTest.cpp" "test/GraphGenerator.h"
#        )

file(GLOB MAIN CONFIGURE_DEPENDS
        "main.cpp"
        "src/Position.cpp" "src/Position.h" "src/Point.cpp" "src/Point.h" "src/Graph.h"
        )

add_executable(test
        test.cpp
        src/Point.cpp src/Position.cpp src/Graph.cpp src/GraphViewerLoader.cpp
        test/PositionTest.cpp test/PointTest.cpp test/GraphTest.cpp test/GraphViewerLoaderTest.cpp test/GraphGenerator.h
        )

add_executable(main
        ${MAIN})

target_link_libraries(test gtest_main gmock_main graphviewer)