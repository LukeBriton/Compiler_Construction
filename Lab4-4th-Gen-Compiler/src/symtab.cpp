#include "defs.h"
#include "declare.h"
#include <map>

// 封装方式全部模仿
// Symbol table functions
// Copyright (c) 2019 Warren Toomey, GPL3

// std::unordered_map<std::string, int> IDs;	// local symbol table
// error: no previous extern declaration for non-static variable 'IDs' [-Werror,-Wmissing-variable-declarations]
// https://stackoverflow.com/questions/28511565/no-previous-extern-declaration-for-non-static-variable-frameworknameversionstri

// static std::unordered_map<symbol, int> IDs;	// local symbol table
// error: use of deleted function 'std::unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>::unordered_map()
// [with _Key = symbol; _Tp = int; _Hash = std::hash<symbol>; _Pred = std::equal_to<symbol>;
// _Alloc = std::allocator<std::pair<const symbol, int> >]'
// https://stackoverflow.com/questions/51220257/compilation-error-related-to-map-and-unordered-map-attempting-to-reference-a-d
// https://stackoverflow.com/questions/37007307/fast-hash-function-for-stdvector

static std::map<symbol, int> IDs;	// local symbol table
static std::map<symbol, int> FUNCs; // function table

// 是否可以划片分区，IDs 分成几段，记录下每段变量数量，对应各个函数。
// 或者干脆在 symbol 里添加上当前作用域的函数名？
// 目前还没有全局变量，局部变量应该都只在其函数 label 底下（有点类似 scope）起作用。
// 可在生成完一个函数的代码后，清空 IDs，另起炉灶。

// 此外，我将 Parametres 也存放在 IDs 中，只不过将值映射成负的，而且，findlocal 等判断时
// 对于不存在的情况返回值为 -1，而参数在 $fp 中至少（指从左数第一个参数，也就是最后入栈的参数）
// 也是在 $fp + 2*4 的位置，正常情况下对于局部变量使用 -4*id($fp)，参数用 4*(-id)($fp) 就行了。

// 流程模拟：
/* int add(int a, int b) { int c; c = a + b; retur c;} // 反正是将 args 当作局部变量来存的。
 * int main() {int m; int n; int p; m = 2; n = 9; p = add(m, n); return p; }
 * 首先处理 add 函数，在此，我们并不知道 $fp, $sp 的实际位置，应该是只有在编译后，在该函数被调用时，
 * 才算确定下来。
 * https://stackoverflow.com/questions/15100476/mips-relevant-use-for-a-stack-pointer-sp-and-the-stack
 * extern void foo();
 * extern int bar();
 * int baz()
 * {
        int x = bar();
        foo();
        return x;
 * }
 * addiu $sp, $sp, -8  # allocate 2 words on the stack
 * sw $ra, 4($sp)      # save $ra in the upper one
 * jal bar             # this overwrites $ra
 * sw $v0, ($sp)       # save returned value (x)
 * jal fool
 * lw $v0, ($sp)       # reload x so we can return it
 * lw $ra, 4($sp)      # reload $ra so we can return to caller
 * addiu $sp, $sp, 8   # restore $sp, freeing the allocated space
 * jr $ra              # return
 */

// 不知道 $fp, $sp 需不需要手动管理。
// 至少得存储 $ra
// 栈帧指针
// https://stackoverflow.com/questions/24436511/whats-the-initial-position-of-the-frame-pointer
// https://stackoverflow.com/questions/36530139/mips-how-does-mips-use-frame-pointer-fp-on-the-stack
// https://stackoverflow.com/questions/46797915/what-are-the-advantages-of-a-frame-pointer
// https://stackoverflow.com/questions/1967482/if-the-program-counter-points-to-the-address-of-the-next-instruction-to-be-execu?rq=3
// https://stackoverflow.com/questions/50774792/does-register-30-fp-have-anything-to-do-with-the-jal-function-in-mips
// 存储
// https://stackoverflow.com/questions/9268586/what-are-callee-and-caller-saved-registers
// https://stackoverflow.com/questions/32733272/mips-program-jr-ra-instructions-and-stack-handling
// https://stackoverflow.com/questions/75708919/knowing-when-to-store-what-in-sp

