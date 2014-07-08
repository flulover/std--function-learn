//
//  main.cpp
//  stdfunctionLearn
//
//  Created by twer on 7/8/14.
//  Copyright (c) 2014 twer. All rights reserved.
//

#include <iostream>
using namespace std;

void printHello()
{
    cout<< "Hello" << endl;
}

void printInteger(int i)
{
    cout << i << endl;
}

void printIntegerAndString(int i, const string&name)
{
    cout<< i << name << endl;
}

class Person
{
private:
    int age = 0;
    string name;
    
public:
    void setAge(int age)
    {
        this->age = age;
    }
    
    void setName(const string& name)
    {
        this->name = name;
    }
    
    int getAge() const
    {
        return age;
    }
    
    void setNameAndAge(const string& name, int age)
    {
        setName(name);
        setAge(age);
    }
    
    const string& getName() const
    {
        return name;
    }
    
    void dump() const
    {
        cout<< age << name << endl;
    }
};

int main(int argc, const char * argv[])
{
    std::function<void(int, const string&)> lamdbFunctor = [](int age, const string& name){
        cout << "lambd" << age << name << endl;
    };
    lamdbFunctor(1, "yzzhou");
    
    std::function<void(const string&)> lambdIntegerFunctor = std::bind(lamdbFunctor, 3, std::placeholders::_1);
    lambdIntegerFunctor("bind yzzhou");
    
    function<void()> printHelloFunctor = printHello;
    printHelloFunctor();
    
    function<void(int)> printIntegerFunctor = printInteger;
    printIntegerFunctor(18);
    
    function<void()> printIntegerFunctor18 = std::bind(printInteger, 18);
    printIntegerFunctor18();
    
    using placeholders::_1;
    function<void(const string&)> printIntegerAndStringFunctor = std::bind(printIntegerAndString, 1, _1);
    printIntegerAndStringFunctor("name");
    
    Person iAm18;
    function<void(Person&, const string&)> setNameFunctor = &Person::setName;
    setNameFunctor(iAm18, "yzzhou");
    iAm18.dump();
    
    function<void()> setNameYzzhouFunctor = std::bind(&Person::setName, &iAm18, "yzzhouIAm18");
    setNameYzzhouFunctor();
    iAm18.dump();
    
    function<void(const string&)> setNamePlaceholderFunctor = std::bind(&Person::setName, &iAm18, _1);
    setNamePlaceholderFunctor("yzzhouAgain");
    iAm18.dump();
    
    return 0;
}

