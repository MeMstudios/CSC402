/***
 * Michael E. Murphy
 * CSC402 - Project 3
 * November, 2016
 * Prof: Michael Clark
 *
 * This is a simulated hospital triage system.
 * You login as a doctor, nurse, hospital, or admin.
 * As an admin you can load patients from a file called "patients.txt"
 *  You must put this file in the debug folder with the application.
 * As an admin you can change the name of the log file.
 *  When you exit, the system will write a report to the log file specified, or "log.txt" by default.
 * As a doctor you can treat the highest priority patient.
 *  You can search for patients by last name and print out a report on them.
 *  You can see a report of all treated patients and view the next patient to be treated.
 * As a nurse you can add a new patient.
 * As a hospital you can treat all the patients in triage.
 *  You can see all the patients needing treatment.
 *  You can list all the patients by doctor.
 *
 * Typing 'exit' will log you out, allowing you to login as something else.
 *  exit again to write the log file and quit the program.
 *
 */

#include "Patient.h"
#include "Logger.h"



using namespace std;
typedef multimap<int, Patient, less<int>> Multi;
//typedef priority_queue<int, Patient, greater<int>> Queue;
/**
 * Reads in a list of patients from a file with formatted fields.
 * @param filename - defaults to "patients.txt"
 * @return
 */
vector<Patient> patientsFromFile(string filename = "patients.txt") {
    //vector of patients
    vector<Patient> patients;
    //strings and ints to hold the parameters of a patient
    string firstname, middlename, lastname, suffix, doctor, ails, thisline;
    int treated, priority;
    //line buffer
    char line[1000];
    //create the filestream
    ifstream file(filename, ios::in);
    //check if the file exists
    if (!file) {
        cerr << "file not found. " << endl;
        exit(0);
    }
    else {
        //read through the file separating lines by the colon.
        while (file.getline(line, 256, ':')) {
            //string for comparisons
            thisline = line;
            //find the newline char to delete line breaks.
            if (thisline.at(0) == '\n') {

                thisline.erase(thisline.begin());
            }
            //if the field is found
            if (thisline == "firstName") {

                file.getline(line, 256);
                //set this line to the field
                firstname = line;

            } else if (thisline == "middleName") {
                file.getline(line, 256);
                middlename = line;
            } else if (thisline == "lastName") {
                file.getline(line, 256);
                lastname = line;
            } else if (thisline == "suffix") {
                file.getline(line, 256);
                suffix = line;
            } else if (thisline == "ailment") {
                file.getline(line, 256);
                thisline = line;
                //we can add multiple ailments to one string.
                ails += thisline + ", ";
            } else if (thisline == "doctor") {
                file.getline(line, 256);
                doctor = line;
            } else if (thisline == "treated") {
                file.getline(line, 256);
                //atoi is a char to int method
                treated = atoi(line);
            } else if (thisline == "priority") {
                file.getline(line, 256);
                priority = atoi(line);
                //take off the end comma from the ailments
                ails.erase(ails.length()-2, ails.length()-1);
                //create a patient with all the information
                Patient *patient = new Patient(firstname, middlename, lastname, suffix, doctor, ails, treated, priority);
                //clear the ails string for the next one.
                ails.clear();
                //cout << "New Patient: " << patient->getName() << endl;
                patients.push_back(*patient);
                //cout << patients.at(0).getName() << endl;
            } else cerr << "Input file format problem!" << endl;
        }

    }

    //EOF
    return patients;

}
/**
 * Helper function for outputting my lists of patients.
 * Used to stream to the cout and stringsteram for logging.
 * @param patients - multimap of patients and their priorities
 * @param out - ostream
 */
