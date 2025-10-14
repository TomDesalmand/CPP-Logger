#include "../../include/test_common.hpp"
#include <string>
#include <cassert>

// Declare inline logging callables so we can call INFO(...), ERROR(...), etc.
// In real practice these would be declared in a shared header.
LOG_DECLARE_TYPE(INFO)
LOG_DECLARE_TYPE(ERROR)
LOG_DECLARE_TYPE(DEBUG)
LOG_DECLARE_TYPE(WARN)
LOG_DECLARE_TYPE(CUSTOM)

using namespace cpp_logging;

static bool test_create_and_call_macros_impl() {
    LOG_DEFINE_TYPE_LABELED(INFO,  1,   0, 200, 100, "INFO");
    LOG_DEFINE_TYPE_LABELED(ERROR, 0, 200,   0,   0, "ERROR");
    LOG_DEFINE_TYPE_LABELED(DEBUG, 2, 150, 150, 150, "DEBUG");
    LOG_DEFINE_TYPE_LABELED(WARN,  1, 255, 165,   0, "WARN");

    INFO("InfoPrefix: ", 123);
    ERROR("Err(", 5, "): ", "oops");
    DEBUG("D", 'B', 3.14);
    WARN("Watch out!");

    LOG_DEFINE_TYPE_LABELED_RGB(CUSTOM, 1, (RGB{123, 45, 67}), "CUSTOM_LABEL");
    CUSTOM("CustomMsg", '#', 77);

    assert(true);

    return true;
}

bool test_create_and_call_macros() {
    return test_create_and_call_macros_impl();
}