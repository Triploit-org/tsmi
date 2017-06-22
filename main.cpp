#include <iostream>
#include <vector>
#include "runtime.hpp"
#include "token.hpp"
#include "defnames.hpp"
#include "keywords.hpp"
#include "operators.hpp"
#include "executor.hpp"
#include "lexer.hpp"
#include "variable.hpp"
#include "variables.hpp"
#include "functions.hpp"

int input();

int main(int argc, char const *argv[])
{
    int i = 1;

    if (argc < 2)
        input();
    else
        Runtime.FILE_NAME = argv[1];

    if (argc > 2)
    {
        if (std::string(argv[argc-1]) == ".debug")
            i = 2;

        for (int c = argc-i; c >= 1; c--)
        {
            Runtime.stack_push(StackElement(argv[c]));
        }

        if (i == 2)
            Runtime.debug = true;
    }

    Runtime.stack_push(StackElement(argc-(1+i)));
    return Executor.execute(Lexer.lex(Runtime.readFile(Runtime.FILE_NAME)));
}

int input()
{
    std::string _input = "";
    while (_input != ".quit")
    {
        std::cout << "> ";
        std::getline(std::cin, _input);

        if (_input[0] == '.')
        {
            switch(_input[1])
            {
                case 's':
                    for (StackElement s : Runtime.stack[Runtime.stack_index])
                        std::cout << s.getStr() << std::endl;
                break;
            }
        }
        else
        {
            Executor.execute(Lexer.lex({_input}));
        }
    }
}
