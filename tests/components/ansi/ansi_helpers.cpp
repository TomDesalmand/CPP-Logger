#include "../../include/test_common.hpp"
#include <cassert>

using namespace cpp_logging;

static bool test_ansi_helpers_impl() {
    RGB sample{10, 20, 30};
    std::string seq = ansi_fg_rgb(sample);
    const char* reset = ansi_reset();

    // Basic sanity checks using assert
    assert(!seq.empty());
    assert(reset != nullptr);
    assert(reset[0] != '\0');

    // Sequence should start with ESC '[' (0x1b '[')
    assert(seq.size() >= 2 && seq[0] == '\x1b' && seq[1] == '[');

    // Expect 24-bit color CSI prefix "38;2;"
    assert(seq.find("38;2;") != std::string::npos);

    // Ensure the numeric components are present
    assert(seq.find("10") != std::string::npos);
    assert(seq.find("20") != std::string::npos);
    assert(seq.find("30") != std::string::npos);

    // Ends with 'm' for SGR parameter terminator
    assert(!seq.empty() && seq.back() == 'm');

    // Reset should contain ESC and '0' (typical "\x1b[0m")
    std::string reset_s(reset ? reset : "");
    assert(reset_s.find("\x1b") != std::string::npos);
    assert(reset_s.find("0") != std::string::npos);

    // Calling the enable function multiple times must be safe (no-op on non-Windows).
    enable_virtual_terminal_processing_once();
    enable_virtual_terminal_processing_once();

    return true;
}

bool test_ansi_helpers() {
    return test_ansi_helpers_impl();
}