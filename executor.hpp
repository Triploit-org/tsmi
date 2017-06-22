#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <iostream>
#include "token.hpp"
#include "variables.hpp"

class Executor
{
private:
    int parse_keyword(std::string kwd, std::vector<Token> tokens, int i)
    {
        if (kwd == "return")
            return -13;

        for (int i = 0; i < keyword_names.size(); i++)
            if (keyword_names[i] == kwd)
                keyword_functions[i](tokens, i);
        return 0;
    }

    int parse_operator(std::string op, std::vector<Token> tokens, int i)
    {
        for (int i = 0; i < operator_names.size(); i++)
            if (operator_names[i] == op)
                operator_functions[i](tokens, i);
        return 0;
    }

public:
    int execute(std::vector<Token> tokens)
    {
        for (int i = 0; i < tokens.size(); i++)
        {
            if (Runtime.debug)
            {
                if (tokens[i].getType() == TT_TO_LEX)
                    std::cout << "INTERPRETING: [" << tokens[i].getValue() << "]" << std::endl;
                else
                    std::cout << "INTERPRETING: " << tokens[i].getValue() << std::endl;
            }

            // if (tokens[i].getType() == TT_LINE_NUMBER)
            //     Runtime.line_number = std::stoi(tokens[i].getValue());

            switch(tokens[i].getType())
            {
                case TT_VARIABLE:
                    //Runtime.stack_push(StackElement(tokens[i].getValue(), false, false, true));
                    Runtime.stack_push(Variables.getValue(tokens[i].getValue()));
                    break;
                case TT_WORD:
                    Runtime.stack_push(StackElement(tokens[i].getValue(), true, false, false));
                    break;
                case TT_INTEGER:
                    Runtime.stack_push(StackElement(std::stoi(tokens[i].getValue())));
                    break;
                case TT_STRING:
                    Runtime.stack_push(StackElement(tokens[i].getValue(), false, false, false));
                    break;
                case TT_TO_LEX:
                    Runtime.stack_push(StackElement(tokens[i].getValue(), false, true, false));
                    break;
                default:
                        switch(tokens[i].getType())
                        {
                            case TT_KEYWORD:
                                if (parse_keyword(tokens[i].getValue(), tokens, i) == -13)
                                    return 0;
                                break;
                            case TT_OPERATOR:
                                parse_operator(tokens[i].getValue(), tokens, i);
                                break;
                        }
                    break;
            }
        }
        return 0;
    }
} Executor;

#endif
