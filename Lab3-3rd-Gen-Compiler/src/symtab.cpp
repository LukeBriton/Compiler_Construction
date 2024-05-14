#include "defs.h"
#include "declare.h"
#include <unordered_map>

// 封装方式全部模仿
// Symbol table functions
// Copyright (c) 2019 Warren Toomey, GPL3

// std::unordered_map<std::string, int> IDs;	// local symbol table
// error: no previous extern declaration for non-static variable 'IDs' [-Werror,-Wmissing-variable-declarations]
// https://stackoverflow.com/questions/28511565/no-previous-extern-declaration-for-non-static-variable-frameworknameversionstri
static std::unordered_map<std::string, int> IDs;	// local symbol table

// static int index = 0;		// 统计变量个数，便于栈操作。
// error: redefinition of 'index' as different kind of symbol
// /usr/include/strings.h:68:14: note: previous definition is here
// extern char *index (const char *__s, int __c)
static int Index = 0;		// 统计变量个数，便于栈操作。

// 其实是在 global symtab 之上改的。
// Determine if the symbol is in the local symbol table.
// Return its slot position or -1 if not found.
int findlocal(std::string name) {
    // int i;
    // error: unused variable 'i' [-Werror,-Wunused-variable]
    
    auto it = IDs.find(name);
    if (it != IDs.end())
        return it->second;
    return (-1);
}

int findlocal(const char* name) {
    return findlocal(std::string(name));
}

// Get the position of a new local symbol slot, or die
// if we've run out of positions.
static int newlocal(void) {
    int p = (++Index);
    return (p);
}

// Add a local symbol to the symbol table.
// Return the slot number in the symbol table
int addlocal(std::string name) {
    int y;

    // If this is already in the symbol table, return the existing slot
    if ((y = findlocal(name)) != -1)
        return (y);

    // Otherwise get a new slot, fill it in and
    // return the slot number
    y = newlocal();
    IDs[name] = y;
    return (y);
}

int addlocal(const char* name) {
    //error: cannot bind non-const lvalue reference of type 'std::string&'
    // {aka 'std::__cxx11::basic_string<char>&'} to an rvalue of type 'std::string'
    // {aka 'std::__cxx11::basic_string<char>'}
    return addlocal(std::string(name));
}

// error: no newline at end of file [-Werror,-Wnewline-eof]
// https://stackoverflow.com/questions/5813311/whats-the-significance-of-the-no-newline-at-end-of-file-log
