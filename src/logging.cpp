
// Header files includes //
#include "../include/logging.hpp"
#include "../include/utils.hpp"

namespace cpp_logging {

    Logger::Logger() {
        enable_virtual_terminal_processing_once();
    }
    
    void Logger::create_type(const std::string& type_name, int code, RGB color, std::string label) {
        Type t;
        t.code  = code;
        t.color = color;
        t.label = label.empty() ? type_name : std::move(label);
        _types[type_name] = std::move(t);
    }
    
    void Logger::create_type(const std::string& type_name, int code, int r, int g, int b, std::string label) {
        create_type(
            type_name,
            code,
            RGB{
                static_cast<std::uint8_t>(r),
                static_cast<std::uint8_t>(g),
                static_cast<std::uint8_t>(b)
            },
            std::move(label)
        );
    }
    
    Logger& implicit_logger() {
        static Logger logger{};
        return logger;
    }

}
