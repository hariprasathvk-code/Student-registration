#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

string studentName;

// Read database
vector<vector<string>> readDB() {
    vector<vector<string>> data;
    ifstream file("database.csv");
    string line;
    while (getline(file, line)) {
        vector<string> row;
        string cell;
        stringstream ss(line);
        while (getline(ss, cell, ',')) row.push_back(cell);
        if (!row.empty()) data.push_back(row);
    }
    return data;
}

// Write database
void writeDB(const vector<vector<string>>& data) {
    ofstream file("database.csv");
    for (auto& row : data) {
        for (size_t i = 0; i < row.size(); i++) {
            file << row[i];
            if (i + 1 < row.size()) file << ",";
        }
        file << "\n";
    }
}

// Update field
void updateField(const string& name, int col, const string& value) {
    auto db = readDB();
    for (auto& row : db) {
        if (row[0] == name) {
            if (row.size() < 7) row.resize(7, "");
            row[col] = value;
            writeDB(db);
            return;
        }
    }
}

// Ensure file header
void ensureHeaderFile() {
    ifstream in("database.csv");
    if (!in.good() || in.peek() == ifstream::traits_type::eof()) {
        ofstream f("database.csv");
        f << "Name,Verified,VisaStatus,FeePaid,Accommodation,TutorAssigned,ExtraCredits\n";
    }
}

void Initialization() {
    bool verified = false;
    do {
        cout << "\nEnter student name: ";
        cin >> studentName;

        auto db = readDB();
        bool exists = false;
        for (auto& row : db) if (row[0] == studentName) exists = true;

        if (exists) {
            cout << "Student already exists. Updating record...\n";
            verified = true;
            break;
        }

        char v;
        cout << "Admin verifies form? (y/n): ";
        cin >> v;
        if (v == 'y' || v == 'Y') {
            verified = true;
            ofstream file("database.csv", ios::app);
            file << studentName << ",Verified,NotNeeded,No,NotNeeded,No,No\n";
        } else {
            cout << "Form not verified. Try again.\n";
        }
    } while (!verified);
}

void Visa() {
    char need;
    cout << "\nNeed visa? (y/n): ";
    cin >> need;
    if (need == 'n' || need == 'N') {
        updateField(studentName, 2, "NotNeeded");
        return;
    }
    char applied;
    do {
        cout << "Applied for visa? (y/n): ";
        cin >> applied;
    } while (!(applied == 'y' || applied == 'Y'));
    updateField(studentName, 2, "Applied");
}

void TuitionFee() {
    char paid;
    do {
        cout << "\nPaid tuition fee? (y/n): ";
        cin >> paid;
    } while (!(paid == 'y' || paid == 'Y'));
    updateField(studentName, 3, "Yes");
}

void Accommodation() {
    char acc;
    cout << "\nNeed accommodation? (y/n): ";
    cin >> acc;
    if (acc == 'y' || acc == 'Y') updateField(studentName, 4, "Assigned");
    else updateField(studentName, 4, "NotNeeded");
}

void AssignTutor() {
    cout << "\nTutor assigned.\n";
    updateField(studentName, 5, "Yes");

    char extra;
    cout << "Extra credits? (y/n): ";
    cin >> extra;
    if (extra == 'y' || extra == 'Y') updateField(studentName, 6, "Yes");
    else updateField(studentName, 6, "No");
}

void Termination() {
    cout << "\nStudent fully registered!\n";
}

int main() {
    ensureHeaderFile();
    cout << "Student Registration System\n";
    Initialization();
    Visa();
    TuitionFee();
    Accommodation();
    AssignTutor();
    Termination();
    cout << "Done\n";
    return 0;
}
