#ifndef COMPLEX_TYPE_H
#define COMPLEX_TYPE_H

#include <string>
#include <iostream>

struct ComplexType {
    int id;
    std::string name;
    double value;
    
    ComplexType(int i = 0, const std::string& n = "", double v = 0.0) 
        : id(i), name(n), value(v) {}
    
    bool operator==(const ComplexType& other) const {
        return id == other.id && name == other.name && value == other.value;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const ComplexType& ct) {
        os << "ComplexType{id=" << ct.id << ", name=\"" << ct.name << "\", value=" << ct.value << "}";
        return os;
    }
};

#endif