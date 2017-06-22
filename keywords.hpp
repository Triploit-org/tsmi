#ifndef KEYWORDS_HPP
#define KEYWORDS_HPP

#include <iostream>
#include <iomanip>
#include "functions.hpp"

int __command_pop(std::vector<Token> tokens, int i)
{
    Runtime.stack_pop();
}

int __command_while(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.isCode() && e2.isCode())
    {
        while (true)
        {
            Executor.execute(Lexer.lex({e2.getStr()}), false, false);
            StackElement e = Runtime.stack_peek();

            if (!e.isInt())
            {
                std::cout << "error: while: \"" << e.getStr() << "\" must be an integer (0 or 1/false or true)!" << std::endl;
            }

            if (e.getInt() == 1)
                Executor.execute(Lexer.lex({e1.getStr()}), true, false);
            else
                break;


            if (Runtime._break)
            {
                Runtime._break = false;
                return 0;
            }
        }
    }
    else
    {
        if (!e1.isCode())
            std::cout << "error: while: can't run \"" << e1.getStr() << "\": is no code-scope!" << std::endl;
        else
            std::cout << "error: while: can't run \"" << e2.getStr() << "\": is no code-scope!" << std::endl;
        exit(1);
    }

}

int __command_swap(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    Runtime.stack_push(e1);
    Runtime.stack_push(e2);
}

int __command_dup(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    Runtime.stack_push(e1);
    Runtime.stack_push(e1);
}

int __command_func(std::vector<Token> tokens, int i)
{
    StackElement name = Runtime.stack_peek();
    StackElement content = Runtime.stack_peek();

    if (name.isWord() && content.isCode())
    {
        Functions.addFunction(name.getStr(), content.getStr());
        // std::cout << "\nFunction \"" << name.getStr() << "\" created!" << std::endl;
    }
    else
    {
        if (!name.isWord())
            std::cout << "error: func: wrong syntax: \"" << name.getStr() << "\" must be a word!" << std::endl;
        else
            std::cout << "error: func: wrong syntax: \"" << content.getStr() << "\" must be a code-scope!" << std::endl;

        exit (1);
    }
}

int __command_rep(std::vector<Token> tokens, int i)
{
    StackElement content = Runtime.stack_peek();
    StackElement repeat = Runtime.stack_peek();

    if (!content.isCode())
    {
        std::cout << "error: rep: can't run content " << content.getStr() << ": is no code-scope!" << std::endl;
        exit(1);
    }
    else if (!repeat.isInt())
    {
        std::cout << "error: rep: can't repeat " << repeat.getStr() << " times: is no integer!" << std::endl;
        exit(1);
    }
    else
    {
        for (int i = 0; i < repeat.getInt(); i++)
        {
            Executor.execute(Lexer.lex({content.getStr()}), true, false);
        }
    }
}

int __command_out(std::vector<Token> tokens, int i)
{
    // std::cout.precision(10);
    // std::cout.setf(std::ios::fixed);

    StackElement se = Runtime.stack_peek();


    if (!Runtime.debug)
    {
        if (se.isInt())
        {
            long long i2 = se.getInt();
            long double i = se.getInt();
            // std::cout << "?=" << i2 << "/" << se.getInt() << std::endl;

            if (se.isInt() < 0)
            {
                i *= -1;
            }

            if ((i - i2) < 0.000001)
            {
                std::cout.unsetf(std::ios::fixed);
                std::cout << std::noshowpoint << i;
            }
            else
            {
                std::cout << std::fixed << i;
                std::cout.unsetf(std::ios::fixed);
            }
        }
        else
            std::cout << se.getStr();
    }

    if (Runtime.debug)
    {
        std::cout << "\nOUT   >> \"";
        std::cout << "\"" << std::endl << std::endl;
    }
}

