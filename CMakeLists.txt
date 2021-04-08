cmake_minimum_required(VERSION 3.17)
project(cal-proj)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest-master)
add_subdirectory(${GOOGLETEST_PATH})

# Add the source files of each TP class
#file(GLOB TEST CONFIGURE_DEPENDS
#        "test/*.cpp"
#        )

file(GLOB MAIN CONFIGURE_DEPENDS
        "main.cpp"
        )

file(GLOB MAIN CONFIGURE_DEPENDS
        "src/*.cpp"
        )

add_executable(test
        test.cpp
        ${TEST} test/PositionTest.cpp test/PointTest.cpp test/GraphTest.cpp src/Point.cpp src/Position.cpp src/Graph.h )

add_executable(main
        main.cpp
        ${MAIN} src/Position.cpp src/Position.h src/Point.cpp src/Point.h src/Graph.h)

target_link_libraries(test gtest_main gmock_main)