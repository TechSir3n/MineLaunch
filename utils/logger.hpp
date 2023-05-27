#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <mutex>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

enum class LogLevel {
   Debug,

   Info,

   Warning,

   Error,

   Critical
};

class Logger {
public:
    Logger() = default;

    ~Logger() = default;

    Logger(const Logger &) = delete;

    Logger & operator=(const Logger &) = delete;

public:
    static Logger & getInstance() {
        static Logger instance;
        return instance;
    }

    template<typename T>
    void print(std::ostream & os,T &&arg) {
        os << arg;
    }

    template<typename T,typename...Args>
    void print(std::ostream &os, T &&arg,Args&&...args) {
        os << arg;
        print(os,std::forward<Args>(args)...);
    }

    template <typename... Args>
    void log(LogLevel level,Args... args) {
        std::ostringstream os;
        std::unique_lock<std::mutex> lock(m_mutex);
        print(os,std::forward<Args>(args)...);
        write(level,os.str());
    }

private:
    void write(LogLevel level,const std::string_view &message)  {
        fs::path file =  fs::path{"/home/ruslan/Documents/MineLaunch/utils/logs_files/"} / getFileName();
        std::ofstream ofs;

        ofs.open(file, std::fstream::in | std::fstream::out | std::fstream::app);
        if(!ofs.is_open()) {
            throw std::runtime_error("Couldn't open file");
        }

        std::string str_level;
        switch(level) {
        case LogLevel::Debug:
        str_level = "Debug";
            break;

        case LogLevel::Info:
        str_level = "Info";
            break;
        case LogLevel::Warning:
        str_level = "Warning";
            break;

        case LogLevel::Error:
        str_level = "Error";
            break;

        case LogLevel::Critical:
        str_level = "Critical";
            break;

        default:
            break;
        }

        ofs << " [LEVEL] -> " << str_level << " : " << message;
        ofs.close();
    }

    std::string getFileName() noexcept {
        std::string fileName;
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::ostringstream stream;
        stream << std::put_time(std::localtime(&time), "%Y-%m-%d_%H-%M-%S") << ".log";
        fileName = stream.str();
        return fileName;
    }

private:
    std::mutex m_mutex;
};

#endif
