#include "../../include/test_common.hpp"
#include <cassert>

// Declare inline logging callables for this test.
LOG_DECLARE_TYPE(LINE_TEST)

using namespace cpp_logging;

static bool test_file_impl() {
    LOG_DEFINE_TYPE_FORMAT(
        LINE_TEST,
        1,
        255, 255, 255,
        "{rgb,80,80,80,0.5}{file}{rgb,reset} {label}: {context}"
    );

    LINE_TEST("Line number should be present for this this.");

    assert(true);
    return true;
}

bool test_file() {
    return test_file_impl();
}