#include "../../include/test_common.hpp"
#include <cassert>

// Declare inline logging callables for this test.
LOG_DECLARE_TYPE(TIMETEST)

using namespace cpp_logging;

static bool test_time_impl() {
    LOG_DEFINE_TYPE_FORMAT(
        TIMETEST,
        1,
        255, 255, 255,
        "{rgb,80,80,80,0.5}{time}{rgb,reset} {label}: {context}"
    );

    TIMETEST("Timestamp should be present for this message.");
    TIMETEST("Timestamp present again.");

    assert(true);
    return true;
}

bool test_time() {
    return test_time_impl();
}