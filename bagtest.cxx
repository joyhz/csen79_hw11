/*
 * Names: Abraham Bhatti, David Lopez-Ryan, Sebastian Ortiz Ayala, Joy Zhu
 * Emails: abhatti@scu.edu, rlopezryan@scu.edu, sortizayala@scu.edu, jhzhu@scu.edu
 * Test program
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "bag.h"
#include "person.h"

using namespace std;
using namespace csen79;

// Added fault injection flag commands SET_FAULT, CLEAR_FAULT
enum Command { ENQ = 'E', DEQ = 'D', PRINT = 'P', QUIT = 'Q', SET_FAULT = 'S', CLEAR_FAULT = 'C'};

template <typename T>
void runBagTest(istream &input) {
    Bag<T> bag;     // template parameter T can be anything
    string line;
    bool quit = false;

    while (!quit && getline(input, line)) {
        if (line.empty()) continue;

        switch (line[0]) {
            case ENQ: {
                try {
                    stringstream ss(line.substr(1));
                    T value;
                    ss >> value;   // Works for any data type
                    bag.enQ(value);
                    cout << "Queued: " << value << endl;
                } catch (const out_of_range &e) {
                    cout << "Data out of range in enQ: " << e.what() << endl;
                } catch (const bad_alloc &e) {
                    cout << "Memory allocation error - new failed: " << e.what() << endl;
                }
            }
                break;
            case DEQ: {
                try {
                    T value = bag.deQ();
                    cout << "Dequeued: " << value << endl;
                } catch (const out_of_range &e) {
                    cout << "Data out of range in deQ: " << e.what() << endl;
                }
            }
                break;
            case PRINT: {
                cout << "Bag contents:" << endl;
                bag.print();
                cout << "Current size: " << bag.size() << endl;
            }
                break;
            case SET_FAULT: {
                cout << "Set fault inject flag to true" << endl;
                bag.setFaultInject();
            }
                break;
            case CLEAR_FAULT: {
                cout << "Set fault inject flag to false" << endl;
                bag.clearFaultInject();
            }
                break;
            case QUIT:
                quit = true;
                break;
            default:
                cout << "Unknown command: " << line << endl;
                break;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Cmd line format: ./bagtest <type> <filename>\n";
        return 1;
    }

    string type = argv[1];
    ifstream inputFile(argv[2]);
    if (!inputFile) {
        cout << "Cannot open file: " << argv[2] << endl;
        return 1;
    }

    // Specifically just for testing with int or Person, but could be changed to work with any data type
    if (type == "int") {
        runBagTest<int>(inputFile);
    } else if (type == "Person") {
        runBagTest<Person>(inputFile);
    } else {
        cout << "Unknown type: " << type << endl;
        return 1;
    }

    return 0;
}
