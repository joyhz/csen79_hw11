/*
 * Names: Yuto Fraley, Theodore Griffin - Jones, Michael Tiburcio, Joy Zhu
 * Emails: yfraley@scu.edu, tgriffinjones@scu.edu, mtiburcio@scu.edu, jhzhu@scu.edu
 * recipe for containers using pointers
 */
#ifndef BAG_H
#define BAG_H

#include <cstddef>

namespace csen79 {

class Bag {
public:
    using Data = int;   // create an alias for the data
    Bag(): data(nullptr), capacity(10), count(0), front(0), rear(0) {};

    // rule of 5
    ~Bag();
    Bag(const Bag &);
    Bag(Bag &&);
    Bag &operator=(const Bag &);
    Bag &operator=(Bag &&rhs);

    // queue functions
    void enQ(const Data &);
    Data deQ();
    void print() const;


    const Data &getData(const int) const;
    void setData(const int, const Data &);
    bool isEmpty() const;
    bool isFull() const;
    std::size_t size() const;
    void expandCapacity(); //double size if we need to
    void setFaultInject() { inject_new_fail = true; };
    void clearFaultInject() { inject_new_fail = false; };

    Data* data;
    std::size_t capacity;   
    std::size_t count;     
    std::size_t front; // Keeps track of first element of the queue
    std::size_t rear; // Keeps track of last element of the queue

private:
    bool inject_new_fail;
    void throwNewFailure();
};

}
#endif // BAG_H
