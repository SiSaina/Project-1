#pragma once
#include <iostream>
#include <iomanip>
#include "InputValidation.cpp"

using namespace std;

class LibrarianAccount{
private:
    int id;
    string name;
    double wage;
protected:
    InputValidation val;
public:
    LibrarianAccount() : id(0), name("unknown"), wage(0.0) {}
    LibrarianAccount(int id, string name, double wage) {
        setID(id);
        setName(name);
        setWage(wage);
    }

    int getID() const {
        return id;
    }
    string getName() const {
        return name;
    }
    double getWage() const {
        return wage;
    }
    void setID(const int id){
        this->id=id;
    }
    void setName(const string name){
        this->name=name;
    }
    void setWage(const double wage){
        this->wage=wage;
    }

    void input(){
        int id;
        string name;
        double wage;

        id=val.enterID();
        setID(id);
        name=val.enterName();
        setName(name);
        wage=val.enterWage();
        setWage(wage);
    }
    void output() const {
        cout<<getID()<<"\t"<<setw(30)<<left<<getName()<<"\t$"<<setw(15)<<getWage();
    }
    void display(){
        cout<<"ID: "<<getID()<<endl;
        cout<<"Name: "<<getName()<<endl;
        cout<<"Wage($/day): "<<getWage()<<endl;
    }
};