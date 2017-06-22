#ifndef STACK_ELEMENT_HPP
#define STACK_ELEMENT_HPP

class StackElement
{
private:
    std::string value = "";
    bool isint = false;
    bool isword = false;
    bool iscode = false;
    bool isvariable = false;

    bool is_number(const std::string& s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

public:
    int getInt()
    {
        if (is_number(value))
            return std::stoi(value);
        else
            return -1;
    }

    std::string getTypeStr()
    {
        if (isint)
            return "INT";
        else if (isword)
            return "WORD";
        else if (iscode)
            return "CODE";
        else
            return "STRING";
    }

    std::string getStr()
    {
        return value;
    }

    bool isWord()
    {
        return isword;
    }

    bool isInt()
    {
        return isint;
    }

    bool isCode()
    {
        return iscode;
    }

    bool isVar()
    {
        return isvariable;
    }

    bool isString()
    {
        if (!isint && !isword && !iscode && !isvariable)
            return true;
        return false;
    }

    StackElement(std::string val, bool word = false, bool code = false, bool variable = true)
    {
        value = val;
        isint = false;
        isword = word;
        iscode = code;
        isvariable = variable;
    }

    StackElement(int val)
    {
        value = std::to_string(val);
        isint = true;
        isword = false;
    }

    StackElement() {}
};

#endif
