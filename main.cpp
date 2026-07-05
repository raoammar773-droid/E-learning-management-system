#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Notification {
private:
    vector<string> messages;

public:
    void addNotification(string msg) {
        messages.push_back(msg);
        ofstream notifFile("notifications.txt", ios::app);
        if (notifFile.is_open()) {
            notifFile << msg << endl;
            notifFile.close();
        }
    }

    void showNotifications() {
        cout << "\n========== NOTIFICATIONS ==========" << endl;
        if (messages.empty()) {
            cout << "No new notifications." << endl;
        } else {
            for (size_t i = 0; i < messages.size(); i++) {
                cout << i + 1 << ". " << messages[i] << endl;
            }
        }
        cout << "====================================" << endl;
    }

    void clearNotifications() {
        messages.clear();
        cout << "\nAll notifications cleared!" << endl;
    }
};

class User {
private:
    string name;
    string id;

protected:
    Notification notif;

public:
    User() : name(""), id("") {}
    User(string n, string i) : name(n), id(i) {}

    string getName() const { return name; }
    string getId()   const { return id;   }
    void setName(string n) { name = n; }
    void setId(string i)   { id = i;   }

    virtual bool login()    = 0;
    virtual void showMenu() = 0;
    virtual void resetNotifications() = 0;

    virtual ~User() {}
};


class Student : public User {
private:
    vector<string> subjects;

public:
    Student() {
        subjects = {
            "Object Oriented Programming",
            "Discrete Structure",
            "Digital Logic Design",
            "Ideology of Pakistan",
            "English",
            "Urdu"
        };
    }

    void resetNotifications() override {
        notif.addNotification("Welcome to E-Learning System!");
        notif.addNotification("New Assignment posted in OOP - Due: Friday");
        notif.addNotification("Quiz scheduled in Discrete Structure - Tomorrow");
        notif.addNotification("New course material uploaded in English");
    }

    bool login() override {
        string inputName, inputId;
        cout << "\n--- Student Login ---" << endl;
        cout << "Enter Name: ";
        cin >> inputName;
        cout << "Enter ID: ";
        cin >> inputId;

        if (inputName == "ali" && inputId == "12345") {
            setName(inputName);
            setId(inputId);
            cout << "\nLogin Successful! Welcome Student: " << getName() << endl;
            return true;
        } else {
            cout << "\nInvalid Student Credentials!" << endl;
            return false;
        }
    }

    void showMenu() override {
        int mainChoice;

      
        while (true) {
            cout << "\n========== STUDENT MENU ==========" << endl;
            cout << "1. View Subjects & Activities" << endl;
            cout << "2. View Notifications" << endl;
            cout << "3. Clear Notifications" << endl;
            cout << "4. Logout" << endl;
            cout << "===================================" << endl;
            cout << "Enter Choice: ";
            cin >> mainChoice;

            if (mainChoice == 1) {
                int subjectChoice, activityChoice;

                cout << "\n*** Enrolled Subjects ***" << endl;
                for (size_t i = 0; i < subjects.size(); i++) {
                    cout << i + 1 << ". " << subjects[i] << endl;
                }
                cout << "Select a subject (1-6): ";
                cin >> subjectChoice;

                if (subjectChoice >= 1 && subjectChoice <= 6) {
                    string chosenSubject = subjects[subjectChoice - 1];

                    cout << "\nSelect an option for " << chosenSubject << ":" << endl;
                    cout << "1. Assignments" << endl;
                    cout << "2. Class" << endl;
                    cout << "3. Quiz" << endl;
                    cout << "Your Choice (1-3): ";
                    cin >> activityChoice;

                    string activityName = "";
                    if (activityChoice == 1) activityName = "Assignments";
                    else if (activityChoice == 2) activityName = "Class";
                    else if (activityChoice == 3) activityName = "Quiz";

                    if (activityChoice >= 1 && activityChoice <= 3) {
                        cout << "\nDone and thanks!" << endl;

                        notif.addNotification("You completed " + activityName + " in " + chosenSubject);

                        ofstream logFile("student_logs.txt", ios::app);
                        if (logFile.is_open()) {
                            logFile << "Student: " << getName() << " (ID: " << getId()
                                    << ") selected " << activityName
                                    << " in " << chosenSubject << endl;
                            logFile.close();
                        }

                        notif.showNotifications();

                    } else {
                        cout << "\nInvalid choice!" << endl;
                    }
                } else {
                    cout << "\nInvalid Subject Selection!" << endl;
                }

            } else if (mainChoice == 2) {
                notif.showNotifications();

            } else if (mainChoice == 3) {
                notif.clearNotifications();

            } else if (mainChoice == 4) {
                cout << "\nLogged out successfully!" << endl;
                break; // Menu loop se bahar aao

            } else {
                cout << "\nInvalid Choice!" << endl;
            }
        }
    }

