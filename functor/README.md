# Functors in C++

Let's consider we have a vector that contains name of people. We are interested to know how many names which length is less than 5. To solve this we use **count_if** method. The **count_if** function takes three parameters, start position, end position and unary predicate ( a method that takes single argument to check the condition and return true or false).

```cpp
bool LengthIsLessThanFive(const string& str)
{
    // if the length is less than 5 return true o.w. false
    return str.length() < 5;
}

int main()
{
    vector<string> names = {"Jack", "Benjamin", "Leo", "Oliver", "Anderson", "Amelia", "Ava"};

    int count = count_if(names.begin(), names.end(), LengthIsLessThanFive);
    cout<<"Total Words Less than five: "<<count<<endl;

    return 0;
}

```

Now consider we have a new requirement to count names which are less than 7, we can write new function LengthIsLessThanSeven.

```cpp
bool LengthIsLessThanSeven(const string& str)
{
    // if the length is less than 7 return true o.w. false
    return str.length() < 7;
}

int main()
{
    vector<string> names = {"Jack", "Benjamin", "Leo", "Oliver", "Anderson", "Amelia", "Ava"};

    int count = count_if(names.begin(), names.end(), LengthIsLessThanSeven);
    cout<<"Total Words Less than seven: " << count << endl;

    return 0;
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

This problem can be solved using **functor or function object**.

### Functor or Function Object:

A functor or function object is an object that is called like function. This can be achieved by defining the **_operator ()_** within a class or struct.

### ReturnType operator() (ParamType1 para1, ParamType2 para2,...);

Examples

```cpp
struct StringLenComparer
{
    int length;

    // constructor
    StringLenComparer(int len):length(len){}

    bool operator()(const string& str)
    {
        return str.length() < length;
    }
};

int main()
{
    vector<string> names = {"Jack", "Benjamin", "Leo", "Oliver", "Anderson", "Amelia", "Ava"};

    // StringLenComparer strLenComparer(4);
    // count = count_if(names.begin(), names.end(), strLenComparer);
    count = count_if(names.begin(), names.end(), StringLenComparer(5));
    cout<<"Total Words : " << count << endl;

    return 0;
}

```

### Functor on custom sorting

Consider an employee class where data are sorted by employee id, and we want to sort all the employee by department.

```cpp

class Employee{
    public:
        int empId;
        string name;
        string department;

        Employee(int id, string name, string dept)
            :empId(id), name(name), department(dept){}
};

class SortByDepartment{
    public:
        bool operator()(const Employee& e1, const Employee& e2)
        {
            return e1.department < e2.department;
        }
};

```

Functor as a callback

```cpp
class Button{

    private:
        // store function address with the same signature
        std::function<void()> clickHandler;

    public:
        template <typename T>
        void setClickHandler(T handler){
            clickHandler = handler;
        }

        void click(){
            if(clickHandler){
                //call function which are stored in std::function
                clickHandler();
            }
        }
};

class CLickHandler{
    public:
        void operator()() const{
            std::cout<<"Button clicked" << std::endl;
        }
};

```

```cpp
int main()
{

    vector<Employee> employees =
        {
            {1, "Jhon Doe", "HR"},
            {2, "Jana Prakash", "IT"},
            {3, "Emily Davis", "HR"},
            {4, "Robert Kiyosaki", "Finance"},
            {5, "Sundar Pitchai", "IT"}
        };

        sort(employees.begin(), employees.end(), SortByDepartment());

        for(const auto& emp: employees)
        {
            cout<<emp.empId<<", "<<emp.name<<", "<<emp.department<<endl;
        }


    Button button;

    // pass functor to setClickHandler
    button.setClickHandler(CLickHandler());
    button.click();

    return 0;
}

```

## Functors and Lambda Expression

In C++, functors and lambdas are both ways to create callable objects, but they have different characteristics and use cases.

### Functor:

A functor is an instance of a class or struct that has an overloaded **_operator()_**. It can store state and provide callable behavior.

```cpp
class Greet{

private:
    string greet;
public:
    //ctor
    Greet(string _greet):greet(_greet){}

    string operator()(string name){
        return greet + " " + name + "!";
    }
};

int main()
{
    Greet engGreet("Helllo");  // create Greet object
    cout<<engGreet("Jhone")<<endl;  // call functor (or operator())
    cout<<engGreet("Robert")<<endl;


    return 0;
}

OUTPUT:
============
Helllo Jhone!
Helllo Robert!

```

### Lambda:

A lambda is an anonymous function object created using the lambda syntax introduced in C++11. It can capture variables from its enclosing scope and provide callable behavior without the need for a named class or struct.

```cpp

    string enGgreet = "Hello";
    // Lambda expression
    auto greet = [enGgreet](string name){
        return enGgreet + " " + name + "!";
    };

    cout<<greet("Jhone")<<endl;
    cout<<greet("Robert")<<endl;
```

#### Storing state

Functors store state in its member variable. The state is defined at the time of the functor's creation.
In this example, greet store the state, and every time when we create instantiate functor, we have to provide the state.

```cpp
class Greet{

private:
    // store state
    string greet;
public:
    //ctor
    Greet(string _greet):greet(_greet){}

    string operator()(string name){
        return greet + " " + name + "!";
    }
};

Greet engGreet("Helllo");  // create Greet object
cout<<engGreet("Jhone")<<endl;  // call functor (or operator())
cout<<engGreet("Robert")<<endl;

Greet hindiGreet("Namaste");
cout<<hindiGreet("Manish")<<endl;
cout<<hindiGreet("Narendra")<<endl;

Greet frenchGreet("Bonjour");
cout<<frenchGreet("Amelia")<<endl;

```

While lambda captures variable from the surrounding scope.

```cpp
// lambda capture variable outside
string enGgreet = "Hello";
string hindiGreet = "Namaste";
string frenchGreet = "Bonjour";

auto enGreet = [enGgreet](string name){
    return enGgreet + " " + name + "!";
};

auto hnGreet = [hindiGreet](string name){
    return hindiGreet + " " + name + "!";
};

auto frGreet = [frenchGreet](string name){
    return frenchGreet + " " + name + "!";
};

cout<<enGreet("Jhone")<<endl;
cout<<enGreet("Robert")<<endl;

cout<<hnGreet("Manish")<<endl;
cout<<hnGreet("Narendra")<<endl;

cout<<frGreet("Amelia")<<endl;

```

#### Advantages and Disadvantages

Functors:

- **Advantages**: Functors can be more expressive, reusable, and maintainable for complex logic. State management is clear and encapsulated.

- **Disadvantages**: Require more boilerplate code to define the class or struct

Lambda:

- **Advantages**: Lambda is concise, inline and easy to use for simple operations. Supports capturing variable from the enclosing scope.

- **Disadvantages**: Less reusable if the logic needs to be used in multiple places. Captures can lead to bugs if not managed carefully.
