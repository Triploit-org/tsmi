#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <iostream>
#include "token.hpp"
#include "runtime.hpp"
#include "variables.hpp"
#include "functions.hpp"

class Executor
{
private:
    bool isloop = false;

    int parse_keyword(std::string kwd, std::vector<Token> tokens, int i)
    {
        if (kwd == "return")
        {
            Runtime._return = true;
            return -13;
        }
        else if (kwd == "break")
        {
            Runtime._break = true;
            return 0;
        }
        else if (kwd == "continue")
        {
            Runtime._continue = true;
            return 0;
        }

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
    int execute(std::vector<Token> tokens, bool loop, bool function)
    {
        for (int i = 0; i < tokens.size(); i++)
        {
            if (Runtime._break)
            {
                return 0;
            }

            if (Runtime._continue)
            {
                Runtime._continue = false;
                return 0;
            }

            if (Runtime._return)
            {
                if (function)
                    Runtime._return = false;
                return 0;
            }

            if (Runtime.debug)
            {
                if (tokens[i].getType() == TT_TO_LEX)
                    std::cout << "INTERPRETING: [" << tokens[i].getValue() << "]" << std::endl;
                else
                    std::cout << "INTERPRETING: " << tokens[i].getValue() << std::endl;
            }

            // if (tokens[i].getType() == TT_LINE_NUMBER)
            //     Runtime.line_number = std::stold(tokens[i].getValue());

            switch(tokens[i].getType())
            {
                case TT_VARIABLE:
                    //Runtime.stack_push(StackElement(tokens[i].getValue(), false, false, true));
                    Runtime.stack_push(Variables.getValue(tokens[i].getValue()));
                    break;
                case TT_WORD:
                    Runtime.stack_push(StackElement(tokens[i].getValue(), true, false, false));

                    if (Runtime.__FUNCTION_KEYWORDS && _exists_function(tokens[i].getValue()))
                        parse_keyword("run", tokens, i);
                    break;
                case TT_INTEGER:
                    Runtime.stack_push(StackElement(std::stold(tokens[i].getValue())));
                    break;
                case TT_STRING:
                    Runtime.stack_push(StackElement(tokens[i].getValue(), false, false, false));
                    break;
                case TT_TO_LEX:
                    Runtime.stack_push(StackElement(tokens[i].getValue(), false, true, false));
                    break;
                default:
                    if (Runtime.debug)
                        std::cout << "INTERPRETING: RUN: " << tokens[i].getValue();

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

            if (Runtime._break)
            {
                return 0;
            }

            if (Runtime._continue)
            {
                Runtime._continue = false;
                return 0;
            }

            if (Runtime._return)
            {
                if (function)
                    Runtime._return = false;
                return 0;
            }
        }
        return 0;
    }
} Executor;

#endif
