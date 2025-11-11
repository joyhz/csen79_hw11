/*
 * Names: Abraham Bhatti, David Lopez-Ryan, Sebastian Ortiz Ayala, Joy Zhu
 * Emails: abhatti@scu.edu, rlopezryan@scu.edu, sortizayala@scu.edu, jhzhu@scu.edu
 * recipe for containers using pointers
 */
#ifndef BAG_H
#define BAG_H

#include <cstddef>

namespace csen79 {

template <typename T>
class Bag {
public:
    Bag(): data(nullptr), capacity(10), count(0), front(0), rear(0) {};

    // Rule of 5
    ~Bag();
    Bag(const Bag &);
    Bag(Bag &&);
    Bag &operator=(const Bag &);
    Bag &operator=(Bag &&rhs);

    // Queue functions
    void enQ(const T &);
    T deQ();
    void print() const;


    const T &getData(const int) const;
    void setData(const int, const T &);
    bool isEmpty() const;
    bool isFull() const;
    std::size_t size() const;
    void expandCapacity();     // Double capacity if needed

    // Fault injection
    void setFaultInject() { inject_new_fail = true; };
    void clearFaultInject() { inject_new_fail = false; };

private:
    T* data;
    std::size_t capacity;   
    std::size_t count;     
    std::size_t front; // Keeps track of first element of the queue
    std::size_t rear; // Keeps track of last element of the queue
    bool inject_new_fail;
    void throwNewFailure();
};

}    // namespace csen79

#include "bag.impl"    // Including the bag template implementation file
#endif // BAG_H
