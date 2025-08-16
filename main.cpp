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

//  Main 
int main() {
    cout << "=== Student Registration System ===\n";

    Register();           

    cout << "\n=== Registration Process Completed ===\n";
    return 0;
}
