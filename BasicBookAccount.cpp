#pragma once
#include <iostream>
#include "BookAccount.cpp"


using namespace std;

class BasicBookAccount : public BookAccount {
private:
    double fee;
public:
    BasicBookAccount() : BookAccount(), fee(0) {};
    BasicBookAccount(int id, string name, double price, double fee) : BookAccount(id, name, price){
        setFee(fee);
    }

    double getFee() const {
        return fee;
    }
    void setFee(const double fee){
        this->fee = (fee > 0) ? fee : throw ExceptionHandling();
    }

    void input(){
        BookAccount::input();
        double fee=val.enterFee();
        setFee(fee);
    }
    void output(){
        BookAccount::output();
        cout<<getFee()<<"$/day";
    }
    void outputHeader() const override {
        cout << "----------------------------------------BASIC BOOK-----------------------------------------"<<endl;
        BookAccount::outputHeader();
        cout << "\t\tFee" << endl;
        cout << "-------------------------------------------------------------------------------------------" << endl;
    }
    void display(){
        BookAccount::display();
        cout<<"Fee: "<<getFee()<<"$/day"<<endl;
    }

    // void printData(std::ostream& output) const override {
    //     BookAccount::printData(output);
    //     output << fee << std::endl;
    // }
    // void readData(std::istream& input) override {
    //     BookAccount::readData(input);
    //     input >> fee;
    // }
    // friend std::istream& operator>>(std::istream& is, BasicBookAccount& obj) {
    //     is >> static_cast<BookAccount&>(obj);
    //     is >> obj.fee;
    //     return is;
    // }
    // friend std::ostream& operator<<(std::ostream& output, const BasicBookAccount& account) {
    //     output << static_cast<const BookAccount&>(account);
    //     output << ';' << account.fee;
    //     return output;
    // }
};