#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Patient {
    string name;
    int arrivalOrder;
    string condition;
    int priority;
    
    // Constructor
    Patient(string n, int order, string cond, int pri) 
        : name(n), arrivalOrder(order), condition(cond), priority(pri) {}
    
    // Overload the < operator for priority comparison
    bool operator<(const Patient& other) const {
        if (priority == other.priority) {
            return arrivalOrder > other.arrivalOrder; // Earlier arrival comes first if same priority
        }
        return priority > other.priority; // Lower priority number means higher priority
    }
};

// Function to display the current treatment queue
void displayQueue(priority_queue<Patient> pq) {
    cout << "\nCurrent Treatment Order:\n";
    cout << setw(15) << left << "Patient Name" 
        << setw(15) << "Arrival Order" 
        << setw(20) << "Emergency Condition" 
        << setw(10) << "Priority" << endl;
    cout << string(60, '-') << endl;
    
    while (!pq.empty()) {
        Patient p = pq.top();
        cout << setw(15) << left << p.name 
            << setw(15) << p.arrivalOrder 
            << setw(20) << p.condition 
            << setw(10) << p.priority << endl;
        pq.pop();
    }
    cout << endl;
}

// Function to get priority based on condition
int getPriority(string condition) {
    if (condition == "Heart Attack" || condition == "Stroke") return 1;
    if (condition == "Broken Leg" || condition == "Severe Burn" || condition == "Fractured Arm") return 2;
    if (condition == "Fever" || condition == "Food Poisoning" || condition == "Migraine") return 3;
    return 4; // For mild conditions
}

int main() {
    priority_queue<Patient> treatmentQueue;
    int arrivalCounter = 1;
    
    cout << "=== Hospital Patient Treatment System ===\n";
    
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Patient\n";
        cout << "2. Show Current Treatment Order\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            string name, condition;
            
            cout << "Enter patient name: ";
            cin.ignore(); // Clear input buffer
            getline(cin, name);
            
            cout << "Enter emergency condition: ";
            getline(cin, condition);
            
            int priority = getPriority(condition);
            
            Patient newPatient(name, arrivalCounter++, condition, priority);
            treatmentQueue.push(newPatient);
            
            cout << "\nPatient added successfully!\n";
            displayQueue(treatmentQueue);
        }
        else if (choice == 2) {
            displayQueue(treatmentQueue);
        }
        else if (choice == 3) {
            cout << "Exiting program...\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}