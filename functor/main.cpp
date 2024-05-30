#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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


int main()
{
    vector<string> names = {"Jack", "Benjamin", "Leo", "Oliver", "Anderson", "Amelia", "Ava"};

    //int count = count_if(names.begin(), names.end(), LengthIsLessThanFive);
    //cout<<"Total Words Less than five: "<<count<<endl;

    int count = count_if(names.begin(), names.end(), LengthIsLessThanSeven);
    cout<<"Total Words Less than seven: " << count << endl;
    return 0;
}