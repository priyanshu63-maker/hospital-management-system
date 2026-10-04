
#include "hospital.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

using namespace std;

// Patient Monitoring
void patientMonitoring() {
    cout << "\nPatient monitoring started...\n";

    int fd = open("/dev/patient_monitor", O_RDONLY);

    if (fd < 0) {
        cout << "Patient monitor device not available.\n";
        return;
    }

    char buffer[256] = {0};

    read(fd, buffer, sizeof(buffer));

    cout << "\n--- Patient Monitor Data ---\n";
    cout << buffer << endl;

    close(fd);
}

// Add Patient
void addPatient() {
    string id, name, disease;
    int age;

    cout << "Enter Patient ID: ";
    cin >> id;

    cout << "Enter Name: ";
    cin >> name;

    cout << "Enter Age: ";
    cin >> age;

    cout << "Enter Disease: ";
    cin >> disease;

    ofstream file("patients.txt", ios::app);

    file << id << " "
         << name << " "
         << age << " "
         << disease << endl;

    file.close();

    cout << "\nPatient saved successfully!\n";

    writeLog("Patient added");
}

// View Patients
void viewPatients() {
    ifstream file("patients.txt");

    string id, name, disease;
    int age;

    if (!file) {
        cout << "\nNo patient records found.\n";
        return;
    }

    cout << "\n=============== PATIENT LIST ===============\n";

    bool found = false;

    while (file >> id >> name >> age >> disease) {
        found = true;

        cout << "---------------------------------------------\n";
        cout << "Patient ID : " << id << endl;
        cout << "Name       : " << name << endl;
        cout << "Age        : " << age << endl;
        cout << "Disease    : " << disease << endl;
    }

    if (!found) {
        cout << "No patient records found.\n";
    }

    cout << "=============================================\n";

    file.close();
}

int main() {

    cout << "=====================================\n";
    cout << "     HOSPITAL MANAGEMENT SYSTEM\n";
    cout << "=====================================\n";

    // Create child process
    pid_t pid = fork();

    if (pid == 0) {
        cout << "\nChild process: Hospital system started.\n";
        return 0;
    }
    else {
        wait(NULL);
        cout << "Parent process: Child process completed.\n";
    }

    int choice;

    do {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. Add Patient\n";
        cout << "2. View Patients\n";
        cout << "3. Add Doctor\n";
        cout << "4. View Doctor\n";
        cout << "5. Book Appointment\n";
        cout << "6. View Appointment\n";
        cout << "7. Add Medical Record\n";
        cout << "8. View Medical Record\n";
        cout << "9. Patient Monitoring\n";
        cout << "10. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addPatient();
            break;

        case 2:
            viewPatients();
            break;

        case 3: {
            string id, name, specialization;

            cout << "Enter Doctor ID: ";
            cin >> id;

            cout << "Enter Name: ";
            cin >> name;

            cout << "Enter Specialization: ";
            cin >> specialization;

            Doctor d(id, name, specialization);
            d.display();

            writeLog("Doctor added");

            break;
        }

        case 4: {
            Doctor d("D101", "Dr_Sharma", "Cardiology");
            d.display();

            break;
        }

        case 5: {
            string patientId, doctorId, date;

            cout << "Enter Patient ID: ";
            cin >> patientId;

            cout << "Enter Doctor ID: ";
            cin >> doctorId;

            cout << "Enter Date: ";
            cin >> date;

            Appointment a(patientId, doctorId, date);
            a.display();

            writeLog("Appointment booked");

            break;
        }

        case 6: {
            Appointment a("P101", "D101", "05-10-2026");
            a.display();

            break;
        }

        case 7: {
            string patientId, diagnosis, medicine;

            cout << "Enter Patient ID: ";
            cin >> patientId;

            cout << "Enter Diagnosis: ";
            cin >> diagnosis;

            cout << "Enter Medicine: ";
            cin >> medicine;

            MedicalRecord m(patientId, diagnosis, medicine);
            m.display();

            writeLog("Medical record added");

            break;
        }

        case 8: {
            MedicalRecord m("P101", "Fever", "Paracetamol");
            m.display();

            break;
        }

        case 9: {
            thread monitorThread(patientMonitoring);
            monitorThread.join();

            break;
        }

        case 10:
            cout << "\nExiting Hospital Management System...\n";
            break;

        default:
            cout << "\nInvalid choice!\n";
        }

    } while (choice != 10);

    return 0;
}
