#include "../../include/test_common.hpp"
#include <cassert>
#include <unistd.h>

static bool test_basic_implementation() {
    cpp_logging::implicit_logger().create_type("ERROR", 0, 255, 0, 0, "ERROR");
    cpp_logging::implicit_logger().create_type("WARN", 0, 255, 205, 0, "WARN");
    cpp_logging::implicit_logger().create_type("INFO", 1, 0, 155, 255, "INFO");
    cpp_logging::implicit_logger().create_type("DEBUG", 2, 75, 75, 75, "DEBUG");

    ERROR("This is an error log at log level 0.");
    WARN("This is an warning log at log level 0.");
    INFO("This is an information log at log level 1.");
    DEBUG("This is an debuging log at log level 2.");

    assert(true);
    return true;
}

bool test_basic() {
    return test_basic_implementation();
}