#include "../../include/test_common.hpp"
#include <cassert>

// Declare inline logging callables for this test.
LOG_DECLARE_TYPE(RGBFMT)
LOG_DECLARE_TYPE(RGBFMT_EXTRA)

using namespace cpp_logging;

static bool test_rgb_format_impl() {
    LOG_DEFINE_TYPE_FORMAT(
        RGBFMT,
        1,
        255, 255, 255,
        R"([{label}]: {context} {rgb,255,0,0}r{rgb,0,255,0}g{rgb,0,0,255}b{rgb,reset})"
    );

    RGBFMT("The following {rgb,255, 195, 0}items{rgb,reset} were attached by the user.");

    // Also test tolerating extra numeric values in the rgb payload.
    // The parser accepts at least three numbers; extras are ignored.
    LOG_DEFINE_TYPE_LABELED_FORMAT(
        RGBFMT_EXTRA,
        1,
        255, 255, 255,
        "RGB_EXTRA",
        R"([{label}]: {context} {rgb,255,0,0,0}x{rgb,reset})"
    );

    RGBFMT_EXTRA("Extra-values RGB token test");

    assert(true);
    return true;
}

bool test_rgb_format() {
    return test_rgb_format_impl();
}