#include "hospital.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// Patient constructor
Patient::Patient(string i, string n, int a, string d) {
    id = i;
    name = n;
    age = a;
    disease = d;
}

// Display patient
void Patient::display() {
    cout << "\nPatient ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Disease: " << disease << endl;
}

// Doctor constructor
Doctor::Doctor(string i, string n, string s) {
    id = i;
    name = n;
    specialization = s;
}

// Display doctor
void Doctor::display() {
    cout << "\nDoctor ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Specialization: " << specialization << endl;
}

// Appointment constructor
Appointment::Appointment(string p, string d, string dt) {
    patientId = p;
    doctorId = d;
    date = dt;
}

// Display appointment
void Appointment::display() {
    cout << "\nPatient ID: " << patientId << endl;
    cout << "Doctor ID: " << doctorId << endl;
    cout << "Date: " << date << endl;
}

// Medical record constructor
MedicalRecord::MedicalRecord(string p, string d, string m) {
    patientId = p;
    diagnosis = d;
    medicine = m;
}

// Display medical record
void MedicalRecord::display() {
    cout << "\nPatient ID: " << patientId << endl;
    cout << "Diagnosis: " << diagnosis << endl;
    cout << "Medicine: " << medicine << endl;
}

// Write activity to log file
void writeLog(string message) {
    ofstream file("hospital.log", ios::app);

    time_t now = time(0);

    file << ctime(&now) << ": " << message << endl;

    file.close();
}