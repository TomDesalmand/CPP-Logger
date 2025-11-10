#ifndef CPP_LOGGER_LOGGING_HPP
#define CPP_LOGGER_LOGGING_HPP

#include <unordered_map>
#include <string>
#include <utility>
#include <sstream>

#include "utils.hpp"

namespace cpp_logging {

    class Logger {
        public:
            struct Type {
                int code{};
                std::string label;
                RGB color;
                std::string format = "[{label}]: {context}";
            };
        
            Logger();
            void create_type(const std::string& type_name, int code, RGB color, std::string label = {}, std::string format = {});
            void create_type(const std::string& type_name, int code, int r, int g, int b, std::string label = {}, std::string format = {});
            void set_format(const std::string& type_name, const std::string& format);
            template <typename... Args>
            void log_by_type(const std::string& type_name, Args&&... args);
        
        private:
            std::unordered_map<std::string, Type> _types;
            static std::string render_format(const Type& type, const std::string& message, const std::string& fmt);
            void log_by_type_message(const std::string& type_name, const std::string& message);
    };
    
    Logger& implicit_logger();
    
    template <typename... Args>
    void Logger::log_by_type(const std::string& type_name, Args&&... args) {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        log_by_type_message(type_name, oss.str());
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

#define LOG_DEFINE_TYPE_FORMAT(NAME, CODE, R, G, B, FORMAT) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (R), (G), (B), std::string(), (FORMAT)))

#define LOG_DEFINE_TYPE_LABELED_FORMAT(NAME, CODE, R, G, B, LABEL, FORMAT) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (R), (G), (B), (LABEL), (FORMAT)))

#define LOG_DEFINE_TYPE_RGB_FORMAT(NAME, CODE, RGBVAL, FORMAT) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (RGBVAL), std::string(), (FORMAT)))

#define LOG_DEFINE_TYPE_LABELED_RGB_FORMAT(NAME, CODE, RGBVAL, LABEL, FORMAT) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (RGBVAL), (LABEL), (FORMAT)))

#define LOG_UPDATE_TYPE(NAME, CODE, R, G, B) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (R), (G), (B)))

#define LOG_UPDATE_TYPE_LABELED(NAME, CODE, R, G, B, LABEL) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (R), (G), (B), (LABEL)))

#define LOG_UPDATE_TYPE_RGB(NAME, CODE, RGBVAL) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (RGBVAL)))

#define LOG_UPDATE_TYPE_LABELED_RGB(NAME, CODE, RGBVAL, LABEL) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (RGBVAL), (LABEL)))

#define LOG_UPDATE_TYPE_FORMAT(NAME, CODE, R, G, B, FORMAT) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (R), (G), (B), std::string(), (FORMAT)))

#define LOG_UPDATE_TYPE_LABELED_FORMAT(NAME, CODE, R, G, B, LABEL, FORMAT) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (R), (G), (B), (LABEL), (FORMAT)))

#define LOG_UPDATE_TYPE_RGB_FORMAT(NAME, CODE, RGBVAL, FORMAT) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (RGBVAL), std::string(), (FORMAT)))

#define LOG_UPDATE_TYPE_LABELED_RGB_FORMAT(NAME, CODE, RGBVAL, LABEL, FORMAT) \
    (::cpp_logging::implicit_logger().create_type(#NAME, (CODE), (RGBVAL), (LABEL), (FORMAT)))

#endif // CPP_LOGGER_LOGGING_HPP
