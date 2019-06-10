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
#include <cstdlib>

#define UNDEFINED "undefined"
using namespace Politocean;
using namespace std::experimental;

std::string logger::rootTag = UNDEFINED;
int logger::activation_level = logger::CONFIG;

const std::map<logger::levels, std::string> logger::levels_name = {
    { logger::ERROR,     Constants::Logger::Levels::ERROR   },
    { logger::WARNING,   Constants::Logger::Levels::WARNING },
    { logger::CONFIG,    Constants::Logger::Levels::CONFIG  },
    { logger::INFO,      Constants::Logger::Levels::INFO    },
    { logger::DEBUG,     Constants::Logger::Levels::DEBUG   }
};

std::map<std::string, logger*> logger::instances;

const int logger::MAX_FILE_SIZE = 1048576; // 1 MB

logger::logger(const std::string& tag) : tag(tag)
{}

logger& logger::getInstance(const std::string& tag) {
    if (tag==""){
        static logger defaultInstance(logger::rootTag);
        return defaultInstance;
    }

    if (instances.find(tag) != instances.end())
	{
		if(instances.at(tag)==nullptr)
			instances.erase(tag);
		else
			return *instances.at(tag);
	}

	instances.insert(std::pair<std::string, logger*>(tag, new logger(tag)));
	return *instances.at(tag);
}

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
    std::string level_name = levels_name.at(level);

    std::stringstream ss;
    ss << "[" << level_name << "] ";
    time_t now = time(0);
    tm *l_time = localtime(&now);
    char* time_str = ctime(&now);
    time_str[strlen(time_str)-1]='\0';
    ss << time_str << " >\t" << ( tag=="" ? rootTag : tag ) << ": " << msg;
    
    std::ofstream out, out_tag;

    std::stringstream fullPath;
    std::stringstream folders;
    std::string fileName;

    folders << rootTag << "/";
    folders << (1900 + l_time->tm_year) << "-" << (l_time->tm_mon+1) << "-" << l_time->tm_mday << "/";

    fullPath << getenv("HOME") << "/" << Constants::Logger::LOGS_PATH << folders.str();

    if(!(filesystem::exists(fullPath.str()))){
        if(!(filesystem::create_directories(fullPath.str()))){
            throw loggerException("Couldn't create the directory.");
        }
    }
    else {
        int lastSize = -1;
        for(const auto& file : filesystem::directory_iterator(fullPath.str())){
            if (filesystem::is_directory(file)) continue;
            lastSize = filesystem::file_size(file.path());
            fileName = file.path().filename();
        }
        if(lastSize==-1 || lastSize > MAX_FILE_SIZE){
            std::stringstream newFileName;
            newFileName << now << ".log";

            fileName = newFileName.str();
        }
        
    }

    out.open(fullPath.str() + fileName, std::ios::out | std::ios::app);
    out << ss.str() << std::endl;
    out.close();

    if (tag != "") {
        fullPath << tag << "/";

        if(!(filesystem::exists(fullPath.str()))){
            if(!(filesystem::create_directories(fullPath.str()))){
                throw loggerException("Couldn't create the directory.");
            }
        }
        else {
            int lastSize = -1;
            for(const auto& file : filesystem::directory_iterator(fullPath.str())){
                if (filesystem::is_directory(file)) continue;
                lastSize = filesystem::file_size(file.path());
                fileName = file.path().filename();
            }
            if(lastSize==-1 || lastSize > MAX_FILE_SIZE){
                std::stringstream newFileName;
                newFileName << now << ".log";

                fileName = newFileName.str();
            }
            
        }

        out_tag.open(fullPath.str() + fileName, std::ios::out | std::ios::app);
        out_tag << ss.str() << std::endl;
        out_tag.close();
    }


    // if below activation_level, don't print on screen
    if(activation_level < level) return;

    if(level <= levels::ERROR)
    {
        std::cerr << ss.str() << std::endl;
    }
    else
    {
        std::cout << ss.str() << std::endl;  
    }
    
}

void logger::setRootTag(const std::string& rootTag) {
    logger::rootTag = rootTag;
}

void logger::enableLevel(const logger::levels level){
    logger::activation_level = level;
}
