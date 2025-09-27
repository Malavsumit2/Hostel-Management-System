//source code 
#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class Student {
public:
    string name;
    int roll;
    int room;

    Student(string n, int r, int rm) {
        name = n;
        roll = r;
        room = rm;
    }
};

class Complaint {
public:
    int id;
    string description;
    string studentName;
    int studentRoom;
    string serviceType;
    bool resolved;

    Complaint(int i, string d, string sName, int sRoom, string sType) {
        id = i;
        description = d;
        studentName = sName;
        studentRoom = sRoom;
        serviceType = sType;
        resolved = false;
    }
};

class Hostel {
private:
    vector<Student> students;
    vector<Complaint> complaints;
    int complaintCounter = 1;

public:
    void registerStudent() {
        string name;
        int roll, room;

        cout << "Enter Name: ";
        getline(cin, name); 
        cout << "Enter Roll No: ";
        cin >> roll;
        cout << "Enter Room No: ";
        cin >> room;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

        students.push_back(Student(name, roll, room));
        cout << "Registration successful!\n";
    }

    void viewStudents() {
        if (students.empty()) {
            cout << "No students found.\n";
            return;
        }
        cout << "\n---- Student List ----\n";
        for (auto &s : students) {
            cout << "Name: " << s.name
                 << " | Roll No: " << s.roll
                 << " | Room No: " << s.room << "\n";
        }
    }

    void deleteStudent(int roll) {
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->roll == roll) {
                students.erase(it);
                cout << "Student with Roll No " << roll << " deleted successfully.\n";
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void addComplaint(int roll) {
        for (auto &s : students) {
            if (s.roll == roll) {
                string desc;
                cout << "Enter Complaint Description: ";
                getline(cin, desc);

                cout << "Select Service Type:\n1. Electrician\n2. Plumber\n3. Sweeper\nChoice: ";
                int sChoice;
                cin >> sChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // buffer clear

                string serviceType;
                if (sChoice == 1) serviceType = "Electrician";
                else if (sChoice == 2) serviceType = "Plumber";
                else if (sChoice == 3) serviceType = "Sweeper";
                else serviceType = "General";

                complaints.push_back(Complaint(complaintCounter++, desc, s.name, s.room, serviceType));
                cout << "Complaint added successfully!\n";
                return;
            }
        }
        cout << "You are not registered! Please register first.\n";
    }

    void viewComplaints(string role, string subRole) {
        if (complaints.empty()) {
            cout << "No complaints found.\n";
            return;
        }

        cout << "\n---- Complaints ----\n";
        for (auto &c : complaints) {
            if (role == "ServiceProvider") {
                if (c.serviceType == subRole) { 
                    cout << "Complaint ID: " << c.id
                         << " | Student: " << c.studentName
                         << " | Room: " << c.studentRoom
                         << " | Complaint: " << c.description
                         << " | Status: " << (c.resolved ? "Resolved" : "Pending") << "\n";
                }
            } else { 
                cout << "Complaint ID: " << c.id
                     << " | Student: " << c.studentName
                     << " | Room: " << c.studentRoom
                     << " | Complaint: " << c.description
                     << " | Service: " << c.serviceType
                     << " | Status: " << (c.resolved ? "Resolved" : "Pending") << "\n";
            }
        }
    }

    void approveComplaint(int id) {
        for (auto &c : complaints) {
            if (c.id == id) {
                if (c.resolved) {
                    cout << "Complaint ID " << id << " is already resolved.\n";
                } else {
                    c.resolved = true;
                    cout << "Complaint ID " << id << " resolved.\n";
                }
                return;
            }
        }
        cout << "Complaint not found.\n";
    }
};

int main() {
    Hostel hostel;
    string role, subRole = "";
    int choice;

    while (true) {
        cout << "\n=== Hostel Management System ===\n";
        cout << "Select Role:\n1. Student\n2. Service Provider\n3. Exit\nChoice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline

        if (choice == 1) role = "Student";
        else if (choice == 2) role = "ServiceProvider";
        else if (choice == 3) break;
        else {
            cout << "Invalid choice!\n";
            continue;
        }

        if (role == "Student") {
            while (true) {
                cout << "\n--- Student Menu ---\n";
                cout << "1. Register Yourself\n";
                cout << "2. View Students\n";
                cout << "3. Add Complaint\n";
                cout << "4. View Complaints\n";
                cout << "5. Delete Student\n";
                cout << "6. Back to Role Selection\n";
                cout << "Enter choice: ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

                if (choice == 1) hostel.registerStudent();
                else if (choice == 2) hostel.viewStudents();
                else if (choice == 3) {
                    int roll;
                    cout << "Enter your Roll No: ";
                    cin >> roll;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    hostel.addComplaint(roll);
                }
                else if (choice == 4) {
                    hostel.viewComplaints(role, subRole);
                    cout << "Press Enter to continue...";
                    cin.get();
                }
                else if (choice == 5) {
                    int roll;
                    cout << "Enter Roll No to delete: ";
                    cin >> roll;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    hostel.deleteStudent(roll);
                }
                else if (choice == 6) break;
                else cout << "Invalid choice!\n";
            }
        } 
        else if (role == "ServiceProvider") {
            cout << "Select your service type:\n1. Electrician\n2. Plumber\n3. Sweeper\nChoice: ";
            int serviceChoice;
            cin >> serviceChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
            if (serviceChoice == 1) subRole = "Electrician";
            else if (serviceChoice == 2) subRole = "Plumber";
            else if (serviceChoice == 3) subRole = "Sweeper";

            while (true) {
                cout << "\n--- Service Provider Menu (" << subRole << ") ---\n";
                cout << "1. View Complaints\n";
                cout << "2. Resolve Complaint\n";
                cout << "3. Back to Role Selection\n";
                cout << "Enter choice: ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

                if (choice == 1) {
                    hostel.viewComplaints(role, subRole);
                    cout << "Press Enter to continue...";
                    cin.get(); 
                }
                else if (choice == 2) {
                    int id;
                    cout << "Enter Complaint ID to resolve: ";
                    cin >> id;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    hostel.approveComplaint(id);
                    cout << "Press Enter to continue...";
                    cin.get(); 
                }
                else if (choice == 3) break;
                else cout << "Invalid choice!\n";
            }
        }
    }

    cout << "Exiting Program...\n";
    return 0;
}

