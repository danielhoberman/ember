#include "myclass.h"

MyClass::MyClass(std::string name, int value)
    : name(name), value(value) {}

std::string MyClass::greet() const {
    return "Hello, " + name + "! Value = " + std::to_string(value);
}

void MyClass::set_value(int v){
    value = v;
}

int MyClass::get_value() const {
    return value;
}