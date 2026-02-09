#ifndef CPP_LOGGER_TEST_COMMON_HPP
#define CPP_LOGGER_TEST_COMMON_HPP

#include "../../include/logging.hpp"
#include "../../include/utils.hpp"

// Users define their own macros
#define INFO(...) \
    ::cpp_logging::implicit_logger().log_by_type("INFO", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define ERROR(...) \
    ::cpp_logging::implicit_logger().log_by_type("ERROR", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define DEBUG(...) \
    ::cpp_logging::implicit_logger().log_by_type("DEBUG", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define WARN(...) \
    ::cpp_logging::implicit_logger().log_by_type("WARN", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
    
#define TRACE(...) \
    ::cpp_logging::implicit_logger().log_by_type("TRACE", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
    
#define LL_LOW(...) \
    ::cpp_logging::implicit_logger().log_by_type("LL_LOW", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define LL_HIGH(...) \
    ::cpp_logging::implicit_logger().log_by_type("LL_HIGH", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
    
#define RGB(...) \
    ::cpp_logging::implicit_logger().log_by_type("RGB", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
    
#define TIMETEST(...) \
    ::cpp_logging::implicit_logger().log_by_type("TIMETEST", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#endif // CPP_LOGGER_TEST_COMMON_HPP