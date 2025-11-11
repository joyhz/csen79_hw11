/*
 * Sin-Yaw Wang <swang24@scu.edu>
 * Template version of Bag container using C-style array
 */
#ifndef BAG_H
#define BAG_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>

namespace csen79 {

template <typename T>
class Bag {
    static constexpr size_t DATASIZE = 1000;    // array size
public:
    using Data = T;   // create an alias for the data type
    
    Bag(): used(0) {
        // Initialize array to default values
        for (size_t i = 0; i < DATASIZE; ++i) {
            data[i] = T();
        }
    }

    // rule of 5
    ~Bag() = default;
    
    // copy constructor
    Bag(const Bag &rhs) : used(rhs.used) {
        std::cout << "copy; calling assignment" << std::endl;
        for (size_t i = 0; i < DATASIZE; ++i) {
            data[i] = rhs.data[i];
        }
    }
    
    // move constructor
    Bag(Bag &&rhs) : used(rhs.used) {
        std::cout << "move constructor; calling assignment" << std::endl;
        for (size_t i = 0; i < DATASIZE; ++i) {
            data[i] = std::move(rhs.data[i]);
        }
        rhs.used = 0;
    }
    
    // copy assignment
    Bag &operator=(const Bag &rhs) {
        std::cout << "assign" << std::endl;
        if (this != &rhs) {
            used = rhs.used;
            for (size_t i = 0; i < DATASIZE; ++i) {
                data[i] = rhs.data[i];
            }
        }
        return *this;
    }
    
    // move assignment
    Bag &operator=(Bag &&rhs) {
        std::cout << "move; calling assign" << std::endl;
        if (this != &rhs) {
            used = rhs.used;
            for (size_t i = 0; i < DATASIZE; ++i) {
                data[i] = std::move(rhs.data[i]);
            }
            rhs.used = 0;
        }
        return *this;
    }

    // access functions
    const Data &getData(const int i) const {
        if (i < 0 || i >= static_cast<int>(used))
            throw std::out_of_range(std::string("index out of range"));
        return data[i];
    }
    
    void setData(const int i, const Data &d) {
        if (i < 0 || i >= static_cast<int>(DATASIZE))
            throw std::out_of_range(std::string("index out of range"));
        data[i] = d;
        if (i >= static_cast<int>(used))
            used = i + 1;
    }
    
    void push(const Data &d) {
        if (used >= DATASIZE)
            throw std::out_of_range(std::string("Bag is full"));
        data[used++] = d;
    }
    
    Data pop() {
        if (used == 0)
            throw std::out_of_range(std::string("Bag is empty"));
        return data[--used];
    }
    
    void print() const {
        std::cout << "Bag contents (" << used << " items):" << std::endl;
        for (size_t i = 0; i < used; ++i) {
            std::cout << "  [" << i << "]: " << data[i] << std::endl;
        }
    }
    
    size_t size() const { return used; }
    bool empty() const { return used == 0; }

private:
    // data storage
    Data data[DATASIZE];
    size_t used;  // number of elements currently in use
};

}
#endif // BAG_H
