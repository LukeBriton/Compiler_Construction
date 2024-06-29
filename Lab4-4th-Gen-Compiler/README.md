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

By the way, [c - struct and union name collision - Stack Overflow](https://stackoverflow.com/a/45408848/3150802) mentions the different identifier categories in C. *Between* those categories there are no clashes, *within* them there are. Most notably, struct names and members do not clash with variables or functions.

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

### 3. std::map

We just didn't utilize what a `std::map` is capable of. Like, it's actually (generally implemented as) a Red-Black tree ordered by key, so it's $O(\log N)$ when just using `map::find` to do lookups. And it can be equipped with a "hint" for insertion, to lower the cost of each insertion from $O(\log N)$ to $O(1)$.

#### Data Structure

[c++ - Why is std::map implemented as a red-black tree? - Stack Overflow](https://stackoverflow.com/questions/5288320/why-is-stdmap-implemented-as-a-red-black-tree)

Although all implementations I've seen use an RB-tree, note that this is still implementation-dependent.

Probably the two most common self balancing tree algorithms are [Red-Black trees](http://en.wikipedia.org/wiki/Red-black_tree) and [AVL trees](http://en.wikipedia.org/wiki/AVL_tree). To balance the tree after an insertion/update both algorithms use the notion of rotations where the nodes of the tree are rotated to perform the re-balancing.

While in both algorithms the insert/delete operations are O(log n), in the case of Red-Black tree re-balancing rotation is an [O(1)](http://en.wikipedia.org/wiki/Big_O_notation) operation while with AVL this is a [O(log n)](http://en.wikipedia.org/wiki/Big_O_notation) operation, making the Red-Black tree more efficient in this aspect of the re-balancing stage and one of the possible reasons that it is more commonly used.

Red-Black trees are used in most collection libraries, including the offerings from Java and Microsoft .NET Framework.

The previous answers only address tree alternatives and red black probably only remains for historical reasons.

**Why not a hash table?**

A type only requires `<` operator (comparison) to be used as a key in a tree. However, hash tables require that each key type has a `hash` function defined. Keeping type requirements to a minimum is very important for generic programming so you can use it with a wide variety of types and algorithms.

Designing a good hash table requires intimate knowledge of the context it which it will be used. Should it use open addressing, or linked chaining? What levels of load should it accept before resizing? 
Should it use an expensive hash that avoids collisions, or one that is rough and fast?

Since the STL can't anticipate which is the best choice for your application, the default needs to be more flexible. Trees "just work" and scale nicely.

(C++11 did add hash tables with `unordered_map`. You can see from the [documentation](http://en.cppreference.com/w/cpp/container/unordered_map) it requires setting policies to configure many of these options.)

**What about other trees?**

Red Black trees offer fast lookup and are self balancing, unlike BSTs. Another user pointed out its advantages over the self-balancing AVL tree.

Alexander Stepanov (The creator of STL) said that he would use a B* Tree instead of a Red-Black tree if he wrote `std::map` again, because it is more friendly for modern memory caches.

> One of the biggest changes since then has been the growth of caches. Cache misses are very costly, so locality of reference is much more important now. Node-based data structures, which have low locality of reference, make much less sense. If I were designing STL today, I would have a different set of containers. For example, an in-memory B*-tree is a far better choice than a red-black tree for implementing an associative container. - [Alexander Stepanov](https://interviews.slashdot.org/story/15/01/19/159242/interviews-alexander-stepanov-and-daniel-e-rose-answer-your-questions)

**Should maps always use trees?**

Another possible maps implementation would be a sorted vector (insertion sort) and binary search. This would work well for containers which aren't modified often but are queried frequently. I often do this in C as `qsort` and `bsearch` are built in.

**Do I even need to use map?**

Cache considerations mean it rarely makes sense to use `std::list` or `std::deque` over `std:vector` even for those situations we were taught in school (such as removing an element from the middle of the list). 
Applying that same reasoning, using a for loop to linear search a list is often more efficient and cleaner than building a map for a few lookups.

Of course choosing a readable container is usually more important than performance.

[c++ - What is the time complexity of std::map - Stack Overflow](https://stackoverflow.com/questions/21740893/what-is-the-time-complexity-of-stdmap)

Lookups are proportional to $\log N$. In a typical case (implementation as a red-black tree) the number of comparisons can be up to twice $\log_{2}N$.

Insertions are *normally* proportional to $\log_{2}N$ as well--but there's a special provision made for when you're inserting a number of items that are already in order [^1] . In this case, you can specify a "hint" for where an insertion is going to take place. When that hint is correct, each insertion is (amortized) $O(1)$ instead of $O(\log N)$, so inserting a range of items in sorted order is linear instead of $O(N\log N)$. The hint you specify is an iterator to the position just after the item to be inserted.

For example, if you have a number of items in a file in sorted order, and you want to insert them into the map, you can specify `your_map.end()` as the "hint", and building the map will have $O(N)$ complexity instead of $O(N\log N)$ complexity.

[^1]: Technically, this applies anytime you insert items, not just when you're inserting them in order--but by far the most common case where you have a reasonable "hint" available is when you're inserting items in order.

#### Ordering

[c++ - Is the order of iterating through std::map known (and guaranteed by the standard)? - Stack Overflow](https://stackoverflow.com/questions/7648756/is-the-order-of-iterating-through-stdmap-known-and-guaranteed-by-the-standard)

Yes, that's guaranteed. Moreover, `*begin()` gives you the smallest and `*rbegin()` the largest element, as determined by the comparison operator, and two key values `a` and `b` for which the expression `!compare(a,b) && !compare(b,a)` is true are considered equal. The default comparison function is `std::less<K>`.

The ordering is not a lucky bonus feature, but rather, it is a fundamental aspect of the data structure, as the ordering is used to determine when two keys are the same (by the above rule) and to perform efficient lookup (essentially a binary search, which has logarithmic complexity in the number of elements).

I think there is a confusion in data structures.

In most languages, a `map` is simply an AssociativeContainer: it maps a key to a value. In the "newer" languages, this is generally achieved using a hash map, thus no order is guaranted.

In C++, however, this is not so:

- `std::map` is a **sorted** associative container
- `std::unordered_map` is a hash-table based associative container introduced in C++11

So, in order to clarify the guarantees on ordering.

**In C++03:**

- `std::set`, `std::multiset`, `std::map` and `std::multimap` are guaranteed to be ordered according to the keys (and the criterion supplied)
- in `std::multiset` and `std::multimap`, the standard does not impose any order guarantee on equivalent elements (ie, those which compare equal)

**In C++11:**

- `std::set`, `std::multiset`, `std::map` and `std::multimap` are guaranteed to be ordered according to the keys (and the criterion supplied)
- in `std::multiset` and `std::multimap`, the Standard *imposes* that equivalent elements (those which compare equal) are ordered according to their insertion order (first inserted first)
- `std::unordered_*` containers are, as the name imply, not ordered. Most notably, the order of elements *may* change when the container is modified (upon insertion/deletion).

When the Standard says that elements are ordered in a way, it means that:

- when iterating, you see the elements in the order defined
- when iterating in reverse, you see the elements in the opposite order

I hope this clears up any confusion.

[c++ - The ordering of an std::map - Stack Overflow](https://stackoverflow.com/questions/32471689/the-ordering-of-an-stdmap)

#### Hint

[c++ - std::map insert() hint location: difference between c++98 and c++11 - Stack Overflow](https://stackoverflow.com/questions/32758548/stdmap-insert-hint-location-difference-between-c98-and-c11)

Yes, it will affect the complexity. Giving the correct hint will make `insert()` have amortized constant complexity, while giving and incorrect hint will force the map to search for the position from the beginning, giving logarithmic complexity. Basically, a good hint makes the insertion happen in constant time, no matter how big your map is; with a bad hint the insertion will be slower on larger maps.

The solution is, apparently, to search for the hint with `upper_bound` instead of `lower_bound`.

[Why is it not possible to give std::map::find a hint when one can give std::map::insert a hint?](https://groups.google.com/a/isocpp.org/g/std-discussion/c/yUF5PhT8psY)

[map::insert gets a hint. What about map::find? - C / C++](https://bytes.com/topic/c/139196-map-insert-gets-hint-what-about-map-find)

[c++ - std::unordered_map insert with hint - Stack Overflow](https://stackoverflow.com/questions/15559655/stdunordered-map-insert-with-hint)

#### Vector

[c++ - std::vector is faster than std::map for a key lookup? - Stack Overflow](https://stackoverflow.com/questions/47192662/stdvector-is-faster-than-stdmap-for-a-key-lookup)

I would say that in general, it's possible that a vector performs 
better than a map for lookups, but for a tiny amount of data only, e.g. 
you've mentioned less than 30 elements.

The reason is that linear search through continuous memory chunk is 
the cheapest way to access memory. A map keeps data at random memory 
locations, so it's a little bit more expensive to access them. In case 
of a tiny number of elements, this might play a role. In real life with 
hundreds and thousands of elements, **algorithmic complexity** of a lookup operation will dominate this performance gain.

**BUT!** You are benchmarking completely different things:

1. You are populating a map. In case of a vector, you don't do this
2. Your code could perform TWO map lookups: first, **find** to check existence, second **[]** operator to find an element to modify. These are relatively heavy operations. You can modify an element just with single **find** (figure this out yourself, check references!)
3. Within each test iteration, you are performing *additional heavy operations*,
   like memory allocation for each map/vector. It means that your tests are measuring not only lookup performance but something else.
4. Benchmarking is a difficult problem, don't do this yourself. For example, there are side effects like cache heating and you have to deal with them. Use something like [Celero](https://github.com/DigitalInBlue/Celero), [hayai](https://github.com/nickbruun/hayai) or [google benchmark](https://github.com/google/benchmark)

Speaking only on the first two paragraphs: 
Yes, and the reason in this case the memory is contiguous is that the vector is holding `std::string` for values which very likely fit in the library's "small string optimization" range - thus the entire string is in contiguous memory. Given the answer [here](https://stackoverflow.com/a/21710033/751579) plus a typical [64 byte cache line width](http://www.7-cpu.com/cpu/Haswell.html) this vector of strings fits in 10 cache lines - accessed sequentially hence prefetched. The map is all over the place. This vector search compares better cold than hot!

Let me clarify: It also well work better hot than the map, just with less of an advantage once the map - also small - is all brought into cache.

[How to create std::map that preserves the order of insertion just using standard C++? : r/cpp_questions](https://www.reddit.com/r/cpp_questions/comments/xh5rb8/how_to_create_stdmap_that_preserves_the_order_of/)

You'll need a vector and a map. You can either use;

1. a map (key,value) and iterate though a vector of values,

2. a map (key,value) and iterate though a vector of keys,

3. a map of (key,index) followed by a vector lookup and iterate though a vector of values - probably slowest,

4. an unordered_map (index,value) and iterate though a vector of keys,

You can try all the above, but replacing the vector for a vector of pair<key,value>. Perhaps this will have some performance increase if you iterate a lot though (key,Val) pairs.

You'll want a vector, not a list, because it's more cache friendly. Do some testing to see which is faster for your use case. Are you iterating or accessing more often?

OP: I access it more often

If the keys are hashable, you might be better off using an unordered_map<key,val>. Otherwise, I'm not sure if map<key,val> or unordered_map<index,val> is quicker.

If you need to iterate though (key,val) pairs, you'll need a Vector of keys (or pair<key,val>, again not sure which is quicker for your use case). Otherwise, just go with a vector of values

### Solution

Should we change to use `std::vector`, or should we combine it with `std::map` or `std::unordered_map`?

It's our case that we just keep the insertion order, and formerly I didn't pay much attention to the design of overloaded `<`, and I think just comparing first the `name` (then `type`, `stype`) is not efficient. Maybe we should add a member `scope` into the struct `symbol` and compare? Different scopes are separated, so we don't need perhaps a stack to store the scopes. Or even we can add an `index` as member of `symbol`, then compare it first, which has been stored in Value before, so it really preserves the insertion order. (Except that order of parametres are just reversed.)

- `std::map<symbol, int> IDs;`

Still it's a problem whether we use `symbol` or `name` as the key, and if we only use `name`, how to store the corresponding `symbol`s? We have negative Values for parametres, but we also have `para_num` when adding parametres, and this can be useful. Maybe we can keep it and when I find the Value, we just add both of them to locate it in `std::vector`. And it's promising for the properties below:

[std::vector - cppreference.com](https://en.cppreference.com/w/cpp/container/vector)

The complexity (efficiency) of common operations on vectors is as follows:

- Random access - constant 𝓞(1).
- Insertion or removal of elements at the end - amortized constant 𝓞(1).
- Insertion or removal of elements - linear in the distance to the end of the vector 𝓞(n). (Which isn't a problem because we always insert/delete local variables at the end.)

Now I suppose we can maintain two STL containers for a symbol table.

It would be better if we could have a `std::map` sorted by value, but that's not how `std::map` works.

[java - Sort a Map<Key, Value> by values - Stack Overflow](https://stackoverflow.com/questions/109383/sort-a-mapkey-value-by-values)

[Sorting a Map by value in C++ STL - GeeksforGeeks](https://www.geeksforgeeks.org/sorting-a-map-by-value-in-c-stl/)

First proposal:

- `std::map<string, int> IDs;` Wait, where is the scope, and we lose the benefit that "hint" may bring us.

- `std::vector<symbol> IDtab;`

Second proposal:

- `std::map<pair<string, int>, int> IDs;` Here we can map (`name`, `scope`)/(`name`, `index`) to `index`. But the lookup process is still linear, and if we use (`name`, `scope`), "hint" is also unused.

- `std::vector<symbol> IDtab;`

Third proposal:

- `std::map<string, pair<int, int>> IDs;` Here we can map `name` to (`index`, `scope`). But "hint" cannot be used, and those of the same scope aren't contiguous either.

- `std::vector<symbol> IDtab;`

1, 3 both have a problem, that if two variables of different scopes are homonymous:

```c
int main()
{
    int a = 3, b = 4;
    if(a > 0)
    {
        int a = 4;
        {
            int b = a + 2;
            return b;
        }
    }
    return 0;
}
```

[C - function inside struct - Stack Overflow](https://stackoverflow.com/questions/17052443/c-function-inside-struct)

[C++ map's insert functions are a mess. : r/cpp](https://www.reddit.com/r/cpp/comments/x5n5aj/c_maps_insert_functions_are_a_mess/)

[c++ - std::map range erase complexity - Stack Overflow](https://stackoverflow.com/questions/38002619/stdmap-range-erase-complexity)

[c++ - Deleting map elements in a range-based loop - Stack Overflow](https://stackoverflow.com/questions/75821522/deleting-map-elements-in-a-range-based-loop)

[c++ - Erasing nodes of a std::map within a range-based "for" loop - Stack Overflow](https://stackoverflow.com/questions/77958080/erasing-nodes-of-a-stdmap-within-a-range-based-for-loop)

[c++ - How to remove from a map while iterating it? - Stack Overflow](https://stackoverflow.com/questions/8234779/how-to-remove-from-a-map-while-iterating-it)

[c++ - Safe to erase from map inside range based for? - Stack Overflow](https://stackoverflow.com/questions/25246937/safe-to-erase-from-map-inside-range-based-for)

Maybe we can turn to `std::multimap`, which is almost the same as `std::map`. Better rather not...

[c# - Red Black Tree and Multimap - Stack Overflow](https://stackoverflow.com/questions/13525138/red-black-tree-and-multimap)

[c++ - multimap upper_bound return confusion - Stack Overflow](https://stackoverflow.com/questions/9832058/multimap-upper-bound-return-confusion)

But I suppose `lower_bound` and `upper_bound` are useful.

[c++ - std::map::upper_bound vs std::upper_bound performance - Stack Overflow](https://stackoverflow.com/questions/59799363/stdmapupper-bound-vs-stdupper-bound-performance)

Based on former Second Proposal:

- `std::map<pair<string, int>, int> IDs;` 

- `std::vector<symbol> IDtab;`

Here we map (`name`, `scope`) to `index`. "hint" is still unused, but other things can be better.

**TODO**: There are a lot of designs in this project based on the principle that the input code files are written correctly. But this may cause trouble at any time... I need some time to write exception handling etc., which sadly must be postponed for the moment.

By the way we don't delete and don't care about the insertion order of functions, neither don't they have scopes, maybe it's okay to do so:

- `std::unordered_map<string, int> FUNCs;`

- `std::vector<symbol> FUNCtab`

#### Related

[c++ - Does std::map::find performance depend on the key size? - Stack Overflow](https://stackoverflow.com/questions/22607076/does-stdmapfind-performance-depend-on-the-key-size)

[c++ - Iterating over a map, starting at a specific key - Stack Overflow](https://stackoverflow.com/questions/59979244/iterating-over-a-map-starting-at-a-specific-key)

## Statements:

[Statements - cppreference.com](https://en.cppreference.com/w/c/language/statements)

There are five types of statements:

### 1. [compound statements](https://en.cppreference.com/w/c/language/statements#Compound_statements)

A compound statement, or *block*, is a brace-enclosed sequence of statements and declarations.

The compound statement allows a set of declarations and statements to be grouped into one unit that can be used anywhere a single statement is expected (for example, in an [if](https://en.cppreference.com/w/c/language/if "c/language/if") statement or an iteration statement).

Each compound statement introduces its own [block scope](https://en.cppreference.com/w/c/language/scope "c/language/scope").

The initializers of the variables with automatic [storage duration](https://en.cppreference.com/w/c/language/storage_duration "c/language/storage duration") declared inside a block and the VLA declarators are executed when flow of control passes over these declarations in order, as if they were statements.

- [ ] `{ statement | declaration...(optional) } (until C23)`

[In c/c++, are block-scope variables stacked only if the block is executed? - Software Engineering Stack Exchange](https://softwareengineering.stackexchange.com/questions/125792/in-c-c-are-block-scope-variables-stacked-only-if-the-block-is-executed)

[When can I omit curly braces in C? - Stack Overflow](https://stackoverflow.com/questions/14901919/when-can-i-omit-curly-braces-in-c)

The only places you can omit brackets are for the bodies of `if-else`, `for`, `while`, `do-while`, or `switch` statements if the body consists of a single statement:

```c
if (cond)
  do_something();

for (;;)
  do_something();

while(condition)
  do_something();

do 
  do_something();
while(condition);
```

However, note that each of the above examples counts as single statement according to the grammar; that means you can write something like

```c
if (cond1)
  if (cond2)
    do_something();
```

This is perfectly legal; `if (cond2) do_something();` reduces to a single statement. So, for that matter, does `if (cond1) if (cond2) do_something();`, so you could descend further into madness with something like

```c
for (i=0; i < N; i++)
  if (cond1)
    if (cond2)
      while (cond3)
        for (j=0; j < M; j++)
          do_something(); 
```

Don't do that.

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