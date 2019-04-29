#include "logger.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstring>
#include <string>
#include "PolitoceanConstants.h"
#include "PolitoceanExceptions.hpp"
#include <experimental/filesystem>

namespace Politocean {

using namespace std::experimental;


const std::map<logger::levels, std::string> logger::levels_name = {
    { logger::ERROR,     Constants::Logger::Levels::ERROR },
    { logger::DEBUG,     Constants::Logger::Levels::DEBUG },
    { logger::INFO,      Constants::Logger::Levels::INFO  }
};

std::map<logger::levels, bool> logger::is_enabled = {
    { logger::ERROR,     true  },
    { logger::DEBUG,     false },
    { logger::INFO,      true  }
};

const int logger::MAX_FILE_SIZE = 1048576; // 1 MB

void logger::log(const levels level, const std::exception& exc){
    log(level, "An error occured due to an exception.", exc);
}

void logger::log(const levels level, const std::string& msg, const std::exception& exc){
    std::stringstream ss;
    ss << msg << "\tException: " << exc.what();
    auto str = ss.str();
    log(level, str.c_str());
}

void logger::log(const levels level, const std::string& msg){
    if(is_enabled.find(level)==is_enabled.end() || !is_enabled.at(level)) return;

    std::stringstream ss;
    time_t now = time(0);
    tm *l_time = localtime(&now);
    char* time_str = ctime(&now);
    time_str[strlen(time_str)-1]='\0';
    ss << time_str << " >\t" << msg;
    
    std::string level_name = levels_name.at(level);

    std::ofstream out;

    std::stringstream fullPath;
    std::stringstream folders;
    std::string fileName;

    folders << (1900 + l_time->tm_year) << "-" << l_time->tm_mon << "-" << l_time->tm_mday << "/" << level_name << "/";

    fullPath << Constants::Logger::LOGS_PATH << folders.str();

    if(!(filesystem::exists(fullPath.str()))){
        if(!(filesystem::create_directories(fullPath.str()))){
            throw loggerException("Couldn't create the directory.");
        }
    }
    else {
        int lastSize = -1;
        for(const auto& file : filesystem::directory_iterator(fullPath.str())){
            lastSize = filesystem::file_size(file.path());
            fileName = file.path().filename();
        }
        if(lastSize==-1 || lastSize > MAX_FILE_SIZE){
            std::stringstream newFileName;
            newFileName << now << "_" << level_name << ".log";

            fileName = newFileName.str();
        }
        
    }
    
    fullPath << fileName;

    out.open(fullPath.str(), std::ios::out | std::ios::app);

    out << ss.str() << std::endl;

    std::cout << "[" << level_name << "]\t" << ss.str() << std::endl;
}

void logger::enableLevel(const logger::levels level, const bool mode){
    is_enabled.at(level) = mode;
}

}