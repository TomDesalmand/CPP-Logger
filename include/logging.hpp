#ifndef CPP_LOGGER_LOGGING_HPP
#define CPP_LOGGER_LOGGING_HPP

#include <unordered_map>
#include <string>
#include <utility>
#include <iostream>

#include "utils.hpp"

namespace cpp_logging {

    class Logger {
        public:
            struct Type {
                int code{};
                std::string label;
                RGB color;
            };
        
            Logger();
            void create_type(const std::string& type_name, int code, RGB color, std::string label = {});
            void create_type(const std::string& type_name, int code, int r, int g, int b, std::string label = {});
        
            template <typename... Args>
            void log_by_type(const std::string& type_name, Args&&... args);
        
        private:
            std::unordered_map<std::string, Type> _types;
    };
    
    Logger& implicit_logger();
    
    template <typename... Args>
    void Logger::log_by_type(const std::string& type_name, Args&&... args) {
        auto it = _types.find(type_name);
        if (it == _types.end())
            return;
    
        const Type& t = it->second;
    
    #if defined(LOG_LEVEL)
        if (t.code > LOG_LEVEL)
            return;
    #endif
    
        std::ostream& os = std::cerr;
        os << '[' << ansi_fg_rgb(t.color) << t.label << ansi_reset() << "] ";
        (os << ... << std::forward<Args>(args)) << '\n';
        os.flush();
    }

}

#if defined(LOG_LEVEL)
  #define LOG_SHOULD_LOG(CODE) ((CODE) <= (LOG_LEVEL))
#else
  #define LOG_SHOULD_LOG(CODE) (true)
#endif

// Declare a logging callable as an inline templated function so it has proper
// linkage across translation units. This avoids the pitfalls of defining
// a lambda (or non-inline object) in a header which leads to multiple- or
// missing-definition issues when used from other TUs.
#define LOG_DECLARE_TYPE(NAME) \
    template<typename... Args> \
    inline void NAME(Args&&... _args) { \
        ::cpp_logging::implicit_logger().log_by_type(#NAME, std::forward<Args>(_args)...); \
    }

#define LOG_DEFINE_TYPE(NAME, CODE, R, G, B) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (R), (G), (B)));

#define LOG_DEFINE_TYPE_LABELED(NAME, CODE, R, G, B, LABEL) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (R), (G), (B), (LABEL)));

#define LOG_DEFINE_TYPE_RGB(NAME, CODE, RGBVAL) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (RGBVAL)));

#define LOG_DEFINE_TYPE_LABELED_RGB(NAME, CODE, RGBVAL, LABEL) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (RGBVAL), (LABEL)));

#define LOG_UPDATE_TYPE(NAME, CODE, R, G, B) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (R), (G), (B)))

#define LOG_UPDATE_TYPE_LABELED(NAME, CODE, R, G, B, LABEL) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (R), (G), (B), (LABEL)))

#define LOG_UPDATE_TYPE_RGB(NAME, CODE, RGBVAL) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (RGBVAL)))

#define LOG_UPDATE_TYPE_LABELED_RGB(NAME, CODE, RGBVAL, LABEL) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (RGBVAL), (LABEL)))

#endif // CPP_LOGGER_LOGGING_HPP
