#pragma once
#include <string>

class MyClass {
    public:
        MyClass(std::string name, int value);

        std::string greet() const;
        void set_value(int v);
        int get_value() const;
    
    private:
        std::string name;
        int value;
};