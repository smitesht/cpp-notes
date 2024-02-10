# unique_ptr

std::unique_ptr is a smart pointer that manages an object or an array allocated on the heap through a raw pointer.
It performs an appropriate disposal when the smart pointer goes out of scope.

- std::unique_ptr has exclusive ownership of resource.
- A non-null unique_ptr always owns what it point to
- Moving a std:: unique_ptr transfer ownership from the resource pointer to the destination pointer. The source pointer is set to null.
- Copy is not allowed as the unique_ptr always has only one owner.
- A non-null unique_ptr destroys its resource. Internally, it calls delete to the raw pointer.
- By default, resource destructor take place vvia delete, but custome deleter can also be used when need special deletion.

'''
#include <iostream>
#include <memory>
#include <string>

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

auto customDeleter = [](Foo \*pf) {
cout<<"custom deleter.."<<std::endl;
delete pf;
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
    return 0;

}
'''
