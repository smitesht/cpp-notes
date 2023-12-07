/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <string>


using namespace std;

struct Address{
    string street;
    string city;
    string pincode;
};

struct Employee{
    string name;
    int age;
    Address address;
};

int main()
{
    // structured bindings of nested struct or class
    Employee e1 { "Jhon", 23, { "Jasper Avenue", "Edmonton", "T2Y 4E5"} };
    
    auto [name, age, address] = e1;
    auto [street, city, pincode] = address;
    
    cout<<name << endl <<age<< endl  <<street<< endl <<city<< endl <<pincode<<endl;     
    
    return 0;
}


