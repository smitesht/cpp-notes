/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <tuple>
#include <string>
#include <utility>

using namespace std;

std::tuple<string, int, float> GetProductData()
{
    // process data...
    return tuple<string, int, float> ("Apple 15",12,1500.00f);
}


std::pair<string, int> GetData()
{
    // process data..
    return pair<string, int> ("Mango",20);
}

int main()
{
    
    auto [name, qty, price] = GetProductData();
    
    cout<<name<<endl;
    cout<<qty<<endl;
    cout<<price<<endl;
    
    auto [fruit, amount] = GetData();
    cout<<fruit<<endl;
    cout<<amount<<endl;

    return 0;
}
