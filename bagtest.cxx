/*
 * Names: Yuto Fraley, Theodore Griffin - Jones, Michael Tiburcio, Joy Zhu
 * Emails: yfraley@scu.edu, tgriffinjones@scu.edu, mtiburcio@scu.edu, jhzhu@scu.edu
 * Test program
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "bag.h"

using namespace std;
using namespace csen79;
// Added fault injection flag commands SET_FAULT, CLEAR_FAULT
enum Command { ENQ = 'E', DEQ = 'D', PRINT = 'P', QUIT = 'Q', SET_FAULT = 'S', CLEAR_FAULT = 'C'};

int main(int argc, char *argv[]) {
    Bag bag;
    string line;
    bool quit = false;

    istream *input; // Pointer to input stream
    ifstream inputFile;
    if (argc == 1) {
        cout << "No file provided, reading from standard input." << endl;
        input = &cin;   // input points to standard input
    }
    else {
        inputFile.open(argv[1]);
        cout << "Reading from file: " << argv[1] << endl;
        if (!inputFile) {
            cerr << "Error opening file: " << argv[1] << endl;
            exit(1);
        }
        input = &inputFile; // input points to the file stream
    }
    
    while (!quit && getline(*input,line)) {
        if (line.empty()) 
            continue;   // skip empty lines
        switch (line[0]) {
            case ENQ: {
                int data;
                try {
                    stringstream ss(line.substr(1));
                    ss >> data;
                    bag.enQ(data);
                    cout << "Queued: " << data << endl;
                } catch (const out_of_range &e) {
                    cerr << "Data out of range" << endl;
                } catch (const bad_alloc &e) {
                    cerr << "Memory allocation error - new failed" << endl;
                }
            }
                break;
            case DEQ: {
                try {
                    int data = bag.deQ();
                    cout << "Dequeued: " << data << endl;
                } catch (const out_of_range &e) {
                    cerr << "Data out of range in deQ: " << e.what() << endl;
                }
            }
                break;
            case PRINT: {
                cout << "Bag contents: " << endl;
                bag.print();
                cout << "Current size: " << bag.size() << endl;
            }
                break;
            case QUIT:
                quit = true;
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
            default:
                cerr << "Unknown command: " << line << endl;
                break;
        }
    }
    return EXIT_SUCCESS;
}
