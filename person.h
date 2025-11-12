/*
 * Sin-Yaw Wang <swang24@scu.edu>
 */
#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <iostream>

namespace csen79 {
class Person {
    public:
        using ID = unsigned int;
        enum Gender : char {Male = 'M', Female = 'F', Other = 'O'};
        Person(): id{0}, gender(Other), weight(0.0), height(0.0) {}
        Person(ID id, char g, const std::string& fn, const std::string& ln, double w, double h)
            : id(id), fname(fn), lname(ln), gender(static_cast<Gender>(g)), weight(w), height(h) {}
        Person(const Person &);
        const ID getId() const { return id; }
        const Gender getGender() const { return gender; }
        const std::string getFName() const { return fname; }
        const std::string getLName() const { return lname; }
        const double getWeight() const { return weight; }
        const double getHeight() const { return height; }
        const bool operator<(const Person &rh) const;
        const bool operator==(const Person &rh) const;
        const bool operator>(const Person &rh) const;

    private:
        ID id;
        std::string fname;
        std::string lname;
        Gender gender;
        double weight;
        double height;
    friend std::ostream & operator<<(std::ostream &, const Person &);
    friend std::istream & operator>>(std::istream &, Person &);
};
}
#endif // PERSON_H
