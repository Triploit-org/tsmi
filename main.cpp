#include <iostream>
#include <vector>
#include <unistd.h>

bool _exists_function(std::string name);

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
    // std::cout.precision(10);
    // std::cout.setf(std::ios::fixed);

    if (argc < 2)
        input();
    else
        Runtime.FILE_NAME = argv[1];

	std::vector<tri::string> pth = tri::string(Runtime.FILE_NAME).trim().split('/');
	std::string path;

	if (pth.size() > 1)
	{
		for (int i = 0; i < pth.size()-1; i++) path += pth[i].cxs();
		Runtime.FILE_NAME = pth[pth.size()-1].cxs();
		chdir(path.c_str());
	}

    if (argc > 2)
    {
        if (std::string(argv[argc-1]) == ".debug")
            i = 2;
        // else if (std::string(argv[argc-1]).substr(0, 7) == ".compile")
        //     i = 3;

        for (int c = argc-i; c >= 1; c--)
        {
            Runtime.stack_push(StackElement(argv[c], false, false, false));
        }

        if (i == 2)
            Runtime.debug = true;
        // else if (i == 3)
        // {
        //     Runtime.compile = true;
        //     Runtime.binary_file = std::string(argv[argc-1]).substr(7, std::string(argv[argc-1]).size()-1);
        // }
    }

    Runtime.stack_push(StackElement(argc-(1+i)));
    return Executor.execute(Lexer.lex(Runtime.readFile(Runtime.FILE_NAME)), false, false);
}

int input()
{
	std::cout << "TSMI-Shell. Type \"help\" for help." << std::endl;
    std::string _input = "";

    while (_input != ".quit" || _input != ".q")
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
		else if (_input == "help")
		{

		}
        else
        {
            Executor.execute(Lexer.lex({_input}), false, false);
        }
    }

	return 0;
}

bool _exists_function(std::string name)
{
    for (function f : Functions.functions)
    {
        if (name == f.name)
            return true;
    }

    return false;
}
