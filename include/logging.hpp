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
            void log_by_type(const std::string& type_name, const char* file, const char* function, int line, Args&&... args);
        
        private:
            std::unordered_map<std::string, Type> _types;
            static std::string trim(const std::string& s);
            static std::string render_format(const Type& type, const std::string& message, const std::string& fmt, const char* file, const char* function, int line);
            void log_by_type_message(const std::string& type_name, const std::string& message, const char* file, const char* function, int line);
    };
    
    Logger& implicit_logger();
    
    template <typename... Args>
    void Logger::log_by_type(const std::string& type_name, const char* file, const char* function, int line, Args&&... args) {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        log_by_type_message(type_name, oss.str(), file, function, line);
    }

}

#if defined(LOG_LEVEL)
  #define LOG_SHOULD_LOG(CODE) ((CODE) <= (LOG_LEVEL))
#else
  #define LOG_SHOULD_LOG(CODE) (true)
#endif

#endif // CPP_LOGGER_LOGGING_HPP