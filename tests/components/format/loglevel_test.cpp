#include "../../include/test_common.hpp"
#include <cassert>
#include <unistd.h>

static bool test_loglevel_implementation() {
    cpp_logging::implicit_logger().create_type("LL_LOW", 1, 255, 255, 255, "LL_LOW", "[{label}]: {context}");
    cpp_logging::implicit_logger().create_type("LL_HIGH", 5, 255, 255, 255, "LL_HIGH", "[{label}]: {context}");

    LL_LOW("This log should display on log level 1, low level.");
    LL_HIGH("This log should display on log level 5, high level.");

    assert(true);
    return true;
}

bool test_loglevel() {
    return test_loglevel_implementation();
}