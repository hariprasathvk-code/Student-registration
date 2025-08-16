#include <iostream>
#include <string>
using namespace std;

//  Registration 
void Register() {
    string registrationForm;
    bool verified = false;

    do {
        cout << "Complete registration form: ";
        cin >> registrationForm;

        // admin verification
        char verify;
        cout << "Admin verifies form? (y/n): ";
        cin >> verify;

        if (verify == 'y' || verify == 'Y') {
            verified = true;
            cout << "Form verified. Sending to department...\n";
            cout << "Student information stored in database.\n";
        } else {
            cout << "Form not verified. Please complete again.\n";
        }
    } while (!verified);

    cout << "Regstration completed.\n";
}

// Visa 
void Visa() {
    char needVisa;
    cout << "\nDo you need a visa? (y/n): ";
    cin >> needVisa;

    if (needVisa == 'n' || needVisa == 'N') {
        cout << "No visa needed.\n";
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
        }
    }
}

//  Tuition Fee 
void TuitionFee() {
    bool paid = false;
    cout << "\n Tuition Fee Payment \n";
    while (!paid) {
        char status;
        cout << "Have you paid the tuition fee? (y/n): ";
        cin >> status;
        if (status == 'y' || status == 'Y') {
            paid = true;
            cout << "Tuition fee paid successfully.\n";
        } else {
            cout << "Waiting until fee is paid...\n";
        }
    }
}

//  Accommodation 
void Accommodation() {
    char needAcc;
    cout << "\nDo you need accommodation? (y/n): ";
    cin >> needAcc;

    if (needAcc == 'y' || needAcc == 'Y') {
        cout << "Accommodation assigned successfully.\n";
    } else {
        cout << "No accommodation required.\n";
    }
}

//  Main 
int main() {
    cout << "=== Student Registration System ===\n";

    Register();           

    cout << "\n=== Registration Process Completed ===\n";
    return 0;
}
