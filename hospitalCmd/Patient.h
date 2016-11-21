//
// Created by Michael on 11/11/2016.
//

#ifndef HOSPITALCMD_PATIENT_H
#define HOSPITALCMD_PATIENT_H

#include <cstdlib>
#include <string>
#include <time.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;
class Patient {
public:
    Patient( string &fn,  string  &mn,  string  &ln,  string  &sf, string &d, string &a, int &t, int &p);
    ~Patient();
    Patient(const Patient & rhs);
    const Patient & operator=(const Patient & rhs);
    void treat();
    string getName() const;
    string getLastName() const;
    string getDoctor() const;
    int getPriority();
    string getAilments();
    int isTreated();
    void setDoctor(string &d);
    string print() const;
    //ostream & operator<<( ostream & out, const Patient &) ;
private:
    string firstname, middlename, lastname, suffix, doctor, ailments;

    int treated, priority;



};


#endif //HOSPITALCMD_PATIENT_H
