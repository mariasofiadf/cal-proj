cmake_minimum_required(VERSION 3.17)
project(CAL-TP_classes)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest-master)
add_subdirectory(${GOOGLETEST_PATH})

# Add the source files of each TP class
file(GLOB TEST CONFIGURE_DEPENDS
        "test/*.cpp"
        )

file(GLOB MAIN CONFIGURE_DEPENDS
        "main.cpp"
        )

file(GLOB MAIN CONFIGURE_DEPENDS
        "src/*.cpp"
        )

add_executable(test
        test.cpp
        ${TEST} src/Printer.h)

add_executable(main
        main.cpp
        ${MAIN} )

target_link_libraries(test gtest_main gmock_main)