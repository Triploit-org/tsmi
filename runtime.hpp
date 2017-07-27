#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include "stackelement.hpp"
#include "tstring.hpp"

class Runtime
{
public:
    std::vector<std::vector<StackElement>> stack;
    int stack_index = 0;
    bool debug = false;
    int line_number = 1;

	std::ifstream t;
    std::vector<std::string> v;
	std::vector<std::string> prae;

    bool _continue = false;
    bool _break = false;
    bool _return = false;

    std::string FILE_NAME;
    std::string FILE_CONTENT;

    void stack_add_stack()
    {
        stack.push_back(std::vector<StackElement>());
    }

    void set_stack_index(int index)
    {
        while (index >= (stack.size()))
            stack_add_stack();

        if (index < 0)
            index = 0;

        stack_index = index;
    }

	std::vector<std::string> readFile(std::string fname)
    {
		if (debug)
			std::cout << "read file: " << fname << std::endl;

        t = std::ifstream(fname);

		if (!t.is_open())
		{
			std::cout << "error: cant open file " << fname << std::endl;
			exit(1);
		}

        FILE_CONTENT = std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        std::string line;
		tri::string tline;

        t.close();
        t.open(fname);

        while (std::getline(t, line))
        {
			tline = tri::string(line).trim();

			if (tline.startsWith("#"))
			{
				tri::string command = tline.cxs().substr(1, tline.length()-1);
				tri::string arg = command.split(' ')[0].trim();

				if (debug)
					std::cout << "prae: command: " << command.cxs() << std::endl;

				if (arg.cxs() == "need")
				{
					std::string file = tri::string(command.cxs().substr(4, command.length()-1)).trim().toLower().cxs();
					bool found = false;

					if (debug)
						std::cout << "prae: command: need: file: " << file << std::endl;

					for (std::string f : prae)
					{
						if (f == file)
							found = true;
					}

					if (!found)
					{
						prae.push_back(file);
						std::vector<std::string> ls = readFile2(file);

						tline = "";
						arg = "";
					}

				}
			}
			else
            	v.push_back(line);
        }

        return v;
    }

	std::vector<std::string> readFile2(std::string fname)
	{
		std::ifstream t(fname);

		if (debug)
			std::cout << "read file: " << fname << std::endl;

		t = std::ifstream(fname);

		if (!t.is_open())
		{
			std::cout << "error: cant open file " << fname << std::endl;
			exit(1);
		}

		FILE_CONTENT = std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		std::string line;
		tri::string tline;

		t.close();
		t.open(fname);

		while (std::getline(t, line))
		{
			tline = tri::string(line).trim();

			if (tline.startsWith("#"))
			{
				tri::string command = tline.cxs().substr(1, tline.length()-1);
				tri::string arg = command.split(' ')[0].trim();

				if (debug)
					std::cout << "prae: command: " << command.cxs() << std::endl;

				if (arg.cxs() == "need")
				{
					std::string file = tri::string(command.cxs().substr(4, command.length()-1)).trim().toLower().cxs();
					bool found = false;

					if (debug)
						std::cout << "prae: command: need: file: " << file << std::endl;

					for (std::string f : prae)
					{
						if (f == file)
							found = true;
					}

					if (!found)
					{
						if (debug) std::cout << std::endl;
						prae.push_back(file);
						std::vector<std::string> ls = readFile(file);

						for (std::string s : ls)
						{
							if (debug)
								std::cout << "INC] " << s << std::endl;
							v.push_back(s);
						}
						if (debug) std::cout << std::endl;

						tline = "";
						arg = "";
					}

				}
			}
			else
				v.push_back(line);
		}

		return v;
	}

    bool is_number(const std::string s)
    {
        char* endptr = 0;
        strtod(s.c_str(), &endptr);

        if(*endptr != '\0' || std::string(endptr) == s)
            return false;
        return true;
    }

    void stack_push(StackElement e)
    {
        stack[stack_index].push_back(e);
    }

    void stack_pop()
    {
        stack[stack_index].pop_back();
    }

    StackElement stack_peek()
    {
        if (debug)
            std::cout << "(PEEK-STACK) STACK_SIZE=" << stack[stack_index].size() << std::endl;

        if (stack[stack_index].size() == 0)
        {
            std::cout << "error: runtime: stack: stack is empty!" << std::endl;
            exit(1);
        }

        StackElement el = stack[stack_index][stack[stack_index].size()-1];
        stack_pop();
        return el;
    }

    StackElement stack_peek_at(int index)
    {
        if (debug)
            std::cout << "(PEEK-AT-INDEX-STACK) INDEX=" << index << " STACK_SIZE=" << stack[stack_index].size() << std::endl;


        if (stack[stack_index].size() == 0)
        {
            std::cout << "error: runtime: stack: stack is empty!" << std::endl;
            exit(1);
        }
        else if (index < 0 || index >= stack[stack_index].size())
        {
            std::cout << "error: runtime: stack: index out of range!" << std::endl;
            exit(1);
        }

        StackElement el = stack[stack_index][index];
        stack_pop();
        return el;
    }

    Runtime()
    {
        stack_add_stack();
    }
} Runtime;

#endif
