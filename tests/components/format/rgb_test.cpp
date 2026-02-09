#include "../../include/test_common.hpp"
#include <cassert>
#include <unistd.h>

static bool test_rgb_implementation() {
    cpp_logging::implicit_logger().create_type("RGB", 1, 255, 255, 255, "RGB", "[{label}]: {context}");

    RGB("This log shows how {rgb, 255, 0, 0}R{rgb, reset}{rgb, 0, 255, 0}G{rgb, reset}{rgb, 0, 0, 255}B{rgb, reset} system works a how you can {bold}bold{unbold} the text as well.");

    assert(true);
    return true;
}

bool test_rgb() {
    return test_rgb_implementation();
}