# Functors in C++

Let's consider we have a vector that contains name of people. We are interested to know how many names which length is less than 5. To solve this we use **count_if** method. The **count_if** function takes three parameters, start position, end position and unary predicate ( a method that takes single argument to check the condition and return true or false).

```cpp
bool LengthIsLessThanFive(const string& str)
{
    // if the length is less than 5 return true o.w. false
    return str.length() < 5;
}
```

Now consider we have a new requirement to count names which are less than 7, we can write new function LengthIsLessThanSeven.

```cpp
bool LengthIsLessThanSeven(const string& str)
{
    // if the length is less than 7 return true o.w. false
    return str.length() < 7;
}
```

Let's say we have again new requirement to count names less than 10, should we create new function? Creating new method on each requirement is not feasible solution.

What if we create general method like this

```cpp
bool LengthIsLessThan(const string& str, int length)
{
    // if the length is less than length return true o.w. false
    return str.length() < length;
}

```

The problem is that **count_if** accept only predicate that contains only one argument. Hence, LengthIsLessThan will not work.

We can declare global variable and use that variable in the LengthIsLessThan method but this is also not the feasible solution. What is we forgot to initialize global variable? we can lead to wrong value.

```cpp
int gMaxLength;

bool LengthIsLessThan(const string& str)
{
    // if the length is less than gMaxLength return true o.w. false
    return str.length() < gMaxLength;
}
```
