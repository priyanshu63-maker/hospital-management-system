#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
using namespace std;

// Patient class
class Patient {
public:
    string id;
    string name;
    int age;
    string disease;

    Patient(string i, string n, int a, string d);

    void display();
};

// Doctor class
class Doctor {
public:
    string id;
    string name;
    string specialization;

    Doctor(string i, string n, string s);

    void display();
};

// Appointment class
class Appointment {
public:
    string patientId;
    string doctorId;
    string date;

    Appointment(string p, string d, string dt);

    void display();
};

// Medical Record class
class MedicalRecord {
public:
    string patientId;
    string diagnosis;
    string medicine;

    MedicalRecord(string p, string d, string m);

    void display();
};

// Log function
void writeLog(string message);

#endif