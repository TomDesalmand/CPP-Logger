#include "../include/test_common.hpp"
#include <cassert>

extern bool test_basic();
extern bool test_trace();
extern bool test_loglevel();
extern bool test_rgb();
extern bool test_time();

int main() {
    assert(test_basic());
    assert(test_trace());
    assert(test_loglevel());
    assert(test_rgb());
    assert(test_time());
    return 0;
}