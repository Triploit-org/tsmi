#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <iostream>
#include "stackelement.hpp"

class Variable
{
private:
    StackElement value;
    std::string name;

public:
    Variable(std::string _name, StackElement _value)
    {
        name = _name;
        value = _value;
    }

    StackElement getValue()
    {
        return value;
    }

    std::string getName()
    {
        return name;
    }

    void setValue(StackElement e)
    {
        value = e;
    }
};

#endif
