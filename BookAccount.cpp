#pragma once
#include <iostream>
#include <iomanip>
#include "InputValidation.cpp"
#include "ExceptionHandling.cpp"

using namespace std;

class BookAccount {
private:
    int id;
    string name;
    double price;
protected:
    InputValidation val;
public:
    BookAccount() : id(-1), name("unknown"), price(0.0) {}
    BookAccount(int id, string name, double price) {
        setID(id);
        setName(name);
        setPrice(price);
    }

    int getID() const {
        return id;
    }
    string getName() const {
        return name;
    }
    double getPrice() const {
        return price;
    }
    void setID(const int id) {
        this->id = (id > 0) ? id : throw ExceptionHandling();
    }
    void setName(const string name) {
        this->name = (name.length() > 0) ? name : throw ExceptionHandling();
    }
    void setPrice(const double price) {
        this->price = (price > 0) ? price : throw ExceptionHandling();
    }

    virtual void output(){
        cout<<getID()<<"\t"<<setw(42)<<left<<getName()<<"\t$"<<setw(15)<<getPrice();
    }
    virtual void outputHeader() const {
        cout << "ID\tName\t\t\t\t\t\tPrice";
    }
    virtual void input(){
        int id;
        string name;
        double price;

        id=val.enterID();
        setID(id);
        name=val.enterName();
        setName(name);
        price=val.enterPrice();
        setPrice(price);
    }
    virtual void display(){
        cout<<"ID: "<<getID()<<endl;
        cout<<"Name: "<<getName()<<endl;
        cout<<"Price: "<<getPrice()<<"$"<<endl;
    }

    // virtual void printData(std::ostream& output) const {
    //     output << id << ';' << name << ';' << price << ';';
    // }
    // virtual void readData(std::istream& input) {
    //     char semicolon;
    //     input >> id >> semicolon >> name >> semicolon >> price >> semicolon;
    // }
    // friend std::istream& operator>>(std::istream& input, BookAccount& account) {
    //     char semicolon;
    //     input >> account.id >> semicolon >> account.name >> semicolon >> account.price;
    //     return input;
    // }
    // friend std::ostream& operator<<(std::ostream& output, const BookAccount& account) {
    //     output << account.id << ';' << account.name << ';' << account.price;
    //     return output;
    // }
};