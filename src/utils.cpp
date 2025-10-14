// Header files includes //
#include "../include/utils.hpp"

// C++ standard library includes //
#include <sstream>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

void enable_virtual_terminal_processing_once() {
#ifdef _WIN32
    static bool initialized = false;
    if (!initialized) {
        const DWORD enable = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        HANDLE handles[2] = { GetStdHandle(STD_OUTPUT_HANDLE), GetStdHandle(STD_ERROR_HANDLE) };
        for (HANDLE h : handles) {
            if (!h || h == INVALID_HANDLE_VALUE) continue;
            DWORD mode = 0;
            if (GetConsoleMode(h, &mode)) {
                mode |= enable;
                SetConsoleMode(h, mode);
            }
        }
        initialized = true;
    }
#else
    // No-op on non-Windows platforms
#endif
}

std::string ansi_fg_rgb(const RGB& c) {
    std::ostringstream oss;
    oss << "\x1b[38;2;"
        << static_cast<int>(c.r) << ';'
        << static_cast<int>(c.g) << ';'
        << static_cast<int>(c.b) << 'm';
    return oss.str();
}

const char* ansi_reset() noexcept {
    return "\x1b[0m";
}
