#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include "lexer.hpp"
#include "executor.hpp"

struct function
{
    std::string name = "";
    std::vector<Token> content;
};

class Functions
{
public:
    std::vector<function> functions;

    void runFunction(std::string name)
    {
        for (function f : functions)
        {
            if (name == f.name)
            {
                Executor.execute(f.content, false, true);
                return;
            }
        }

        std::cout << "error: function " << name << " not defined.";
        exit(1);
    }

    bool existsFunction(std::string name)
    {
        for (function f : functions)
        {
            if (name == f.name)
                return true;
        }

        return false;
    }

    std::vector<Token> getContent(std::string name)
    {
        for (function f : functions)
        {
            if (name == f.name)
            {
                return f.content;
            }
        }
    }

    void addFunction(std::string name, std::vector<Token> content)
    {
        for (function f : functions)
        {
            if (name == f.name)
            {
                std::cout << "error: function " << name << " already defined.";
                exit(1);
            }
        }

        function f;
        f.name = name;
        f.content = content;

        functions.push_back(f);
    }
} Functions;

#endif
