#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Logger {

public:

    void log(const string, ofstream &);

    static Logger* getLogger() {
        static Logger *instance;
        return instance;
    }

private:
    Logger() {}
    Logger(const Logger&);
    static Logger *logger;

};


#endif //LOGGER_H
