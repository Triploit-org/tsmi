#ifndef DEF_NAMES_HPP
#define DEF_NAMES_HPP

#include <iostream>
#include <vector>

int __command_equals(std::vector<Token> tokens, int i);
int __command_not_equals(std::vector<Token> tokens, int i);
int __command_add(std::vector<Token> tokens, int i);
int __command_sub(std::vector<Token> tokens, int i);
int __command_mul(std::vector<Token> tokens, int i);
int __command_div(std::vector<Token> tokens, int i);
int __command_mod(std::vector<Token> tokens, int i);
int __command_less(std::vector<Token> tokens, int i);
int __command_greater(std::vector<Token> tokens, int i);
int __command_less_or_equals(std::vector<Token> tokens, int i);
int __command_greater_or_equals(std::vector<Token> tokens, int i);

std::vector<std::string> defined_names;

std::vector<std::string> operator_names =
{
    "==",
    "!=",
    "+",
    "-",
    "*",
    "/",
    "%",
    "<",
    ">",
    "<=",
    ">="
};

int (*operator_functions[])(std::vector<Token> tokens, int i) =
{
    &__command_equals,
    &__command_not_equals,
    &__command_add,
    &__command_sub,
    &__command_mul,
    &__command_div,
    &__command_mod,
    &__command_less,
    &__command_greater,
    &__command_less_or_equals,
    &__command_greater_or_equals
};


int __command_pop(std::vector<Token> tokens, int i);
int __command_swap(std::vector<Token> tokens, int i);
int __command_dup(std::vector<Token> tokens, int i);
int __command_func(std::vector<Token> tokens, int i);
int __command_rep(std::vector<Token> tokens, int i);
int __command_out(std::vector<Token> tokens, int i);
int __command_outl(std::vector<Token> tokens, int i);
int __command__if(std::vector<Token> tokens, int i);
int __command_run(std::vector<Token> tokens, int i);
int __command_while(std::vector<Token> tokens, int i);
int __command_set(std::vector<Token> tokens, int i);
int __command_inp(std::vector<Token> tokens, int i);
int __command_pick(std::vector<Token> tokens, int i);
int __command_index(std::vector<Token> tokens, int i);
int __command__else(std::vector<Token> tokens, int i);
int __command_size(std::vector<Token> tokens, int i);

std::vector<std::string> keyword_names =
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
    "while",
    "!",
    "inp",
    "pick",
    "index",
    "else",
	"size"
};

int (*keyword_functions[])(std::vector<Token> tokens, int i) =
{
    &__command_pop,
    &__command_swap,
    &__command_dup,
    &__command_func,
    &__command_rep,
    &__command_out,
    &__command_outl,
    &__command__if,
    &__command_run,
    &__command_set,
    &__command_while,
    &__command_run,
    &__command_inp,
    &__command_pick,
    &__command_index,
    &__command__else,
    &__command_size
};

#endif
