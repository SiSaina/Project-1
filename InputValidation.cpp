#pragma once
#include <iostream>
#include <string>

using namespace std;

class InputValidation{
private:
    bool validationNum(int num){
        if(cin.fail()||num>1000){
            cin.clear();
            cin.ignore(1000, '\n');
            return false;
        }
        return true;
    }
    bool validationName(string name){
        if(name.length()<0||name.length()>30){
            cin.clear();
            cin.ignore(1000, '\n');
            return false;
        }
        return true;
    }
    bool validationDouble(double dou){
        if(cin.fail()||dou>100000){
            cin.clear();
            cin.ignore(1000, '\n');
            return false;
        }
        return true;
    }
    bool validationShortDouble(double dou){
        if(cin.fail()||dou>100){
            cin.clear();
            cin.ignore(1000, '\n');
            return false;
        }
        return true;
    }
    bool validationYN(char choice) {
        if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
            cin.clear();
            cin.ignore(1000, '\n');
            return false;
        }
        return true;
    }
public:
    int enterID(){
        int id;
        while (true) {
            cout<<"Enter ID(1-999): ";
            cin>>id;
            if(validationNum(id)){
                return id;
            }else{
                cout<<"Error: INPUT ID BETWEEN 1 AND 999"<<endl;
            }
        }
    }
    string enterName(){
        string name;
        while (true) {
            cin.ignore();
            cout<<"Enter name: ";
            getline(cin, name);
            if(validationName(name)){
                return name;
            }else{
                cout<<"Error: INPUT NAME IS INCORRECT"<<endl;
            }
        }
    }
    string enterPass(){
        string pass;
        while (true) {
            cout<<"Enter password: ";
            getline(cin, pass);
            if(validationName(pass)){
                return pass;
            }else{
                cout<<"Error: INPUT PASSWORD IS INCORRECT"<<endl;
            }
        }
    }
    double enterPrice(){
        double price;
        while(true){
            cout<<"Enter price($): ";
            cin>>price;
            if(validationDouble(price)){
                return price;
            }else{
                cout<<"Error: INPUT PRICE IS TOO MUCH"<<endl;
            }
        }
    }
    double enterDC(){
        double DC;
        while(true){
            cout<<"Enter discount percentage(%): ";
            cin>>DC;
            if(validationShortDouble(DC)){
                return DC;
            }else{
                cout<<"Error: INPUT PERCENTAGE IS TOO MUCH"<<endl;
            }
        }
    }
    double enterFee(){
        double fee;
        while(true){
            cout<<"Enter fee($/day): ";
            cin>>fee;
            if(validationShortDouble(fee)){
                return fee;
            }else{
                cout<<"Error: INPUT FEE IS TOO MUCH"<<endl;
            }
        }
    }
    double enterWage(){
        double wage;
        while (true) {
            cout<<"Enter wage($/day): ";
            cin>>wage;
            if(validationDouble(wage)){
                return wage;
            }else{
                cout<<"Error: INPUT WAGE IS TOO MUCH"<<endl;
            }
        }
    }
    int enterChoice(){
        int choice;
        while(true){
            cout<<"Enter choice: ";
            cin>>choice;
            if(validationNum(choice)){
                return choice;
            } else{
                cout<<"Error: PLEASE ENTER THE CHOICE ON THE SCREEN"<<endl;
            }
        }
    }
    char enterYN() {
        char choice;
        while (true) {
            cout << "Enter choice (Y/N): ";
            cin >> choice;
            if (validationYN(choice)) {
                return choice;
            } else {
                cout << "Error: PLEASE ENTER Y OR N" << endl;
            }
        }
    }
};