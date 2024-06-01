#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

bool LengthIsLessThanFive(const string& str)
{
    return str.length() < 5;
}

bool LengthIsLessThanSeven(const string& str)
{
    return str.length() < 7;
}

int gLength;

bool LengthIsLessThan(const string& str)
{
    return str.length() < gLength;
}

struct StringLenComparer
{
    int length;

    StringLenComparer(int len):length(len){}

    bool operator()(const string& str)
    {
        return str.length() < length;
    }
};


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
    vector<string> names = {"Jack", "Benjamin", "Leo", "Oliver", "Anderson", "Amelia", "Ava"};

    //int count = count_if(names.begin(), names.end(), LengthIsLessThanFive);
    //cout<<"Total Words Less than five: "<<count<<endl;

    int count = count_if(names.begin(), names.end(), LengthIsLessThanSeven);
    cout<<"Total Words Less than seven: " << count << endl;

    //StringLenComparer strLenComparer(4);
    //StringLenComparer strLenComparer(4);
    count = count_if(names.begin(), names.end(), StringLenComparer(5));
    cout<<"Total Words : " << count << endl;



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

    
    /*Greet engGreet("Helllo");  // create Greet object 
    cout<<engGreet("Jhone")<<endl;  // call functor (or operator())
    cout<<engGreet("Robert")<<endl;

    Greet hindiGreet("Namaste");
    cout<<hindiGreet("Manish")<<endl;
    cout<<hindiGreet("Narendra")<<endl;

    Greet frenchGreet("Bonjour");
    cout<<frenchGreet("Amelia")<<endl;*/


    // Lambda Expression
    string enGgreet = "Hello";
    auto greet = [enGgreet](string name){
        return enGgreet + " " + name + "!";
    };

    cout<<greet("Jhone")<<endl;
    cout<<greet("Robert")<<endl;

    return 0;
}