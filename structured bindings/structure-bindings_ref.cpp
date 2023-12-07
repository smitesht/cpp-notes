/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <string>


using namespace std;

struct Employee{
    string name;
    int age;
};

int main()
{
    // structured bindings example
    
    Employee e1 { "Jhon", 23 };
    auto [name, age] = e1;
    
    cout<<e1.name<<endl;  // print Jhon
    cout<<name<<endl;     // print Jhon
    
    // By default structured bindings perform value type bindings
    // Changes in name will not change the e1.name
    
    name = "Robert";
    cout<<e1.name<<endl; // print Jhon
    cout<<name<<endl;    // print Robert
    
    // structured bindings with reference type
    auto &[ename, eage] = e1;
    
    // with the reference bindings changes in ename will change the e1.name
    ename = "Robert";
    cout<<e1.name<<endl; // print Robert
    cout<<name<<endl;    // print Robert
    

    return 0;
}
