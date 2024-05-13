#include "defs.h"
#include "declare.h"
#include <unordered_map>
#include <string>

// 封装方式全部模仿
// Symbol table functions
// Copyright (c) 2019 Warren Toomey, GPL3

std::unordered_map<std::string, int> IDs;	// local symbol table

static int index = 0;		// 统计变量个数，便于栈操作。

// 其实是在 global symtab 之上改的。
// Determine if the symbol is in the local symbol table.
// Return its slot position or -1 if not found.
int findlocal(std::string name) {
    int i;
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
    int p = (++index);
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