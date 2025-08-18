#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

string studentName;

string toLower(string s){ transform(s.begin(), s.end(), s.begin(), ::tolower); return s; }

vector<vector<string>> readDB(){
    vector<vector<string>> data;
    ifstream file("database.csv");
    string line;
    while(getline(file, line)){
        vector<string> row; string cell; stringstream ss(line);
        while(getline(ss, cell, ',')) row.push_back(cell);
        if(!row.empty()) data.push_back(row);
    }
    return data;
}

// write CSV
void writeDB(const vector<vector<string>>& data){
    ofstream file("database.csv");
    for(const auto& row : data){
        for(size_t i=0;i<row.size();++i){
            file << row[i];
            if(i+1<row.size()) file << ",";
        }
        file << "\n";
    }
}


size_t dataStart(const vector<vector<string>>& db){
    if(!db.empty() && !db[0].empty() && db[0][0] == "Name") return 1;
    return 0;
}

int fieldCol(const string& field){
    if(field=="Name") return 0;
    if(field=="Verified") return 1;
    if(field=="VisaStatus") return 2;
    if(field=="FeePaid") return 3;
    if(field=="Accommodation") return 4;
    if(field=="TutorAssigned") return 5;
    if(field=="ExtraCredits") return 6;
    return -1;
}


void ensureCols(vector<string>& row){
    if(row.size() < 7) row.resize(7, "");
}


bool studentExists(const string& name){
    auto db = readDB();
    size_t start = dataStart(db);
    for(size_t i=start; i<db.size(); ++i){
        if(!db[i].empty() && toLower(db[i][0]) == toLower(name)) return true;
    }
    return false;
}


void updateField(const string& name, const string& field, const string& value){
    auto db = readDB();
    int col = fieldCol(field);
    if(col < 0) return;

    size_t start = dataStart(db);
    for(size_t i=start; i<db.size(); ++i){
        if(!db[i].empty() && toLower(db[i][0]) == toLower(name)){
            ensureCols(db[i]);
            db[i][col] = value;
            writeDB(db);
            return;
        }
    }
}

// create header if file missing or empty
void ensureHeaderFile(){
    ifstream in("database.csv");
    if(!in.good()){
        ofstream f("database.csv");
        f << "Name,Verified,VisaStatus,FeePaid,Accommodation,TutorAssigned,ExtraCredits\n";
        f.close();
    }else{
        // if file exists but empty, add header
        string any; getline(in, any);
        if(any.empty()){
            ofstream f("database.csv");
            f << "Name,Verified,VisaStatus,FeePaid,Accommodation,TutorAssigned,ExtraCredits\n";
            f.close();
        }
    }
}



void Initialization(){
    bool verified = false;
    do{
        cout << "\nEnter student name: ";
        cin >> studentName;

        if(studentExists(studentName)){
            cout << "Student already exists. Continuing to update their record...\n";
            verified = true;
            break;
        }

        char v; cout << "Admin verifies form? (y/n): "; cin >> v;
        if(v=='y' || v=='Y'){
            verified = true;
            ofstream file("database.csv", ios::app);
            // initialize with defaults; updates will overwrite below
            file << studentName << ",Verified,NotNeeded,No,NotNeeded,No,No\n";
            file.close();
        }else{
            cout << "Form not verified. Try again.\n";
        }
    }while(!verified);
}

void Visa(){
    char need; cout << "\nNeed visa? (y/n): "; cin >> need;
    if(need=='n' || need=='N'){
        updateField(studentName, "VisaStatus", "NotNeeded");
        return;
    }
    char applied;
    do{
        cout << "Applied for visa? (y/n): ";
        cin >> applied;
    }while(!(applied=='y' || applied=='Y'));
    updateField(studentName, "VisaStatus", "Applied");
}

void TuitionFee(){
    char paid;
    do{
        cout << "\nPaid tuition fee? (y/n): ";
        cin >> paid;
    }while(!(paid=='y' || paid=='Y'));
    updateField(studentName, "FeePaid", "Yes");
}

void Accommodation(){
    char acc; cout << "\nNeed accommodation? (y/n): "; cin >> acc;
    if(acc=='y' || acc=='Y') updateField(studentName, "Accommodation", "Assigned");
    else updateField(studentName, "Accommodation", "NotNeeded");
}

void AssignTutor(){
    cout << "\nTutor assigned.\n";
    updateField(studentName, "TutorAssigned", "Yes");

    char extra; cout << "Extra credits? (y/n): "; cin >> extra;
    if(extra=='y' || extra=='Y') updateField(studentName, "ExtraCredits", "Yes");
    else updateField(studentName, "ExtraCredits", "No");
}

void Termination(){
    cout << "\nStudent fully registered!\n";
}

int main(){
    ensureHeaderFile(); // create header if missing/empty

    cout << "Student Registration System\n";
    Initialization();
    Visa();
    TuitionFee();
    Accommodation();
    AssignTutor();
    Termination();
    cout << " Done \n";
    return 0;
}
