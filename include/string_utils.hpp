#ifndef FILE_UTILS
#define FILE_UTILS

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <source_location>
#include <vector>

namespace string_helpers {
    /* 
     * Reads a file from a given file and stores it as vector of strings (Linearly)
     */  
    std::vector<std::string> get_inputs_from_file (
            std::string_view filep, char delim='\n',
            const std::source_location location =
            std::source_location::current()) {
        
        std::vector<std::string> result;
        try{
            std::ifstream fs;
            fs.open(std::string(filep));
            if (!fs) {
                throw std::runtime_error("File opening error!: Check if Path is correct"); 
            }

            for (std::string res; std::getline(fs,res,delim)) {
                result.push_back(res);
            }
        }
        catch (std::exception & e) {
            std::cerr<< location.file_name() << '('
              << location.line() << ':'
              << location.column() << ") `"
              << location.function_name() << "`: "<<e.what()<<std::endl;
        }
        return result;
    }
};

#endif /* FILE_UTILS */