int __command_outl(std::vector<Token> tokens, int i)
{
    std::cout.unsetf(std::ios::scientific);
    std::cout.unsetf(std::ios::floatfield);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(5);

    StackElement se = Runtime.stack_peek();
    //std::cout << se.getTypeStr() << std::endl;

    if (Runtime.debug)
    {
        std::cout << "\nOUTL  >> \"";
        std::cout << se.getStr() << "\"\n" << std::endl;
    }

    if (!Runtime.debug)
    {
        if (se.isInt())
        {
            long long i2 = se.getInt();
            long double i = se.getInt();
            // std::cout << "?=" << i2 << "/" << se.getInt() << std::endl;

            if (se.isInt() < 0)
            {
                i *= -1;
            }

            if ((i - i2) < 0.000001)
            {
                std::cout.unsetf(std::ios::fixed);
                std::cout << std::noshowpoint << i << std::endl;
            }
            else
            {
                std::cout << std::fixed << i << std::endl;
                std::cout.unsetf(std::ios::fixed);
            }
        }
        else
            std::cout << se.getStr() << std::endl;
    }

}

int __command__if(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.isCode() && e2.isInt())
    {
        if (e2.getInt() == 1)
            Executor.execute(Lexer.lex({e1.getStr()}), false, false);
    }
    else
    {
        if (!e1.isCode())
            std::cout << "error: if: can't run \"" << e1.getStr() << "\": is no code-scope!" << std::endl;
        else
            std::cout << "error: if: \"" << e2.getStr() << "\" must be a number (0 or 1/false or true)!" << std::endl;
        exit(1);
    }
}

int __command__else(std::vector<Token> tokens, int i)
{
    StackElement e1 = Runtime.stack_peek();
    StackElement e2 = Runtime.stack_peek();

    if (e1.isCode() && e2.isInt())
    {
        if (e2.getInt() == 0)
            Executor.execute(Lexer.lex({e1.getStr()}), false, false);
    }
    else
    {
        if (!e1.isCode())
            std::cout << "error: else: can't run \"" << e1.getStr() << "\": is no code-scope!" << std::endl;
        else
            std::cout << "error: else: \"" << e2.getStr() << "\" must be a number (0 or 1/false or true)!" << std::endl;
        exit(1);
    }
}

int __command_run(std::vector<Token> tokens, int i)
{
    StackElement se = Runtime.stack_peek();

    if (se.isWord())
        Functions.runFunction(se.getStr());
    else if (se.isCode())
        Executor.execute(Lexer.lex({se.getStr()}), false, false);
    else
    {
        std::cout << "error: run: can't run \"" << se.getStr() << "\": it's not a word and not a code-scope" << std::endl;
        exit(1);
    }

    // if (se.isWord())
    //     std::cout << Functions.getContent(se.getStr()) << std::endl << std::endl;
}

int __command_set(std::vector<Token> tokens, int i)
{
    StackElement se = Runtime.stack_peek();
    StackElement val = Runtime.stack_peek();

    if (se.isWord())
    {
        Variables.setVariable(std::string("$"+se.getStr()), val);
    }
    else
    {
        std::cout << "error: set: \"" << se.getStr() << "\" must be a word" << std::endl;
    }
}

int __command_inp(std::vector<Token> tokens, int i)
{
    std::string s;
    std::getline(std::cin, s);

    if (Runtime.is_number(s))
        Runtime.stack_push(StackElement(std::stoi(s)));
    else
        Runtime.stack_push(StackElement(s));
}

int __command_pick(std::vector<Token> tokens, int i)
{
    StackElement se = Runtime.stack_peek();

    if (se.isInt())
        Runtime.stack_push(Runtime.stack_peek_at(se.getInt()));
    else
    {
        std::cout << "error: pick: integer expected, found " << se.getTypeStr() << std::endl;
        exit(1);
    }
}

int __command_index(std::vector<Token> tokens, int i)
{
    StackElement se = Runtime.stack_peek();

    if (Runtime.debug)
        std::cout << "INDEX: current stack = stack " << se.getStr() << std::endl;

    if (se.isInt())
        Runtime.set_stack_index(se.getInt());
    else
    {
        std::cout << "error: index: integer expected, found " << se.getTypeStr() << std::endl;
        exit(1);
    }
}
#endif
