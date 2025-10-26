#include <iostream>
#include <vector>
#include <string>
using namespace std;

// -----------------------------
// Student Class Definition
// -----------------------------
class Student {
private:
    int rollNumber;
    string name;
    float grade;
    string course;

public:
    // Constructor
    Student(int r, string n, float g, string c) {
        rollNumber = r;
        name = n;
        grade = g;
        course = c;
    }

    // Getters
    int getRollNumber() { return rollNumber; }
    string getName() { return name; }
    float getGrade() { return grade; }
    string getCourse() { return course; }

    // Setters
    void setGrade(float g) { grade = g; }
    void setCourse(string c) { course = c; }

    // Optional: Determine Pass/Fail status
    string getStatus() {
        return (grade >= 50) ? "Pass" : "Fail";
    }

    // Display Student Info
    void display() {
        cout << "--------------------------------------\n";
        cout << "Roll Number : " << rollNumber << endl;
        cout << "Name        : " << name << endl;
        cout << "Grade       : " << grade << " (" << getStatus() << ")" << endl;
        cout << "Course      : " << course << endl;
        cout << "--------------------------------------\n";
    }
};

// -----------------------------
// Function Prototypes
// -----------------------------
void addStudent(vector<Student>& students);
void viewStudents(const vector<Student>& students);
void updateStudent(vector<Student>& students);
void deleteStudent(vector<Student>& students);

// -----------------------------
// Main Menu Function
// -----------------------------
int main() {
    vector<Student> students;
    int choice;

    while (true) {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                viewStudents(students);
                break;
            case 3:
                updateStudent(students);
                break;
            case 4:
                deleteStudent(students);
                break;
            case 5:
                cout << "Exiting program... Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}

// -----------------------------
// Add Student
// -----------------------------
void addStudent(vector<Student>& students) {
    int roll;
    string name, course;
    float grade;

    cout << "\nEnter Roll Number: ";
    cin >> roll;

    // Check if roll number already exists
    for (const auto& s : students) {
        if (s.getRollNumber() == roll) {
            cout << "Error: Roll Number already exists!\n";
            return;
        }
    }

    cout << "Enter Name: ";
    cin.ignore(); // Clear input buffer
    getline(cin, name);

    cout << "Enter Grade (0-100): ";
    cin >> grade;

    if (grade < 0 || grade > 100) {
        cout << "Invalid grade! Must be between 0 and 100.\n";
        return;
    }

    cout << "Enter Course: ";
    cin.ignore();
    getline(cin, course);

    students.push_back(Student(roll, name, grade, course));
    cout << "Student added successfully!\n";
}

// -----------------------------
// View Students
// -----------------------------
void viewStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records available.\n";
        return;
    }

    cout << "\n===== STUDENT LIST =====\n";
    for (const auto& s : students) {
        s.display();
    }
}

// -----------------------------
// Update Student
// -----------------------------
void updateStudent(vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records available.\n";
        return;
    }

    int roll;
    cout << "Enter Roll Number of student to update: ";
    cin >> roll;

    for (auto& s : students) {
        if (s.getRollNumber() == roll) {
            float newGrade;
            string newCourse;

            cout << "Enter new Grade (or -1 to skip): ";
            cin >> newGrade;

            if (newGrade != -1) {
                if (newGrade >= 0 && newGrade <= 100)
                    s.setGrade(newGrade);
                else {
                    cout << "Invalid grade! Skipping grade update.\n";
                }
            }

            cout << "Enter new Course (or press ENTER to skip): ";
            cin.ignore();
            getline(cin, newCourse);
            if (!newCourse.empty()) {
                s.setCourse(newCourse);
            }

            cout << "Student record updated successfully!\n";
            return;
        }
    }

    cout << "Student with Roll Number " << roll << " not found.\n";
}

// -----------------------------
// Delete Student
// -----------------------------
void deleteStudent(vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records available.\n";
        return;
    }

    int roll;
    cout << "Enter Roll Number of student to delete: ";
    cin >> roll;

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getRollNumber() == roll) {
            students.erase(it);
            cout << "Student deleted successfully!\n";
            return;
        }
    }

    cout << "Student with Roll Number " << roll << " not found.\n";
}
