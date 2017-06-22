#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include <iostream>
#include <vector>
#include "variable.hpp"

class Variables
{
    std::vector<Variable> variables;

public:
    bool existsVariable(std::string name)
    {
        for (Variable v : variables)
        {
            if (v.getName() == name)
                return true;
        }

        return false;
    }

    Variable* getVariable(std::string name)
    {
        for (int i = 0; i < variables.size(); i++)
        {
            if (variables[i].getName() == name)
                return &variables[i];
        }

        return (new Variable("null", StackElement(0)));
    }

    StackElement getValue(std::string name)
    {
        for (Variable v : variables)
        {
            if (v.getName() == name)
                return v.getValue();
        }

        return (StackElement(0));
    }

    void createVariable(std::string name, StackElement value)
    {
        variables.push_back(Variable(name, value));
    }

    void setVariable(std::string name, StackElement e)
    {
        if (!existsVariable(name))
            createVariable(name, e);
        getVariable(name)->setValue(e);
    }
} Variables;

#endif
