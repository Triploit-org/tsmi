#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include "lexer.hpp"
#include "executor.hpp"

class Funtions
{
private:
    struct function
    {
        std::string name = "";
        std::string content = "";
    };

    std::vector<std::string> names;
    std::vector<std::string> contents;
    std::vector<function> functions;

public:
    void runFunction(std::string name)
    {
        for (function f : functions)
        {
            if (name == f.name)
            {
                Executor.execute(Lexer.lex({f.content}));
                return;
            }
        }

        std::cout << "error: function " << name << " not defined.";
        exit(1);
    }

    std::string getContent(std::string name)
    {
        for (function f : functions)
        {
            if (name == f.name)
            {
                return f.content;
            }
        }
    }

    void addFunction(std::string name, std::string content)
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
