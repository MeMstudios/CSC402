//
// Created by Michael on 11/20/2016.
//

#include "Logger.h"


void Logger::log(const string output, ofstream & file) {

    if (file.is_open()) {
        file << output;
    }

}

