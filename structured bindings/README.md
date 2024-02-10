# Structured Bindings in C++ 17

Structured Bindings help to extract or destructure members of a structure, class, tuple, or pair more conveniently and concisely.

### Example
Consider the below code example where **ShowAllProducts()** prints all the products from the m_Products vector.

```
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Product
{
    int product_id;
    string name;
    string description;
    float price;
    string image_url;
};

class ProductManager
{
private: 
    vector<Product> m_Products;

public:
    ProductManager() {};
    void AddProduct(Product p);
    void ShowAllProducts();
    void ImprovedShowAllProducts();
    ~ProductManager();
};


void ProductManager::AddProduct(Product p)
{
    m_Products.push_back(p);

}

void ProductManager::ShowAllProducts()
{
    for(auto product: m_Products)
    {
        cout << "Product Id :" << product.product_id<<endl;
        cout << "Name       :" << product.name << endl;
        cout << "Description:" << product.description << endl;
        cout << "Price      :" << product.price << endl;
        cout << "Image URL  :" << product.image_url << endl;       
    }
}

ProductManager::~ProductManager()
{
    m_Products.clear();
}

int main()
{
    ProductManager p;
    
    p.AddProduct(Product{ 1,"Coffee", "This is Coffee",20.00f,"Coffee-mage-url" });
    p.AddProduct(Product{ 2,"Milk", "This is Milk",10.00f,"Milk-image-url" });
    p.AddProduct(Product{ 3,"Cookies", "This is Cookies",5.00f,"Cookies-image-url" });
    p.AddProduct(Product{ 4,"Green Tea", "This is Green Tea",25.00f,"GreenTea-image-url" });
    p.AddProduct(Product{ 5,"Hot Choclate", "This is Hot Choclate",20.00f,"HotChoclate-image-url" });
    p.ShowAllProducts();
    p.ImprovedShowAllProducts();
}
```
In the **ShowAllProducts()** for loop, it creates a dummy variable product, and each time we want to access the Product property, we have to perform **product.property_name**.

This can be easily avoided using Structured Bindings.

```
void ProductManager::ImprovedShowAllProducts()
{
    for (auto [id, name, desc, price, url] : m_Products)
    {
        cout << "Product Id :" << id << endl;
        cout << "Name       :" << name << endl;
        cout << "Description:" << desc << endl;
        cout << "Price      :" << price << endl;
        cout << "Image URL  :" << url << endl;
    }
}
```
Structured Bindings allows extracting each Product member without introducing a dummy variable. This improves the coding style and code readability. 

## Syntax

```
auto [var1, var2, var3, . . . ] = expression;

auto [ var1, var2, var3 , . . . ] { expression };

auto [ var1, var2, var3, . . . ] ( expression );
```

## How Structured Bindings Works

When the compiler sees structured bindings, it might create a temporary tuple-like object with member variables corresponding to the expression.

```
auto tuple_like_obj = expression;
using var1 = tuple_like_obj.first;
using var2 = tuple_like_obj.second;
```

The variables **var1** and **var2** are just other names for the **first**, and **second**. The **decltype(var1)** is the type of the member **first**, and **decltype(var2)** is the type of **second**. Also, as the compiler creates a temporary tuple-like object, we cannot access it by name directly like **tuple_like_obj.first**.

Structure binding uses automatic type deduction to unpack the structure into variables. It determines the type of each value independently and assigns a corresponding type to each variable.

auto [var1, var2, var3, . . . ] = expression;

We must use ***auto*** as structured binding performs automatic type deduction for the specific type binding.

## Binding

Consider this example,

```
struct Employee
{
    string name;
    int age;
};


Employee jhon {"Jhon", 23};
auto [name, age] = jhon;
```

By default structured bindings perform value type bindings rather than reference bindings. This means the change in ***name*** will not change in ***jhon.name*** and vice versa.

```
jhon.name = "New Jhon";
cout<<name<<endl;  // Jhon
cout<<jhon.name<<endl;  //New Jhon

name = "Robin";
cout<<name<<endl;  // Robin
cout<<jhon.name<<endl;  // New Jhon
```

### References in Structured Bindings

```
auto & [ var1, var2, var3, . . . ] = expression;
   
Employee jhon {"Jhon", 23};
auto & [name, age] = jhon;


jhon.name = "New Jhon";
cout<<name<<endl; //New Jhon
cout<<jhon.name<<endl; //New Jhon
    
name = "Robin";
cout<<name<<endl; // Robin
cout<<jhon.name<<endl;  // Robin
```

Here, ***name*** and ***age*** are reference bindings to ***jhon.name*** and ***jhon.age***. Hence, any changes in ***name*** or ***age***, reflect changes in ***jhon.name*** or ***jhon.age***.

## NOTE: 
The number of elements or data members must fit the number of names in the declaration of the structured binding.

```
struct Employee
{
    string name;
    int age;
};

int main()
{
    Employee jhon {"Jhon", 23};    
    auto [name] = jhon; // ERROR: only 1 name provided for structured binding
}
```

## More Examples:

### Structure Binding with nested class/struct

```
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
```

### Structure Binding with tuple or pair

```
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
```
