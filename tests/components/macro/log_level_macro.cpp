#include "../../include/test_common.hpp"
#include <string>
#include <cassert>

// Declare inline callables for the log types used by this test.
// In real practice these would be declared in a shared header.
LOG_DECLARE_TYPE(LL_LOW)
LOG_DECLARE_TYPE(LL_HIGH)

using namespace cpp_logging;

bool test_log_level_macro() {
    const int low_code  = 1;
    const int mid_code  = 500;
    const int high_code = 1000;

    bool low_should  = LOG_SHOULD_LOG(low_code);
    bool mid_should  = LOG_SHOULD_LOG(mid_code);
    bool high_should = LOG_SHOULD_LOG(high_code);

    assert(!(high_should && !mid_should));
    assert(!(mid_should && !low_should));

    LOG_DEFINE_TYPE_LABELED(LL_LOW,  low_code,  10,  20,  30,  "LL_LOW");
    LOG_DEFINE_TYPE_LABELED(LL_HIGH, high_code, 200, 100,  50,  "LL_HIGH");

    LL_LOW("low_message_", 42);
    LL_HIGH("high_message_", 99);

    return true;
}