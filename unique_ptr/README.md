# unique_ptr

std::unique_ptr is a smart pointer that manages an object or an array allocated on the heap through a raw pointer.
It performs an appropriate disposal when the smart pointer goes out of scope.

- std::unique_ptr has exclusive ownership of a resource.
- A non-null unique_ptr always owns what it points to
- Moving a std:: unique_ptr transfer ownership from the resource pointer to the destination pointer. The source pointer is set to null.
- Copy is not allowed as the unique_ptr always has only one owner.
- A non-null unique_ptr destroys its resource. Internally, it calls delete to the raw pointer.
- By default, resource destructor takes place via delete, but custom deleter can also be used when needing special deletion.

```c++
#include <iostream>
#include <memory>
#include <string>
#include <utility>


using std::unique_ptr;
using std::make_unique;
using std::cout;
using std::string;


class Foo
{
    int Id;
    string Name;
    public:
        Foo() { cout<<"ctor..."; }
        Foo(int id, string name):Id(id),Name(name)
        {
            cout<<"ctor.. "<<Id<<" "<<Name<<std::endl;
        }
        ~Foo() { cout<<"dtor..."; }
};

auto customDeleter = [](Foo *pf) {
    cout<<"custom deleter.."<<std::endl;
    delete pf;
};

class Base
{
    public:
        virtual ~Base()
        {
            std::cout<<"~Base() dtor..."<<std::endl;
        }
};

class Derived : public Base
{
    public:
        virtual ~Derived()
        {
            std::cout<<"~Derived dtor..."<<std::endl;
        }
};


int main()
{

    unique_ptr<int> pNull;
    unique_ptr<int> pi(new int(32));
    unique_ptr<int[]> parr(new int[4] {1,2,3,4});
    unique_ptr<Foo> pFoo(new Foo(10,"C++"));

    // create object using make_unique
    unique_ptr<int> mi = make_unique<int>(32);
    unique_ptr<int[]> mArr = make_unique<int[]>(4);
    unique_ptr<Foo> mFoo = make_unique<Foo>(3,"CPP");

    unique_ptr<Foo,decltype(customDeleter)> mFooEx(new Foo(4,"Hello"),customDeleter);
    mFooEx.reset();


    unique_ptr<Derived> pDerived = std::make_unique<Derived>();
    unique_ptr<Base> pBase = std::move(pDerived);

    return 0;
}
```

An std::unique_ptr that manages the object of a Derived class can be implicitly onverted to an std::unique_ptr that manages an object of the class Base if Derived is derived from the Base class. The implicit conversion is safe only if Base has a virtual destructir, otherwise, undefined behaviour is employed.

```c++

class Base
{
    public:
        virtual ~Base()
        {
            std::cout<<"~Base() dtor..."<<std::endl;
        }
};

class Derived : public Base
{
    public:
        virtual ~Derived()
        {
            std::cout<<"~Derived dtor..."<<std::endl;
        }
};

```

std::unique_ptr can be stored in containers, such as vector. As only one std::unique_ptr object can be own the managed object at any point, the smart pointer cannot be copied to the container, it has to be moved. This is possible with std::move(), which performs a static_cast to an rvalue reference type. This allows the ownership of the managed object to vbe transferred to the unique_ptr object that is crearted in the container.
