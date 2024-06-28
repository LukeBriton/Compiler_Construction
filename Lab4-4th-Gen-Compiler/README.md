# Lab3 -> Lab4 改造方案大纲

(TODO: Many links to be added for reference.)

## Refactoring:

We once used `std::unordered_map<string, int>` to store local symbols (actually only `string`s) in Lab2 refactored version. In Lab3, `symbol` wasn't just a `string` any more. And because `map` just requires `<` to be overloaded, while `unordered_map` requires a custom hash function, which I didn't bother to learn about, we changed to `std::map<symbol, int>` for both local symbol table (which is limited to a single function) and function table.

Then it left us with some problems:

### 1. ~~Variables and Functions of the same name~~

(For some reason, in English they don't use homonymous to describe this in programming?)

Not a problem for the moment, since currently we have functions as global

[Can local variables and functions have the same names in C? - Stack Overflow](https://stackoverflow.com/questions/21325761/can-local-variables-and-functions-have-the-same-names-in-c)

```c
void a (void)
{
    // whatever
}

int main(void)
{
    int a;
    a++; // no problem, boss
    a(); // <-- compiler tantrum: variable used as a function
    // ::a(); // I think this is workable, but in C++
    // whatever
}
```

[scope - C Local variable has same name as function - how does it work? - Stack Overflow](https://stackoverflow.com/questions/16216768/c-local-variable-has-same-name-as-function-how-does-it-work)

You are correct in assuming that the function is global and the variable is local. That is the reason why there is no conflict in your program.

```c
#include<stdio.h>
int x=10;
void x()
{
    printf("\n%d",x);
}

int main()
{
    x(); // You will get an error because in this program both the function x() and variable x are global.
    return 0; 
}
```

[Can't we use same name for a variable and function in C programming - Stack Overflow](https://stackoverflow.com/questions/77267407/cant-we-use-same-name-for-a-variable-and-function-in-c-programming)

Namespaces and scopes are independent concepts, but namespaces often mitigate the problem since they're no longer the same name. C has nothing analogous to namespaces.

By the way, [stackoverflow.com/a/45408848/3150802](https://stackoverflow.com/a/45408848/3150802) mentions the different identifier categories in C. *Between* those categories there are no clashes, *within* them there are. Most notably, struct names and members do not clash with variables or functions.

Anyway, the following program may be amusing:

```c
struct i { int i; };
int i;
int main()
{
i:
    if( (struct i){i}.i)
        goto i;
    return i;
}
```

C has four different "name spaces" for identifiers:

[**C11 6.2.3 Name spaces of identifiers (N1570 Draft)**](http://port70.net/~nsz/c/c11/n1570.html#6.2.3)

> If more than one declaration of a particular identifier is visible at any point in a translation unit, the syntactic context disambiguates uses that refer to different entities. Thus, there are separate name spaces for various categories of identifiers, as follows:
> 
> - Label names (distinguished by the `goto` keyword and the colon `:`);
> - Tag names for struct/enum/union types (distinguished by the `struct`, `enum`, and `union` keywords);
> - Struct and union member names (distinguished by appearing in a struct or union definition and the `.` or `->` member selection operators in an expression; each struct or union type 
>   acts as a different namespace so you can use the same member names in 
>   different struct or union definitions);
> - All other names (variable names, function names, typedef names, enumeration constants, etc.);

[c++ - What happens when a class and a function have the same name? - Stack Overflow](https://stackoverflow.com/questions/26341979/what-happens-when-a-class-and-a-function-have-the-same-name?noredirect=1&lq=1)

```cpp
void test(){cout<<"function"<<endl;}

struct test
{
    test(){cout<<"class"<<endl;}
};

int main()
{
    test(); // prints out function
    return 0;
}
```

[c++ - Why can't a class have same name for a function and a data member? - Stack Overflow](https://stackoverflow.com/questions/7763802/why-cant-a-class-have-same-name-for-a-function-and-a-data-member?rq=3)

Suppose you want to take the address of the member-function `size()`, then you would write this:

```cpp
auto address = &demo::size;
```

But it could be very well be the address of the member-data `size` as well. Ambiguous situation. Hence, it is disallowed by the language specification.

[c++ - function identifier and variable identifier relations? - Stack Overflow](https://stackoverflow.com/questions/63431521/function-identifier-and-variable-identifier-relations)

A function name is some sort of handle to the function—it is some thing that provides a way to call the function. In many C implementations, it is the address of the machine code of the function (in the virtual memory used in the running program). However, in some C implementations, it may be the address of a data structure that provides further information about the function, such as what registers the function uses and where its code is located in memory.

[Address of a function in C or C++ - GeeksforGeeks](https://www.geeksforgeeks.org/address-function-c-cpp/)

### 2. Scope

Perhaps I can just do as this:

```c
int add(int a, int b) // addpara("a", 1); addpara("b", 2);
{                     // Scope 0
    int sum;          // addlocal("sum");
    {                 // Scope 1
        int x = 7;    // addlocal("x");
        int y = 8;    // addlocal("y");
        {             // Scope 2
            int z = 1;
            sum = z;
        }             // Delete local vars decalred in Scope 2.
        sum = sum + x*a+y*b;
    }
    sum = sum + 1;    // Delete local vars decalred in Scope 1.
    return sum;
}                     // clearlocal(); // Called when entering a new function/main. 
```

[In c/c++, are block-scope variables stacked only if the block is executed? - Software Engineering Stack Exchange](https://softwareengineering.stackexchange.com/questions/125792/in-c-c-are-block-scope-variables-stacked-only-if-the-block-is-executed)

[Are stack variables always freed when they go out of scope? : r/cpp_questions](https://www.reddit.com/r/cpp_questions/comments/15ogm6i/are_stack_variables_always_freed_when_they_go_out/)

[c - malloc and scope - Stack Overflow](https://stackoverflow.com/questions/8101992/malloc-and-scope)

[c - Will malloc automatically free the memory at the end of a function? - Stack Overflow](https://stackoverflow.com/questions/34383241/will-malloc-automatically-free-the-memory-at-the-end-of-a-function)

### 3. Map (TODO)

[c++ - Is the order of iterating through std::map known (and guaranteed by the standard)? - Stack Overflow](https://stackoverflow.com/questions/7648756/is-the-order-of-iterating-through-stdmap-known-and-guaranteed-by-the-standard)

[c++ - std::vector is faster than std::map for a key lookup? - Stack Overflow](https://stackoverflow.com/questions/47192662/stdvector-is-faster-than-stdmap-for-a-key-lookup)

[c++ - Does std::map::find performance depend on the key size? - Stack Overflow](https://stackoverflow.com/questions/22607076/does-stdmapfind-performance-depend-on-the-key-size)

[c++ - Iterating over a map, starting at a specific key - Stack Overflow](https://stackoverflow.com/questions/59979244/iterating-over-a-map-starting-at-a-specific-key)

[c++ - std::map::upper_bound vs std::upper_bound performance - Stack Overflow](https://stackoverflow.com/questions/59799363/stdmapupper-bound-vs-stdupper-bound-performance)

[c++ - The ordering of an std::map - Stack Overflow](https://stackoverflow.com/questions/32471689/the-ordering-of-an-stdmap)

## Statements:

[Statements - cppreference.com](https://en.cppreference.com/w/c/language/statements)

There are five types of statements:

### 1. [compound statements](https://en.cppreference.com/w/c/language/statements#Compound_statements)

A compound statement, or *block*, is a brace-enclosed sequence of statements and declarations.

The compound statement allows a set of declarations and statements to be grouped into one unit that can be used anywhere a single statement is expected (for example, in an [if](https://en.cppreference.com/w/c/language/if "c/language/if") statement or an iteration statement).

Each compound statement introduces its own [block scope](https://en.cppreference.com/w/c/language/scope "c/language/scope").

The initializers of the variables with automatic [storage duration](https://en.cppreference.com/w/c/language/storage_duration "c/language/storage duration") declared inside a block and the VLA declarators are executed when flow of control passes over these declarations in order, as if they were statements.

- [ ] `{ statement | declaration...(optional) } (until C23)`

### 2. [expression statements](https://en.cppreference.com/w/c/language/statements#Expression_statements)

An expression statement without an expression is called a *null statement*. It is often used to provide an empty body to a [for](https://en.cppreference.com/w/c/language/for "c/language/for") or [while](https://en.cppreference.com/w/c/language/while "c/language/while") loop. It can also be used to carry a label in the end of a compound statement or before a declaration:

- [ ] `expression (optional) ;` -> ` ;`

### 3. [selection statements](https://en.cppreference.com/w/c/language/statements#Selection_statements)

- [ ] `if ( expression ) statement-true`

- [ ] `if ( expression ) statement-true else statement-false` -> `if ( expression ) statement-true else if ( expression ) statement-true else statement-false` -> ...

#### Declaration in a condition

##### C++ (Disallowed in C):

> A name introduced by a declaration in a condition (either introduced by 
> the type-specifier-seq or the declarator of the condition) is in scope 
> from its point of declaration until the end of the substatements 
> controlled by the condition.

```cpp
if (int x = f()) {
    int x;    // ill-formed, redeclaration of x
}
else {
    int x;    // ill-formed, redeclaration of x
}
```

[c++ - Defining a variable in the condition part of an if-statement? - Stack Overflow](https://stackoverflow.com/questions/12655284/defining-a-variable-in-the-condition-part-of-an-if-statement)

[c++ - Why is variable declared in an if-statement still in scope in else block? - Stack Overflow](https://stackoverflow.com/questions/67062409/why-is-variable-declared-in-an-if-statement-still-in-scope-in-else-block)

##### C:

[declaration - Where you can and cannot declare new variables in C? - Stack Overflow](https://stackoverflow.com/questions/8474100/where-you-can-and-cannot-declare-new-variables-in-c)

GNU C:

[Declare variable in if statement (ANSI C) - Stack Overflow](https://stackoverflow.com/questions/43643349/declare-variable-in-if-statement-ansi-c)

> A compound statement enclosed in parentheses may appear as an expression in GNU C. This allows you to use loops, switches, and local variables within an expression. Recall that a compound statement is a sequence of statements surrounded by braces; in this construct, parentheses go around the braces. For example:

```c
({ int y = foo (); int z;
   if (y > 0) z = y;
   else z = - y;
   z; })
```

**The last thing in the compound statement should be an expression followed by a semicolon; the value of this subexpression serves as the value of the entire construct.**

### 4. [iteration statements](https://en.cppreference.com/w/c/language/statements#Iteration_statements)

- [ ] `while ( expression ) statement`

- [ ] `do statement while ( expression ) ;` (Optional)

- [ ] `for ( init-clause ; expression(optional) ; expression(optional) ) statement` (Optional)

### 5. [jump statements](https://en.cppreference.com/w/c/language/statements#Jump_statements)

- [ ] `break ;`

- [ ] `continue ;`

- [ ] `return expression(optional) ;`

- [ ] `goto identifier ;`

### Labels (Optional)

Any statement can be *labeled*, by providing a name followed by a colon before the statement itself.

- [ ] `identifier :`

- [ ] `case constant-expression :`

- [ ] `default :`

Any statement (but not a declaration) may be preceded by any number of *labels*, each of which declares identifier to be a label name, which must be unique within the enclosing function (in other words, label names have [function scope](https://en.cppreference.com/w/c/language/scope "c/language/scope")).

Label declaration has no effect on its own, does not alter the flow of control, or modify the behavior of the statement that follows in any way.

(until C23) A label shall be followed by a statement.

(since C23) A label can appear without its following statement. If a label appears alone in a block, it behaves as if it is followed by a [null statement](https://en.cppreference.com/w/c/language/statements#Expression_statements)

## Assignment:

- [ ] Return Lvalue, e.g. `a = b = c = 0;` (Optional)

[Part 18: Lvalues and Rvalues Revisited](https://github.com/DoctorWkt/acwj/tree/master/18_Lvalues_Revisited)

[Assignment operators](https://en.cppreference.com/w/c/language/operator_assignment)

[Value categories](https://en.cppreference.com/w/c/language/value_category)