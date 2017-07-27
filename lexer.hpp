#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <vector>
#include "runtime.hpp"
#include "tstring.hpp"
#include "token.hpp"

class Lexer
{
private:
    std::string removeCommentFromLine(std::string line)
    {
        if (tri::string(line).trim().at(0) == ' ')
            return " ";

        std::string s = "";
        std::vector<char> data(line.begin(), line.end());

        for (char c : data)
        {
            if (c != '#')
                s = s + c;
            else return s;
        }

        return s;
    }

    bool is_ignore(char c)
    {
        switch(c)
        {
            case ' ':
                return true;
            case ';':
                return true;
            case ',':
                return true;
            case '\n':
                return true;
            case '\t':
                return true;
        }

        return false;
    }

public:
    std::vector<Token> lex(std::vector<std::string> code)
    {
        std::string ncode = "";
        std::string tmp;
        std::vector<Token> tokens;

        for (std::string line : code)
        {
            ncode += (removeCommentFromLine(line)) + "  \n";
        }

        for (int i = 0; i < ncode.size(); i++)
        {

			if (ncode[i] == '*' && ncode[i+1] == '*')
			{
				if (Runtime.debug) std::cout << "=== COMMANT START ===" << std::endl;

				i+=2;
				while (i < ncode.size() && (ncode[i] != '*' && ncode[i+1] != '*'))
				{
					if (Runtime.debug) std::cout << ncode[i];
					i++;
				}
				if (Runtime.debug) std::cout << "=== COMMANT END ====" << std::endl;
				i+=2;
				continue;
			}

            if (is_ignore(ncode[i]))
            {
                if (Runtime.debug)
                    std::cout << "LEX: \"" << tmp << "\"" << std::endl;
                if (tmp != "" && !tmp.empty())
                    tokens.push_back(Token(tmp, (new Token("", TT_OPERATOR))->findType(tmp)));
                tmp = "";
                continue;
            }

            // if (ncode[i] == '[')
            //     std::cout << "new scope!" << std::endl;

            if (ncode[i] == '"')
            {
                i++;
                while (ncode[i] != '"')
                {
                    if (ncode[i] == '\\')
                    {
                        switch (ncode[i+1])
                        {
                            case 'n':
                                tmp += "\n";
                                break;
                            case '"':
                                tmp += "\"";
                                break;
                        }

                        i++;
                        i++;
                        continue;
                    }

                    tmp += ncode[i];
                    i++;
                }

                if (Runtime.debug)
                    std::cout << "LEX: \"" << tmp << "\"" << std::endl;
                tokens.push_back(Token(tmp, TT_STRING));
                tmp = "";
                continue;
            }

            if (ncode[i] == '[')
            {
                i++;
                for (int bc = 2; bc > 1;)
                {
                    if (ncode[i] == '[')
                        bc++;
                    else if (ncode[i] == ']')
                    {
                        bc--;
                    }

                    if (ncode[i] == ' ')
                        while (ncode[i+1] == ' ' && (i+1) < ncode.size()) { i++; };

                    tmp += ncode[i];
                    i++;
                }

                if (Runtime.debug)
                    std::cout << "LEX: \"" << tmp << "\"" << std::endl;
                tokens.push_back(Token(tmp.substr(0, tmp.size()-1), TT_TO_LEX));
                tmp = "";
            }

            if (ncode[i] == '!')
            {
                if (i+1 < ncode.size())
                {
                    if (ncode[i+1] == '=')
                    {
                        tmp += ncode[i];
                        continue;
                    }
                }

                if (tmp != "" && !tmp.empty())
                    tokens.push_back(Token(tmp, (new Token("", TT_OPERATOR))->findType(tmp)));

                if (Runtime.debug)
                    std::cout << "LEX: \"" << tmp << "\"" << std::endl;

                if (Runtime.debug)
                    std::cout << "LEX: \"!\"" << std::endl;

                tokens.push_back(Token(std::string(1, ncode[i]), TT_KEYWORD));
                tmp = "";
                continue;
            }

            if (ncode[i] != ' ')
                tmp += ncode[i];
        }

        // for (Token t : tokens)
        //     std::cout << ">>>>" << t.getValue() << "<<<<" << std::endl << std::endl;

        return tokens;
    }
} Lexer;

#endif