void listPatients (Multi & patients, ostream & out) {

    for(Multi::const_iterator it = patients.begin(); it != patients.end(); ++it) {
        out << it->second.print();
    }
}
int main() {
    const int SIZE = 128;
    //a buffer for command inputs
    char buffer[SIZE];
    //strings for the input and my log file's name
    string input, filename="log.txt";
    //strings and ints to hold input from a nurse to create new patients.
    string firstname, middlename, lastname, suffix, doctor, ails;
    int treated, priority;
    //vecotr of patients from file
    vector<Patient> patients;
    //multimaps that holds patients and sort them by order of priority
    Multi triagePatients;
    Multi treatedPatients;
    //declare a log file
    ofstream logfile;
    //stringstream holds my data to be logged
    stringstream ss;
    //get the logger instance
    Logger *log = Logger::getLogger();
    //promt for input
    cout << "Type: doctor, nurse, hospital, or admin to login. " << endl;
    cin >> buffer;
    //buffer to input for comparison
    input = buffer;
    while (input != "exit") {
        //doctors' commands
        if (input == "doctor") {
            ss << "Doctor login. " << endl;
            while (input != "exit") {
                cout
                        << "Hello Doctor, please type 'treat' to treat the next patient in triage. \n"
                                "Type 'help' for more options. \n"
                                "Type 'exit' to quit."
                        << endl;

                cin >> buffer;
                input = buffer;
                if (input == "treat") {
                    if (triagePatients.size() > 0) {
                        //show the patient's name before treating
                        cout << "Treating highest priority patient: " << triagePatients.begin()->second.getName()
                             << endl;
                        ss << "Treating highest priority patient: " << triagePatients.begin()->second.getName()
                              << endl;
                        //treat the first patient in the triage container
                        triagePatients.begin()->second.treat();
                        //this_thread::sleep_for(chrono::milliseconds(3000)); //can't get it to recognize this_thread but this is where it would sleep for 3 seconds
                        //put the treated patient into the treatedPatient map
                        treatedPatients.insert(*triagePatients.begin());
                        //delete from the triagePatient map
                        triagePatients.erase(triagePatients.begin());
                    } else {
                        //no patients in the queue
                        cout << "No more Patients!" << endl;
                    }

                } else if (input == "report") {
                    //report the treated patients to the console and the log.
                    cout << "Treated Patients: " << endl;
                    listPatients(treatedPatients, cout);
                    ss << "Listing treated patients. " << endl;
                    listPatients(treatedPatients, ss);
                } else if (input == "find") {
                    //prompt for the last name
                    cout << "Search for a patient by last name. " << endl;

                    cin >> buffer;
                    input = buffer;
                    ss << "Searching for patient by last name: " << buffer << endl;
                    //search through the two maps for the patients with the last name and send it to the console and the log.
                    for (Multi::const_iterator it = triagePatients.begin(); it != triagePatients.end(); ++it) {
                        if (it->second.getLastName() == input) {
                            cout << it->second.print();
                            ss << "Found: " << it->second.getName() << endl;
                        }
                    }
                    for (Multi::const_iterator it = treatedPatients.begin(); it != treatedPatients.end(); ++it) {
                        if (it->second.getLastName() == input) {
                            cout << it->second.print();
                            ss << "Found: " << it->second.getName() << endl;
                        }
                    }

                } else if (input == "next") {
                    //show the next patient in triage to the console and the log
                    cout << "Next patient in triage: " << endl;
                    cout << triagePatients.begin()->second.print();
                    ss << "Showing next patient in triage: " << endl;
                    ss << triagePatients.begin()->second.print();
                } else if (input != "exit") { //could be 'help' or any other input
                    //show the user the available commands.
                    cout << "Type 'report' to see a list of treated patients.  \n"
                            "Type 'find' to search for a patient. \n"
                            "Type 'next' to see the next patient to be treated."
                         << endl;
                }


            }

        }
            //nurses' commands
        else if (input == "nurse") {
            ss << "Nurse login." << endl;
            while (input != "exit") {
                cout << "Hello Nurse, please type 'new' to create a new patient or 'exit' to quit." << endl;
                cin >> buffer;
                input = buffer;
                if (input == "new") {
                    //retrieve all the the patient's information
                    cout << "Enter patient's first name:" << endl;
                    cin >> firstname;
                    cout << "Enter patient's middle name: " << endl;
                    cin >> middlename;
                    cout << "Enter patient's last name: " << endl;
                    cin >> lastname;
                    cout << "Enter a suffix, if none; type 'none': " << endl;
                    cin >> buffer;
                    input = buffer;

                    if (input != "none") {
                        suffix = input;
                    }

                    cout << "Enter an ailment and press enter, type 'done' when done: " << endl;
                    cin >> buffer;
                    input = buffer;
                    while (input != "done") {
                        ails += input + " ";
                        cin >> buffer;
                        input = buffer;
                    }

                    cout << "Enter an assigned doctor: " << endl;
                    cin >> doctor;
                    cout << "Enter 0 if the patient needs treatment.  Enter 1 if the patient is already treated. " << endl;
                    cin >> treated;
                    cout << "Enter a priority with 1 being the highest priority. " << endl;
                    cin >> priority;
                    //create a new patient
                    Patient *patient = new Patient(firstname, middlename, lastname, suffix, doctor, ails, treated, priority);
                    //clear the ails string for next time
                    ails.clear();
                    //check if the patient is treated or not and add the the correct map
                    if (!treated) {
                        triagePatients.insert(Multi::value_type(patient->getPriority(), *patient));
                        cout << "New triage patient: " << patient->getName() << endl;
                        ss << "Entered new triage patient: " << patient->getName() << endl;
                    } else {
                        treatedPatients.insert(Multi::value_type(patient->getPriority(), *patient));
                        cout << "New treated patient: " << patient->getName() << endl;
                        ss << "Entered new treated patient: " << patient->getName() << endl;
                    }

                }
            }
        }
            //hospital commands
        else if(input ==  "hospital") {
            ss << "Hospital login." << endl;
            while (input != "exit") {
                cout << "Logged in as the Hospital.  Please type 'report' to see a report of all the patients in triage. \n"
                        "Type 'help' for more options. \n"
                        "Type 'exit' to quit. "
                     << endl;
                cin >> buffer;
                input = buffer;
                //check for the command
                if (input == "report") {
                    //list the patients in triage to the console and the log
                    cout << "Patients in triage: " << endl;
                    listPatients(triagePatients, cout);
                    ss << "Reporting patients in triage: " << endl;
                    listPatients(triagePatients, ss);
                }
                else if (input == "treat") {

                    cout << "Treating all patienets. " << endl;
                    //treat all the patients in triage in order and put them in the treated container
                    while (triagePatients.size() > 0) {
                        triagePatients.begin()->second.treat();

                        treatedPatients.insert(*triagePatients.begin());
                        triagePatients.erase(triagePatients.begin());
                    }
                }
                else if (input == "doctor") {
                    //get the doctor's name
                    cout << "Type the doctor's name to show their patients: " << endl;

                    cin >> buffer;
                    input = buffer;
                    ss << "Searching for patients by doctor: " << buffer << endl;
                    //search the two containers for the doctor and log them to the console and file
                    for (Multi::const_iterator it = triagePatients.begin(); it != triagePatients.end(); ++it) {
                        if (it->second.getDoctor() == input) {
                            cout << it->second.print() << endl;
                            ss << "Found: " << it->second.print() << endl;
                        }
                    }
                    for (Multi::const_iterator it = treatedPatients.begin(); it != treatedPatients.end(); ++it) {
                        if (it->second.getDoctor() == input) {
                            cout << it->second.print() << endl;
                            ss << "Found: " << it->second.print() << endl;
                        }
                    }
                }
                else if (input != "exit") {
                    //if the input is not one of the above or 'exit', show the user the additional commands. Needing help is implied
                    cout << "Type 'report' to show all patients needing treatment. \n"
                            "Type 'treat' to treat all patients in triage. \n"
                            "Type 'doctor' to find a patient by doctor's last name."
                         << endl;
                }
            }

        }
        else if (input == "admin") {
            //administrator will perform one task and go back to the main menu.
            cout << "Logged in as administrator.  \nType 'add' to bulk add patients from a file saved as: 'patients.txt' \nType 'log' to change the system log file. (default: 'log.txt')" << endl;
            cin >> buffer;
            input = buffer;
            if (input ==  "add") {
                //get the vector from the patientsFromFile function.
                patients = patientsFromFile();
                //iterate through the patients and put them in the proper container.  Logging at the same time.
                for(vector<Patient>::const_iterator it = patients.begin(); it != patients.end(); ++it) {
                    Patient patient = *it;
                    cout << "New Patient: " << patient.getName() << endl;
                    ss << "New Patient: " << patient.getName() << endl;
                    if (patient.isTreated()) {
                        treatedPatients.insert(Multi::value_type(patient.getPriority(), patient));

                    }
                    else {
                        triagePatients.insert(Multi::value_type(patient.getPriority(), patient));

                    }
                }
                //log progress
                cout << "Patients loaded from file. " << endl;
                ss << "Patients loaded from file. " << endl;

            }
            else if (input == "log") {
                cout << "enter a new file name for the log file: " << endl;
                cin >> buffer;
                ss << "Changing log file to: " << buffer << endl;
                filename = buffer;
                //create a new logfile with the specified name.

            }
        }
        //get the next login or exit
        cout << "Type: doctor, nurse, hospital, or admin to login. 'exit' to exit " << endl;
        cin >> buffer;
        input = buffer;
    }
    //send the string log to the file
    logfile = ofstream(filename, fstream::out);
    log->log(ss.str(), logfile);


    return 0;
}
