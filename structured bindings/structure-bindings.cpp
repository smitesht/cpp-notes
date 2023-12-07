// structure-bindings.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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


