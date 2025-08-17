#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

string studentName;  


vector<vector<string>> readDatabase() {
    vector<vector<string>> data;
    ifstream file("database.csv");
    string line;

    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }
    return data;
}


void writeDatabase(const vector<vector<string>>& data) {
    ofstream file("database.csv");
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); i++) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
}
void updateField(const string& name, const string& field, const string& value) {
    vector<vector<string>> data = readDatabase();

    if (data.empty()) return;

    // First row = header
    int colIndex = -1;
    for (size_t i = 0; i < data[0].size(); i++) {
        if (data[0][i] == field) {
            colIndex = i;
            break;
        }
    }

    if (colIndex == -1) return;

    for (size_t i = 1; i < data.size(); i++) {
        if (data[i][0] == name) {
            data[i][colIndex] = value;
            break;
        }
    }

    writeDatabase(data);
}


bool studentExists(const string& name) {
    ifstream file("database.csv");
    string line;

    getline(file, line); // skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string storedName;
        getline(ss, storedName, ','); // first column is name
        if (storedName == name) {
            return true; // student already exists
        }
    }
    return false;
}


void addStudentToDB(const string& name) {
    ofstream file("database.csv", ios::app); // append mode
    file << name << ",Verified,PendingVisa,PendingFee,NoAccommodation,NoTutor,NoExtraCredits\n";
    file.close();
}


void Initialization() {
    bool verified = false;

    do {
        cout << "\n--- Initialization ---\n";
        cout << "Enter student name: ";
        cin >> studentName;

        if (studentExists(studentName)) {
            cout << "Student with name \"" << studentName << "\" already exists in database!\n";
            continue; // ask again
        }

        char verify;
        cout << "Admin verifies form? (y/n): ";
        cin >> verify;

        if (verify == 'y' || verify == 'Y') {
            verified = true;
            cout << "Form verified. Sending to department...\n";
            addStudentToDB(studentName);
            cout << "Student information stored in database.\n";
        } else {
            cout << "Form not verified. Please complete again.\n";
        }
    } while (!verified);

    cout << "Initialization completed.\n";
}


void Visa() {
    char needVisa;
    cout << "\nDo you need a visa? (y/n): ";
    cin >> needVisa;

    if (needVisa == 'n' || needVisa == 'N') {
        cout << "No visa needed.\n";
        updateField(studentName, "VisaStatus", "NotNeeded");
        return;
    }

    bool applied = false;
    while (!applied) {
        cout << "Informing student for visa application...\n";
        char check;
        cout << "Have you applied for visa? (y/n): ";
        cin >> check;
        if (check == 'y' || check == 'Y') {
            applied = true;
            cout << "Visa application confirmed.\n";
            updateField(studentName, "VisaStatus", "Applied");
        }
    }
}


void TuitionFee() {
    bool paid = false;
    cout << "\n--- Tuition Fee Payment ---\n";
    while (!paid) {
        char status;
        cout << "Have you paid the tuition fee? (y/n): ";
        cin >> status;
        if (status == 'y' || status == 'Y') {
            paid = true;
            cout << "Tuition fee paid successfully.\n";
            updateField(studentName, "FeePaid", "Yes");
        } else {
            cout << "Waiting until fee is paid...\n";
        }
    }
}

-
void Accommodation() {
    char needAcc;
    cout << "\nDo you need accommodation? (y/n): ";
    cin >> needAcc;

    if (needAcc == 'y' || needAcc == 'Y') {
        cout << "Accommodation assigned successfully.\n";
        updateField(studentName, "Accommodation", "Assigned");
    } else {
        cout << "No accommodation required.\n";
        updateField(studentName, "Accommodation", "NotNeeded");
    }
}


void AssignTutor() {
    cout << "\n--- Assigning Personal Tutor ---\n";
    cout << "Personal Tutor Assigned.\n";
    updateField(studentName, "TutorAssigned", "Yes");

    cout << "Meeting with Personal Tutor completed.\n";

    char extra;
    cout << "Do you have extra credits? (y/n): ";
    cin >> extra;

    if (extra == 'y' || extra == 'Y') {
        cout << "Choose additional courses successfully.\n";
        updateField(studentName, "ExtraCredits", "Yes");
    } else {
        cout << "No additional courses chosen.\n";
        updateField(studentName, "ExtraCredits", "No");
    }
}


void Termination() {
    cout << "\n--- Termination ---\n";
    cout << "Student Fully Registered!\n";
}


int main() {
    cout << " Student Registration System \n";

    // Ensure database file exists with header
    ifstream infile("database.csv");
    if (!infile.good()) {
        ofstream file("database.csv");
        file << "Name,Verified,VisaStatus,FeePaid,Accommodation,TutorAssigned,ExtraCredits\n";
        file.close();
    }

    Initialization();     
    Visa();               
    TuitionFee();      
    Accommodation();     
    AssignTutor();        
    Termination();        

    cout << "\n Registration Process Completed \n";
    return 0;
}
