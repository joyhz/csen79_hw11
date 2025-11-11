/*
 * Names: Abraham Bhatti, David Lopez-Ryan, Sebastian Ortiz Ayala, Joy Zhu
 * Emails: abhatti@scu.edu, rlopezryan@scu.edu, sortizayala@scu.edu, jhzhu@scu.edu
 * recipe for containers using pointers
 */
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <string.h>
#include <new>
#include "bag.h"

namespace csen79 {

    // assignment
    Bag &Bag::operator=(const Bag &rhs) {
        std::cout << "assign" << std::endl;
        if (this != &rhs) {  // Avoiding any self-assignment of rhs to this
            delete [] data;
            data = nullptr;     // Setting data to nullptr as a safety net
            capacity = 0;
            count = 0;
            front = 0;
            rear = 0;
            if (rhs.capacity > 0) { // Should keep front and rear to be the same as the rhs ones, not rearranging the queue
                capacity = rhs.capacity;
                count = rhs.count;
                front = rhs.front;
                rear = rhs.rear;
                data = new Data[capacity];
                throwNewFailure();
                for (std::size_t i = 0; i < count; ++i) {
                    data[i] = rhs.data[(front + i) % capacity];
                }
            }
        }
        return *this;
    }

    Bag::~Bag(){
        delete[] data;
    }

    // move constructor
    Bag::Bag(Bag &&rhs) {
        std::cout << "move constructor; calling move operator" << std::endl;
        this->operator=(rhs);
    }

    // copy constructor
    Bag::Bag(const Bag &rhs) {
        std::cout << "copy constructor: " << std::endl;
        if (capacity > 0) {
            data = new Data[capacity];
            throwNewFailure();
            for (std::size_t i = 0; i < count; ++i) {
                data[i] = rhs.data[(front + i) % capacity];
            }
        }
    }

    // move
    Bag &Bag::operator=(Bag &&rhs) {
        std::cout << "move operator: " << std::endl;
        if (this != &rhs) {  // Avoiding self-assignment
            delete [] data;  // Releasing current data

            data = rhs.data;
            capacity = rhs.capacity;
            count = rhs.count;
            front = rhs.front;
            rear = rhs.rear;

            // Setting rhs data to null and its parameters to 0
            rhs.data = nullptr;
            rhs.capacity = 0;
            rhs.count = 0;
            rhs.front = 0;
            rhs.rear = 0;
        }
        return *this;
    }

    void Bag::throwNewFailure() {
        if (inject_new_fail == true) {
            std::cout << "Inject new failure" << std::endl;
            delete [] data;
            data = nullptr;
            throw std::bad_alloc();
        }
    }

    // simple access functions
    // replace them with appropriate ones for assignments
    bool Bag::isEmpty() const {
        return (count == 0);
    }

    bool Bag::isFull() const {
        return (count == capacity);
    }

    std::size_t Bag::size() const {
        return count;
    }

    void Bag::expandCapacity() {
        std::size_t oldCap = capacity;
        std::size_t newCapacity = (oldCap > 0) ? (oldCap * 2) : 1;
        std::cout << "Old capacity: " << oldCap << ", new capacity: " << newCapacity << std::endl;
        Bag::Data* newData = nullptr;

        // Allocating memory for a new, expanded queue
        newData = new Bag::Data[newCapacity];
        throwNewFailure();

        // Copying elements from the old queue to the new one
        for (std::size_t i = 0; i < count; ++i) {
            newData[i] = data[(front + i) % oldCap];
        }

        delete [] data;             // Deleting the old queue
        data = newData;             // Having data point to the new queue
        capacity = newCapacity;     // Updating the capacity
        front = 0;
        rear = count;               // Updating rear to the current count
        return;
    }

    void Bag::enQ(const Data &d) {
        if ((data == nullptr) && (count == 0)) {
            data = new Data[capacity]; // Capacity is initialized to 10
            throwNewFailure();
        }
        if (isFull()) {
            expandCapacity();   // Double the capacity if queue is full
        }

        data[rear] = d;
        rear = (rear + 1) % capacity;     // Updating rear
        ++count;                          // Updating count
        return;
    };

    Bag::Data Bag::deQ() {
        if (isEmpty()) {
            throw std::out_of_range("Out of range: Can't dequeue, queue is empty");
        }

        Data frontElt = data[front];
        front = (front + 1) % capacity;   // Updating front
        --count;                          // Updating count
        return frontElt;                  // Returning the dequeued front element
    };

    void Bag::print() const {
        if(isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
        }
        else {
            for (std::size_t i = 0; i < count; i++) {
                std::cout << data[(front + i) % capacity] << std::endl; // Printing from the front of the queue -> end
            }
        }
        return;
    }
}
