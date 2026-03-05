# Student Management System (C++)

## Overview
This is a **Student Management System** developed in **C++**, designed to manage student information efficiently.  
It is a console-based application with a **user-friendly interface** and **strict input validation**, making it robust for real-world usage.

The system supports **CRUD operations**, searching, sorting, department reports, and GPA statistics. Student data is **persistently stored** in a text file.

---

## Features
- Add, view, update, delete student records
- Search students by ID or Name (partial search supported)
- Sort students by ID, Name, or GPA
- Department-wise student report
- GPA statistics (Highest, Lowest, Average)
- Persistent storage using `students.txt`
- Strict input validation for numbers, GPA, and non-empty strings
- Colored messages for prompts, errors, and success notifications
- ASCII-based menus for Windows compatibility

---

## Technologies Used
- **C++** (OOP, STL, file handling)
- **Vector, string, algorithm**
- **ANSI color codes** for enhanced terminal messages

---

## Getting Started

### Prerequisites
- Windows or Linux system
- **C++ compiler** (e.g., `g++`)
- **VS Code** or any terminal (PowerShell recommended for Windows)

### How to Run
1. Clone the repository:
git clone https://github.com/mabubakarali/Student-Management-System-Cpp.git
2. Navigate to the project folder:
cd Student-Management-System-Cpp
3. Compile the program:
g++ main.cpp -o StudentManagementSystem
4. Run the program:
./StudentManagementSystem
