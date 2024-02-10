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