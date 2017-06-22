#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include "tstring.hpp"

enum TokenType
{
    TT_INTEGER = 1,
    TT_STRING,
    TT_VARIABLE,
    TT_KEYWORD,
    TT_OPERATOR,
    TT_WORD,
    TT_TO_LEX,
    TT_UNKNOWN,
    TT_LINE_NUMBER
};

std::vector<std::string> keywords =
{
    "pop",
    "swap",
    "dup",
    "func",
    "rep",
    "out",
    "outl",
    "if",
    "run",
    "set",
    "!",
    "return",
    "while",
    "inp",
    "set",
    "pick",
    "index",
    "else",
    "break",
    "continue"
};

std::vector<std::string> operators =
{
    "==",
    "<",
    ">",
    "<=",
    ">=",
    "!=",
    "+",
    "/",
    "*",
    "-",
    "%"
};

class Token
{
private:
    TokenType type;
    std::string value;

public:
    Token(std::string val, TokenType toktyp)
    {
        value = val;
        type = toktyp;
    }

    std::string getValue()
    {
        return value;
    }

    TokenType getType()
    {
        return type;
    }

    TokenType findType(std::string s)
    {
        for (std::string word : keywords)
            if (s == word)
                return TT_KEYWORD;

        for (std::string word : operators)
            if (s == word)
                return TT_OPERATOR;

        if (Runtime.is_number(s))
            return TT_INTEGER;

        if (s[0] == '$' && tri::string(s).trim().length() > 1)
            return TT_VARIABLE;

        if (tri::string(s).trim().startsWith("~<l:") && tri::string(s).trim().endsWith(":>~"))
            return TT_LINE_NUMBER;

        if (tri::string(s).trim().cxs() == "")
            return TT_UNKNOWN;

        return TT_WORD;
    }
};

#endif
