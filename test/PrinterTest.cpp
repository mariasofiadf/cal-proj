#include "../src/Printer.h"


/// TESTS ///
#include <gtest/gtest.h>
#include "string"

using namespace std;

TEST(PrinterTests, print) {
    string string = "Hello";
    Printer printer(string);

    EXPECT_EQ(printer.print(), string);
}
