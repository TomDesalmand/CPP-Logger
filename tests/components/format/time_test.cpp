#include "../../include/test_common.hpp"
#include <cassert>
#include <unistd.h>

static bool test_time_implementation() {
    cpp_logging::implicit_logger().create_type("TIMETEST", 1, 255, 255, 255, "TIMETEST", "[{rgb, 0, 0, 0}{time}{rgb, reset}][{label}]: {context}");

    TIMETEST("Timestamp should be present for this message.");
    sleep(1);
    TIMETEST("Timestamp present again but 1 second later.");

    assert(true);
    return true;
}

bool test_time() {
    return test_time_implementation();
}