#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"

// ======================= Input Handling Functions =======================
int getIntInput(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Invalid input! Please enter a number.\n" << RESET;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

float getFloatInput(const string &prompt) {
    float value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Invalid input! Please enter a number.\n" << RESET;
        } else if (value < 0 || value > 4.0) {
            cout << RED << "GPA must be between 0 and 4.0\n" << RESET;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

string getStringInput(const string &prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << RED << "Input cannot be empty!\n" << RESET;
        } else return input;
    }
}

// ======================= Student Class =======================
class Student {
public:
    int id;
    string name;
    int age;
    string department;
    float gpa;

    Student() {}
    Student(int _id, string _name, int _age, string _dept, float _gpa) {
        id = _id; name = _name; age = _age; department = _dept; gpa = _gpa;
    }

    void display() const {
        cout << left << setw(5) << id
             << setw(20) << name
             << setw(5) << age
             << setw(15) << department
             << setw(5) << gpa << endl;
    }
};

// ======================= Student Management System =======================
class StudentManagementSystem {
private:
    vector<Student> students;
    string filename = "students.txt";

    void saveToFile() {
        ofstream outFile(filename);
        for (auto &s : students) {
            outFile << s.id << "," << s.name << "," << s.age << "," << s.department << "," << s.gpa << endl;
        }
        outFile.close();
    }

    void loadFromFile() {
        ifstream inFile(filename);
        if(!inFile) return;
        string line;
        while(getline(inFile, line)) {
            if(line.empty()) continue;
            int id, age;
            float gpa;
            string name, dept;
            size_t prev = 0, pos;

            pos = line.find(',', prev);
            id = stoi(line.substr(prev, pos-prev));
            prev = pos + 1;

            pos = line.find(',', prev);
            name = line.substr(prev, pos-prev);
            prev = pos + 1;

            pos = line.find(',', prev);
            age = stoi(line.substr(prev, pos-prev));
            prev = pos + 1;

            pos = line.find(',', prev);
            dept = line.substr(prev, pos-prev);
            prev = pos + 1;

            gpa = stof(line.substr(prev));
            students.push_back(Student(id, name, age, dept, gpa));
        }
        inFile.close();
    }

    void displayHeader() {
        cout << BLUE;
        cout << "====================================\n";
        cout << "         STUDENT MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << RESET;
    }

    void displayStudents(const vector<Student>& list) {
        if(list.empty()) {
            cout << RED << "No students found!\n" << RESET;
            return;
        }
        cout << left << setw(5) << "ID"
             << setw(20) << "Name"
             << setw(5) << "Age"
             << setw(15) << "Department"
             << setw(5) << "GPA" << endl;
        cout << "--------------------------------------------------\n";
        for(auto &s : list) s.display();
    }

public:
    StudentManagementSystem() { loadFromFile(); }
    ~StudentManagementSystem() { saveToFile(); }

    void welcomeMessage() {
        cout << GREEN;
        cout << "====================================\n";
        cout << "  Welcome to the Student Management System\n";
        cout << "====================================\n";
        cout << RESET;
    }

    void addStudent() {
        int id = getIntInput(CYAN "Enter Student ID: " RESET);
        string name = getStringInput(CYAN "Enter Name: " RESET);
        int age = getIntInput(CYAN "Enter Age: " RESET);
        string department = getStringInput(CYAN "Enter Department: " RESET);
        float gpa = getFloatInput(CYAN "Enter GPA (0-4): " RESET);

        students.push_back(Student(id, name, age, department, gpa));
        cout << GREEN << "Student added successfully!" << RESET << endl;
    }

    void viewAllStudents() { displayHeader(); displayStudents(students); }

    void searchStudent() {
        if(students.empty()) { cout << RED << "No students to search!\n" << RESET; return; }

        int choice = getIntInput(YELLOW "Search by: 1. ID  2. Name\nChoice: " RESET);
        bool found = false;

        if(choice == 1) {
            int id = getIntInput("Enter ID: ");
            for(auto &s : students) {
                if(s.id == id) { cout << GREEN << "Student found:\n" << RESET; s.display(); found = true; break; }
            }
        } else if(choice == 2) {
            string name = getStringInput("Enter Name or partial: ");
            for(auto &s : students) {
                if(s.name.find(name) != string::npos) { cout << GREEN << "Student found:\n" << RESET; s.display(); found = true; }
            }
        } else { cout << RED << "Invalid choice!\n" << RESET; return; }

        if(!found) cout << RED << "Student not found!\n" << RESET;
    }

