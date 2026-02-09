#include "../../include/test_common.hpp"
#include <cassert>
#include <unistd.h>

static bool test_trace_implementation() {
    cpp_logging::implicit_logger().create_type("TRACE", 1, 255, 255, 255, "TRACE", "{file}:{line} [{label}]: {context}");
    TRACE("Basic clickable tracing log.");
    
    cpp_logging::implicit_logger().create_type("TRACE", 1, 255, 255, 255, "TRACE", "[{label}]: {context}");
    auto loop_function = []() {
        for (int i = 0; i < 3; i++) {
            TRACE("This log should be a trace within a lambda loop function at {file}:{line} on iteration: ", i);
        }
    };
    loop_function();
    
    TRACE("This log should give the full path to the logging call file path inlcuded: {filepath}:{function}:{line}");
    
    assert(true);
    return true;
}

bool test_trace() {
    return test_trace_implementation();
}