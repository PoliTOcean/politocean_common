#include "logger.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstring>
#include "PolitoceanConstants.h"
#include "PolitoceanExceptions.hpp"
#include <experimental/filesystem>

namespace Politocean {

using namespace std::experimental;


const std::map<logger::levels, std::string> logger::levels_name = {
    {logger::ERROR,     Constants::Logger::Levels::ERROR},
    {logger::DEBUG,     Constants::Logger::Levels::DEBUG},
    {logger::INFO,      Constants::Logger::Levels::INFO }
};

const int logger::MAX_FILE_SIZE = 1048576; // 1 MB

void logger::log(const levels level, const std::exception& exc){
    log(level, "Error occured due to exception: ", exc);
}

void logger::log(const levels level, const char* msg, const std::exception& exc){
    std::stringstream ss;
    ss << msg << " " << exc.what();
    auto str = ss.str();
    log(level, str.c_str());
}

void logger::log(const levels level, const char* msg){
    std::stringstream ss;
    time_t now = time(0);
    tm *l_time = localtime(&now);
    char* time_str = ctime(&now);
    time_str[strlen(time_str)-1]='\0';
    ss << time_str << " > " << msg;
    
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

    std::cout << "[" << level_name << "] " << ss.str() << std::endl;
}

}