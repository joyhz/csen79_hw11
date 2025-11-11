/*
 * Sin-Yaw Wang <swang24@scu.edu>
 * Test program for template Bag
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include "bag.h"
#include "person.h"

using namespace std;
using namespace csen79;

enum Command { PUSH = 'P', POP = 'O', PRINT = 'D', QUIT = 'Q' };

void testIntBag() {
    cout << "\n=== Testing Bag<int> ===" << endl;
    Bag<int> bag;
    string line;
    bool quit = false;
    
    while (!quit && std::getline(cin, line)) {
        switch (line[0]) {
        case PUSH: {
            int data;
            try {
                stringstream ss(line.substr(1));
                ss >> data;
                bag.push(data);
                cout << "Pushed: " << data << endl;
            } catch (const out_of_range &e) {
                cerr << "Error: " << e.what() << endl;
                continue;
            }
        }
            break;
        case POP:
            try {
                int val = bag.pop();
                cout << "Popped: " << val << endl;
            } catch (const out_of_range &e) {
                cerr << "Error: " << e.what() << endl;
            }
            break;
        case PRINT:
            bag.print();
            break;
        case QUIT:
            quit = true;
            break;
        default:
            cerr << "Unknown command: " << line << endl;
            break;
        }
    }
}

void testPersonBag() {
    cout << "\n=== Testing Bag<Person> ===" << endl;
    Bag<Person> personBag;
    
    //Sample people (No file but works the same ;-;)
    personBag.push(Person(4949049, 'F', "Myra", "Pack", 187.7, 67.4));
    personBag.push(Person(6769623, 'F', "Annalise", "Ontiveros", 186.7, 69.1));
    personBag.push(Person(7034384, 'F', "Lia", "Eubanks", 172.4, 65.1));
    personBag.push(Person(7753101, 'M', "Eluzer", "Whittington", 197.7, 71.2));
    personBag.push(Person(4725774, 'F', "Zendaya", "Colwell", 170.5, 63.4));
    
    cout << "\nAdded 5 people to the bag." << endl;
    
    // Print all people
    cout << "\nPrinting all people:" << endl;
    personBag.print();
    
    // Pop one person
    cout << "\nPopping one person:" << endl;
    try {
        Person p = personBag.pop();
        cout << "Popped: " << p << endl;
    } catch (const out_of_range &e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    // Print remaining people
    cout << "\nPrinting remaining people:" << endl;
    personBag.print();
    
    // Test copy constructor
    cout << "\nTesting copy constructor:" << endl;
    Bag<Person> personBag2(personBag);
    cout << "Copied bag contents:" << endl;
    personBag2.print();
    
    // Test move constructor
    cout << "\nTesting move constructor:" << endl;
    Bag<Person> personBag3(std::move(personBag2));
    cout << "Moved bag contents:" << endl;
    personBag3.print();
}

int main(void) {
    cout << "Choose test mode:" << endl;
    cout << "1. Test with int (interactive)" << endl;
    cout << "2. Test with Person (automatic)" << endl;
    cout << "3. Both" << endl;
    cout << "Enter choice: ";
    
    int choice;
    cin >> choice;
    cin.ignore(); // Clear newline
    
    switch (choice) {
    case 1:
        testIntBag();
        break;
    case 2:
        testPersonBag();
        break;
    case 3:
        testPersonBag();
        cout << "\n\nNow testing with int..." << endl;
        cout << "Enter commands (P <value>, O, D, Q):" << endl;
        testIntBag();
        break;
    default:
        cerr << "Invalid choice" << endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
