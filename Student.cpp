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
