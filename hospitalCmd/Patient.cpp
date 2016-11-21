//
// Created by Michael on 11/11/2016.
//

#include <iostream>
#include "Patient.h"
#include <sstream>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;

Patient::Patient( string & fn,  string  &mn,  string  &ln,  string  &sf, string &d, string &a, int &t, int &p)
        : firstname(fn), middlename(mn), lastname(ln), suffix(sf), doctor(d), ailments(a), treated(t), priority(p) {}
Patient::~Patient() {}

Patient::Patient(const Patient & rhs) {
    if (this != &rhs) {
        doctor = rhs.doctor;
        firstname = rhs.firstname;
        middlename = rhs.middlename;
        lastname = rhs.lastname;
        suffix = rhs.suffix;
        ailments = rhs.ailments;
        treated = rhs.treated;
        priority = rhs.priority;
    }

}
const Patient & Patient::operator=(const Patient & rhs){
    if (this != &rhs) {
        firstname = rhs.firstname;
        middlename = rhs.middlename;
        lastname = rhs.lastname;
        suffix = rhs.suffix;
        doctor = rhs.doctor;
        ailments = rhs.ailments;
        treated = rhs.treated;
        priority = rhs.priority;
    }
    return *this;
}
/**
 * Simulates treating a patient, putting the thread to sleep for 1-3 seconds.
 *
 */
void Patient::treat() {
    srand(time(NULL));
    if (treated == 0) {
        treated = 1;
        this_thread::sleep_for(chrono::milliseconds(rand() % 2000 + 1000));
        cout << "Patient treated." << endl;

    }
}
/**
 * Combines the patients first, middle, and last name to return the full name
 * @return
 */
string Patient::getName() const {
    return (firstname + " " + middlename + " " + lastname + " " + suffix);
}
string Patient::getLastName() const {
    return lastname;
}
string  Patient::getDoctor() const {
    return doctor;
}
int Patient::getPriority() {
    return priority;
}

int Patient::isTreated() {
    return treated;
}
//not used but could be useful
void Patient::setDoctor(string &d) {
    doctor = d;
}
/**
 * Uses stringstream to build a report of the patient and return it as a string.
 * @return
 */
string Patient::print() const {
    stringstream ss;

    ss << "Patient: " << getName() << endl;
    ss << "Doctor: " << doctor << endl;
    ss << "Ailments: " << ailments << endl;

    if (treated) {
        ss << "Patient has been treated." << endl;
    }
    else {
        ss << "Patient has not yet been treated." << endl;
    }
    ss << endl;
    return ss.str();
}
/*
ostream & Patient::operator<<( ostream & out, const Patient & rhs)   {

    return out;

}
*/