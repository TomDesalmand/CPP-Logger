#include "../include/test_common.hpp"
#include <cassert>

extern bool test_create_and_call_macros();
extern bool test_ansi_helpers();
extern bool test_log_level_macro();
extern bool test_rgb_format();

int main() {
    assert(test_create_and_call_macros());
    assert(test_ansi_helpers());
    assert(test_log_level_macro());
    assert(test_rgb_format());
    return 0;
}