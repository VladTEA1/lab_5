#ifndef COMPLEX_TYPE_H
#define COMPLEX_TYPE_H

#include <string>
#include <iostream>

struct ComplexType {
    int identifier;
    std::string title;
    double data_value;
    
    ComplexType(int id_val = 0, const std::string& text = "", double num = 0.0) 
        : identifier(id_val), title(text), data_value(num) {}
    
    bool isEqual(const ComplexType& other) const {
        return identifier == other.identifier && 
               title == other.title && 
               data_value == other.data_value;
    }
    
    void print(std::ostream& output) const {
        output << "ComplexType{id=" << identifier 
               << ", name=\"" << title 
               << "\", value=" << data_value << "}";
    }
};

inline std::ostream& operator<<(std::ostream& output, const ComplexType& obj) {
    obj.print(output);
    return output;
}

inline bool operator==(const ComplexType& first, const ComplexType& second) {
    return first.isEqual(second);
}

#endif
