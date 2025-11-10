// Header files includes //
#include "../include/logging.hpp"
#include "../include/utils.hpp"

// C++ standard library includes //
#include <utility>
#include <iostream>

namespace cpp_logging {

    Logger::Logger() {
        enable_virtual_terminal_processing_once();
    }

    void Logger::create_type(const std::string& type_name, int code, RGB color, std::string label, std::string format) {
        Type type;
        type.code  = code;
        type.color = color;
        type.label = label.empty() ? type_name : std::move(label);
        if (!format.empty()) {
            type.format = std::move(format);
        }
        _types[type_name] = std::move(type);
    }

    void Logger::create_type(const std::string& type_name, int code, int r, int g, int b, std::string label, std::string format) {
        create_type(
            type_name,
            code, 
            RGB{ 
                static_cast<std::uint8_t>(r), 
                static_cast<std::uint8_t>(g),
                static_cast<std::uint8_t>(b)
            },
            std::move(label),
            std::move(format)
        );
    }

    std::string Logger::render_format(const Type& type, const std::string& message, const std::string& fmt) {
        std::string out;
        out.reserve(fmt.size() + message.size() + type.label.size() + 16);

        const std::string label_colored = std::string(ansi_fg_rgb(type.color)) + type.label + ansi_reset();

        std::size_t pos = 0;
        while (pos < fmt.size()) {
            std::size_t brace_pos = fmt.find('{', pos);
            if (brace_pos == std::string::npos) {
                out.append(fmt, pos, fmt.size() - pos);
                break;
            }
            out.append(fmt, pos, brace_pos - pos);
            std::size_t end_brace = fmt.find('}', brace_pos + 1);
            if (end_brace == std::string::npos) {
                out.append(fmt, brace_pos, fmt.size() - brace_pos);
                break;
            }
            std::string key = fmt.substr(brace_pos + 1, end_brace - brace_pos - 1);
            if (key == "label") {
                out += label_colored;
            } else if (key == "context") {
                out += message;
            } else {
                out.append(fmt, brace_pos, end_brace - brace_pos + 1);
            }
            pos = end_brace + 1;
        }
        return out;
    }

    void Logger::set_format(const std::string& type_name, const std::string& format) {
        auto it = _types.find(type_name);
        if (it == _types.end())
            return;
        if (!format.empty())
            it->second.format = format;
    }

    void Logger::log_by_type_message(const std::string& type_name, const std::string& message) {
        auto it = _types.find(type_name);
        if (it == _types.end())
            return;
        const Type& type = it->second;
    #if defined(LOG_LEVEL)
        if (type.code > LOG_LEVEL)
            return;
    #endif
        const std::string& fmt = type.format;
        std::string formatted = render_format(type, message, fmt);
        std::ostream& os = std::cerr;
        os << formatted << '\n';
        os.flush();
    }

    Logger& implicit_logger() {
        static Logger logger{};
        return logger;
    }

}