    ~Student() override {}
};


class Teacher : public User {
private:
    string section;

public:
    void resetNotifications() override {
        notif.addNotification("Welcome Teacher! New student enrolled in Section 2E.");
        notif.addNotification("Assignment deadline reminder: OOP Assignment Due Tomorrow.");
        notif.addNotification("Quiz results are pending for Section 2E.");
    }

    bool login() override {
        string inputName, inputId;
        cout << "\n--- Teacher Login ---" << endl;
        cout << "Enter Name: ";
        cin >> inputName;
        cout << "Enter ID: ";
        cin >> inputId;

        if (inputName == "Dr.zubair" && inputId == "54321") {
            setName(inputName);
            setId(inputId);
            cout << "\nLogin Successful! Welcome Teacher: " << getName() << endl;
            return true;
        } else {
            cout << "\nInvalid Teacher Credentials!" << endl;
            return false;
        }
    }

    void showMenu() override {
        int mainChoice;

       
        while (true) {
            cout << "\n========== TEACHER MENU ==========" << endl;
            cout << "1. Manage Section" << endl;
            cout << "2. View Notifications" << endl;
            cout << "3. Clear Notifications" << endl;
            cout << "4. Logout" << endl;
            cout << "===================================" << endl;
            cout << "Enter Choice: ";
            cin >> mainChoice;

            if (mainChoice == 1) {
                cout << "\nEnter Section: ";
                cin >> section;

                if (section == "2E" || section == "2e") {
                    int activityChoice;
                    cout << "\n*** Section 2E Management ***" << endl;
                    cout << "1. Assignment" << endl;
                    cout << "2. Class" << endl;
                    cout << "3. Quiz" << endl;
                    cout << "Select an option (1-3): ";
                    cin >> activityChoice;

                    string activityName = "";
                    if (activityChoice == 1) activityName = "Assignment";
                    else if (activityChoice == 2) activityName = "Class";
                    else if (activityChoice == 3) activityName = "Quiz";

                    if (activityChoice >= 1 && activityChoice <= 3) {
                        cout << "\nDone" << endl;

                        notif.addNotification("You posted " + activityName + " for Section 2E. Students have been notified.");

                        ofstream logFile("teacher_logs.txt", ios::app);
                        if (logFile.is_open()) {
                            logFile << "Teacher: " << getName() << " managed "
                                    << activityName << " for Section 2E." << endl;
                            logFile.close();
                        }

                        notif.showNotifications();

                    } else {
                        cout << "\nInvalid Choice!" << endl;
                    }
                } else {
                    cout << "\nInvalid choice (Only Section 2E is accessible)!" << endl;
                }

            } else if (mainChoice == 2) {
                notif.showNotifications();

            } else if (mainChoice == 3) {
                notif.clearNotifications();

            } else if (mainChoice == 4) {
                cout << "\nLogged out successfully!" << endl;
                break; // Menu loop se bahar aao

            } else {
                cout << "\nInvalid Choice!" << endl;
            }
        }
    }

    ~Teacher() override {}
};


int main() {
    int continueChoice;


    do {
        int roleChoice;
        User* userPtr = nullptr;

        cout << "\n======================================" << endl;
        cout << "   E-LEARNING MANAGEMENT SYSTEM       " << endl;
        cout << "======================================" << endl;
        cout << "Identify your role:" << endl;
        cout << "1. Student" << endl;
        cout << "2. Teacher" << endl;
        cout << "Enter choice (1 or 2): ";
        cin >> roleChoice;

        if (roleChoice == 1) {
            userPtr = new Student();
        } else if (roleChoice == 2) {
            userPtr = new Teacher();
        } else {
            cout << "\nInvalid Role Selection!" << endl;
        }

        if (userPtr != nullptr) 
		{
            if (userPtr->login()) {
                userPtr->resetNotifications(); 
                userPtr->showMenu();
            }
            delete userPtr;
            userPtr = nullptr;
        }


        cout << "\n======================================" << endl;
        cout << " Do you want to continue?" << endl;
        cout << " Press 1 to continue | Press 0 to exit" << endl;
        cout << "======================================" << endl;
        cout << "Your Choice: ";
        cin >> continueChoice;

    }
      while (continueChoice == 1);

    cout << "\nThank you for using E-Learning System. Goodbye!" << endl;

    return 0;
}