    void updateStudent() {
        if(students.empty()) { cout << RED << "No students to update!\n" << RESET; return; }

        int id = getIntInput("Enter ID to update: ");
        bool found = false;
        for(auto &s : students) {
            if(s.id == id) {
                s.name = getStringInput(CYAN "Enter new Name: " RESET);
                s.age = getIntInput(CYAN "Enter new Age: " RESET);
                s.department = getStringInput(CYAN "Enter new Department: " RESET);
                s.gpa = getFloatInput(CYAN "Enter new GPA (0-4): " RESET);
                cout << GREEN << "Student updated successfully!" << RESET << endl;
                found = true; break;
            }
        }
        if(!found) cout << RED << "Student not found!\n" << RESET;
    }

    void deleteStudent() {
        if(students.empty()) { cout << RED << "No students to delete!\n" << RESET; return; }

        int id = getIntInput("Enter ID to delete: ");
        bool found = false;
        for(auto it = students.begin(); it != students.end(); ++it) {
            if(it->id == id) { students.erase(it); cout << GREEN << "Student deleted!\n" << RESET; found = true; break; }
        }
        if(!found) cout << RED << "Student not found!\n" << RESET;
    }

    void sortStudents() {
        int choice = getIntInput(YELLOW "Sort by: 1. ID  2. Name  3. GPA\nChoice: " RESET);
        if(choice == 1) sort(students.begin(), students.end(), [](Student a, Student b){ return a.id < b.id; });
        else if(choice == 2) sort(students.begin(), students.end(), [](Student a, Student b){ return a.name < b.name; });
        else if(choice == 3) sort(students.begin(), students.end(), [](Student a, Student b){ return a.gpa > b.gpa; });
        else { cout << RED << "Invalid choice!\n" << RESET; return; }
        cout << GREEN << "Students sorted successfully!\n" << RESET;
    }

    void departmentReport() {
        if(students.empty()) { cout << RED << "No students!\n" << RESET; return; }
        string dept = getStringInput("Enter Department: ");
        vector<Student> deptList;
        for(auto &s : students) if(s.department == dept) deptList.push_back(s);
        displayStudents(deptList);
    }

    void gpaStatistics() {
        if(students.empty()) { cout << RED << "No students!\n" << RESET; return; }
        float maxG = students[0].gpa, minG = students[0].gpa, sum = 0;
        for(auto &s : students) {
            if(s.gpa > maxG) maxG = s.gpa;
            if(s.gpa < minG) minG = s.gpa;
            sum += s.gpa;
        }
        cout << GREEN << "GPA Statistics:\n" << RESET;
        cout << "Highest GPA: " << maxG << "\nLowest GPA: " << minG << "\nAverage GPA: " << sum/students.size() << endl;
    }

    void menu() {
        welcomeMessage();
        int choice;
        do {
            cout << "\n+---------------- Menu ----------------+\n";
            cout << "1. Add Student\n2. View All Students\n3. Search Student\n4. Update Student\n5. Delete Student\n";
            cout << "6. Sort Students\n7. Department Report\n8. GPA Statistics\n9. Exit\n";
            cout << "+-------------------------------------+\n";
            choice = getIntInput("Enter your choice: ");
            if(choice < 1 || choice > 9) { cout << RED << "Invalid choice! Please select 1-9\n" << RESET; continue; }

            switch(choice) {
                case 1: addStudent(); break;
                case 2: viewAllStudents(); break;
                case 3: searchStudent(); break;
                case 4: updateStudent(); break;
                case 5: deleteStudent(); break;
                case 6: sortStudents(); break;
                case 7: departmentReport(); break;
                case 8: gpaStatistics(); break;
                case 9: cout << GREEN << "Exiting... Goodbye!\n" << RESET; break;
            }
        } while(choice != 9);
    }
};

// ======================= Main =======================
int main() {
    StudentManagementSystem sms;
    sms.menu();
    return 0;
}