// static int index = 0;		// 统计变量个数，便于栈操作。
// error: redefinition of 'index' as different kind of symbol
// /usr/include/strings.h:68:14: note: previous definition is here
// extern char *index (const char *__s, int __c)
static int Index = 0;		// 统计变量个数，便于栈操作。
static int Index_func = 0;  // 统计函数个数

// 其实是在 global symtab 之上改的。
// Determine if the symbol is in the local symbol table.
// Return its slot position or -1 if not found.
int findlocal(std::string name) {
    // int i;
    // error: unused variable 'i' [-Werror,-Wunused-variable]
    for (auto const& id : IDs)
        if(id.first.name == name)
            return id.second;
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
int addlocal(std::string name, int type, int stype) {
    int y;

    // If this is already in the symbol table, return the existing slot
    if ((y = findlocal(name)) != -1)
        return (y);

    // Otherwise get a new slot, fill it in and
    // return the slot number
    y = newlocal();
    IDs[symbol(name, type, stype)] = y;
    return (y);
}

int addlocal(const char* name) {
    //error: cannot bind non-const lvalue reference of type 'std::string&'
    // {aka 'std::__cxx11::basic_string<char>&'} to an rvalue of type 'std::string'
    // {aka 'std::__cxx11::basic_string<char>'}
    return addlocal(std::string(name), P_INT, S_VAR);
}

int addpara(std::string name, int para_num, int type, int stype) {
    int y;

    // If this is already in the symbol table, return the existing slot
    if ((y = findlocal(name)) != -1)
        return (y);

    // Otherwise get a new slot, fill it in and
    // return the slot number
    // e.g. 最左的 parametre，其应该是存放在 $fp + 2 * word 的地址处
    y = -(para_num + 1); 
    IDs[symbol(name, type, stype)] = y;
    return (y);
}

int addpara(const char* name, int para_num) {
    //error: cannot bind non-const lvalue reference of type 'std::string&'
    // {aka 'std::__cxx11::basic_string<char>&'} to an rvalue of type 'std::string'
    // {aka 'std::__cxx11::basic_string<char>'}
    return addpara(std::string(name), para_num, P_INT, S_VAR);
}

void clearlocal()
{
    IDs.clear();
    Index = 0;
}

int findfunc(std::string name)
{
    for (auto const& func : FUNCs)
        if(func.first.name == name)
            return func.second;
    return (-1);
}

int findfunc(const char* name)
{
    return findfunc(std::string(name));
}

// 以防 exp 出现 void 类型等。
int functype(int value)
{
    if(value <= 0)
        return -1;
    else
    {
        for (auto const& func : FUNCs)
            if(func.second == value)
                return func.first.type;
        return (-1);
    }
}

std::string funcname(int value)
{
    if(value <= 0)
        return std::string("");
    else
    {
        for (auto const& func : FUNCs)
            if(func.second == value)
                return func.first.name;
        return std::string("");
    }
}

// Get the position of a new function slot
static int newfunc(void) {
    int p = (++Index_func);
    return (p);
}

int addfunc(std::string name, int type, int stype)
{
    int y;

    // If this is already in the symbol table, return the existing slot
    if ((y = findlocal(name)) != -1)
        return (y);

    // Otherwise get a new slot, fill it in and
    // return the slot number
    y = newfunc();
    FUNCs[symbol(name, type, stype)] = y;
    return (y);
}

int addfunc(const char* name, int type)
{
    return addfunc(std::string(name), type, S_FUNC);
}

// error: no newline at end of file [-Werror,-Wnewline-eof]
// https://stackoverflow.com/questions/5813311/whats-the-significance-of-the-no-newline-at-end-of-file-log
