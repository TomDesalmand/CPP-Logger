#ifndef CPP_LOGGER_UTILS_HPP
#define CPP_LOGGER_UTILS_HPP

#include <cstdint>
#include <string>

struct RGB {
    std::uint8_t r{};
    std::uint8_t g{};
    std::uint8_t b{};
};

#ifdef _WIN32
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif
  #include <windows.h>
#endif

void enable_virtual_terminal_processing_once();
std::string ansi_fg_rgb(const RGB& color);
const char* ansi_reset() noexcept;
void log_test();

#endif // CPP_LOGGER_UTILS_HPP
