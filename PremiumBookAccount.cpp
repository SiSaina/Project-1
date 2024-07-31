#pragma once
#include <iostream>
#include "BookAccount.cpp"
#include "InputValidation.cpp"

using namespace std;

class PremiumBookAccount : public BookAccount {
private:
    double discountPercentage;
public:
    PremiumBookAccount() : BookAccount(), discountPercentage(0) {};
    PremiumBookAccount(int id, string name, double price, double discountPercentage) : BookAccount(id, name, price){
        setDC(discountPercentage);
    }

    double getDC() const {
        return discountPercentage;
    }
    void setDC(const double discountPercentage){
        this->discountPercentage = (discountPercentage > 0) ? discountPercentage : throw ExceptionHandling();
    }

    void input(){
        BookAccount::input();
        double DC=val.enterDC();
        setDC(DC);
    }
    void output(){
        BookAccount::output();
        cout<<getDC()<<"%";
    }
    void outputHeader() const override{
        cout << "----------------------------------------PREMUIM BOOK---------------------------------------"<<endl;
        BookAccount::outputHeader(); 
        cout<<"\t\tDiscount percentage" << endl;
        cout << "-------------------------------------------------------------------------------------------"<<endl;
    }
    void display(){
        BookAccount::display();
        cout<<"Discount percentage: "<<getDC()<<"%"<<endl;
    }

    // void printData(std::ostream& output) const override {
    //     BookAccount::printData(output);
    //     output << discountPercentage << std::endl;
    // }
    // void readData(std::istream& input) override {
    //     BookAccount::readData(input);
    //     input >> discountPercentage;
    // }
    // friend std::istream& operator>>(std::istream& is, PremiumBookAccount& obj) {
    //     is >> static_cast<BookAccount&>(obj);
    //     is >> obj.discountPercentage;
    //     return is;
    // }
    // friend std::ostream& operator<<(std::ostream& output, const PremiumBookAccount& account) {
    //     output << static_cast<const BookAccount&>(account);
    //     output << ';' << account.discountPercentage;
    //     return output;
    // }
};