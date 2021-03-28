cmake_minimum_required(VERSION 3.17)
project(CAL-TP_classes)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest-master)
add_subdirectory(${GOOGLETEST_PATH})

# Add the source files of each TP class
file(GLOB TP1_FILES CONFIGURE_DEPENDS
        "test/*.cpp"
        )

add_executable(test
        test.cpp
        ${TP1_FILES} src/Printer.h)

target_link_libraries(test gtest_main gmock_main)