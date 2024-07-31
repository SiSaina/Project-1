#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "LibrarianAccount.cpp"
#include "InputValidation.cpp"

using namespace std;

class LibrarianManager {
private:
    vector<LibrarianAccount*> LA;
    InputValidation val;

	void findMenu(){
		cout << "==============FIND MENU=============="<<endl;
		cout << "1. Find by ID"<<endl;
		cout << "2. Find by name"<<endl;
        cout << "3. Back to main menu"<<endl;
	}
public:
    ~LibrarianManager(){
        for(auto& acc : LA){
		delete acc;
		}
    }

    void addAccount(){
        cout<<"How many you want to add??"<<endl;
        int time=val.enterChoice();

        for(int i=0; i<time; i++){
            LibrarianAccount* acc = new LibrarianAccount();
            acc->input();
            LA.push_back(acc);
            cout<<"\tAdded successfully"<<endl;
        }

    }

    void viewAllAccount(){
        if (LA.empty()) {
        cout << "No accounts to display." << endl;
        return;
    }
    cout << "----------------------------------------LIBRARIAN ACCOUNT------------------------------------------" << endl;
    cout << "ID" << "\t" << setw(30) << left << "Name" << "\t" << "Wage($/day)" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;
    for (const LibrarianAccount* acc : LA) {
        acc->output();
        cout << endl;
    }
    }

    void updateSingleDetail(LibrarianAccount* acc){
        cout<<"==============UPDATE MENU=============="<<endl;
        cout<<"1. Update ID"<<endl;
        cout<<"2. Update name"<<endl;
        cout<<"3. Update wage"<<endl;
        int choice=val.enterChoice();
        switch (choice) {
        case 1:{
            int id=val.enterID();
            acc->setID(id);
            break;
        }
        case 2:{
            string name=val.enterName();
            acc->setName(name);
            break;
        }
        case 3:{
            double wage=val.enterWage();
            acc->setWage(wage);
            break;
        }
        default:
            cout<<"Error: INVALID INPUT"<<endl;
            break;
        }
    }
    void updateAllDetail(LibrarianAccount* acc){
        cout<<"==============UPDATE MENU=============="<<endl;
		acc->input();
    }
    void updateHandleMenu(LibrarianAccount* acc) {
        cout << "==============UPDATE MENU=============="<<endl;
        cout << "1. Update a single detail"<<endl;
        cout << "2. Update all detail"<<endl;
        int option = val.enterChoice();
            switch (option) {
                case 1:
                    updateSingleDetail(acc);
                    break;
                case 2:
                    updateAllDetail(acc);
                    break;
                default:
                    cout << "Error: INVALID INPUT" << endl;
                    break;
            }
    }
    void updateAccount(LibrarianAccount* acc){
        findMenu();
        int choice=val.enterChoice();
        switch (choice) {
        case 1:{
            int key=val.enterID();

            auto it = find_if(LA.begin(), LA.end(), [key](const LibrarianAccount* acc) 
            { return acc->getID() == key;});

            if (it != LA.end()) {
				updateHandleMenu(*it);
                cout<<"Updated successfully"<<endl;
			} else {
				cout << "Not found" << endl;
			}
            break;
        }
        case 2:{
            string key=val.enterName();

            auto it = find_if(LA.begin(), LA.end(), [key](const LibrarianAccount* acc) 
            { return acc->getName() == key;});

            if (it != LA.end()) {
				updateHandleMenu(*it);
                cout<<"Updated successfully"<<endl;
			} else {
				cout << "Not found" << endl;
			}
            break;
        }
        case 3:
            break;
        default:
            cout<<"Error: INVALID INPUT"<<endl;
            break;
        }
    }

    void deleteAccount(LibrarianAccount* acc){
        findMenu();
        int choice=val.enterChoice();
        switch (choice) {
        case 1:{
            int key=val.enterID();

            auto it=find_if(LA.begin(), LA.end(), [key](const LibrarianAccount* acc) {return acc->getID() == key;});
			if(it!=LA.end()){
				cout<<"Book information will be deleted"<<endl;
				(*it)->display();
				cout<<"Are you sure you want to delete it?? "<<endl;
				char choice=val.enterYN();
				
				if(choice=='y'||choice=='Y'){
					auto iter=find(LA.begin(), LA.end(), acc);
					LA.erase(it);
                    cout<<"Deleted successfully"<<endl;
				}else{
					cout<<"Deletion canceled"<<endl;
				}
			}else{
				cout<<"Not found"<<endl;
			}
			break;
        }
        case 2:{
            string key=val.enterName();

			auto it=find_if(LA.begin(), LA.end(), [key](const LibrarianAccount* acc) {return acc->getName() == key;});
			if(it!=LA.end()){
				cout<<"Book information will be deleted"<<endl;
				(*it)->display();
				cout<<"Are you sure you want to delete it?? ";
				char choice=val.enterYN();
				
				if(choice=='y'||choice=='Y'){
					auto iter=find(LA.begin(), LA.end(), acc);
					LA.erase(it);
                    cout<<"Deleted successfully"<<endl;
				}else{
					cout<<"Deletion canceled"<<endl;
				}
			}else{
				cout<<"Not found"<<endl;
			}
			break;
        }
        case 3:
            break;
        default:
            cout<<"Error: INVALID INPUT"<<endl;
            break;
        }
    }
    void searchAccount(LibrarianAccount* acc){
        findMenu();
		int choice=val.enterChoice();

		switch (choice) {
		case 1:{
			int key=val.enterID();

			auto it=find_if(LA.begin(), LA.end(), [key](const LibrarianAccount* acc) {return acc->getID() == key;});
			if(it!=LA.end()){
				cout << "==============BOOK INFORMATION=============="<<endl;
				(*it)->display();
			}else{
				cout<<"Not found"<<endl;
			}
			break;
		}
		case 2:{
			string key=val.enterName();

			auto it=find_if(LA.begin(), LA.end(), [key](const LibrarianAccount* acc) {return acc->getName() == key;});
			if(it!=LA.end()){
				cout << "==============BOOK INFORMATION=============="<<endl;
				(*it)->display();
			}else{
				cout<<"Not found"<<endl;
			}
			break;
		}
        case 3:
            break;
		default:
			cout<<"Error: INVALID INPUT"<<endl;
			break;
		}
	}
    void sortAccount(LibrarianAccount* acc){
        cout<<"==============SORT MENU=============="<<endl;
		cout<<"1. Sort by ID"<<endl;
		cout<<"2. Sort by name"<<endl;
        cout<<"3. Back to main menu"<<endl;
		int choice=val.enterChoice();

		switch (choice) {
		case 1:{
			cout<<"==============SORT MENU=============="<<endl;
			cout<<"1. Ascending"<<endl;
			cout<<"2. Descending"<<endl;
			int option=val.enterChoice();

			switch (option) {
			case 1:
				sort(LA.begin(), LA.end(), [](const LibrarianAccount* a, const LibrarianAccount* b) { return a->getID() < b->getID();});
				break;
			case 2:
				sort(LA.begin(), LA.end(), [](const LibrarianAccount* a, const LibrarianAccount* b) { return a->getID() > b->getID();});
				break;
			default:
				cout<<"Error: INVALID INPUT"<<endl;
				break;
			}
			break;
		}
		case 2:{
			cout<<"==============SORT MENU=============="<<endl;
			cout<<"1. Ascending"<<endl;
			cout<<"2. Descending"<<endl;
			int option=val.enterChoice();

			switch (option) {
			case 1:
				sort(LA.begin(), LA.end(), [](const LibrarianAccount* a, const LibrarianAccount* b) { return a->getName() < b->getName();});
				break;
			case 2:
				sort(LA.begin(), LA.end(), [](const LibrarianAccount* a, const LibrarianAccount* b) { return a->getName() > b->getName();});
				break;
			default:
				cout<<"Error: INVALID INPUT"<<endl;
				break;
			}
			break;
		}
        case 3:
            break;
		default:
			cout<<"Error: INVALID INPUT"<<endl;
			break;
		}
    }

    void saveAccount() {
        ofstream outputFile("Librarian account.dat");
        if (!outputFile.is_open()) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        for(const auto& it : LA){
            outputFile  << it->getID() << ";"
                        << it->getName() << ";"
                        << it->getWage() << endl;
        }
        outputFile.close();
        cout << "Data saved successfully." << endl;
    }

    void loadAccount() {
        ifstream inputFile("Librarian account.dat");
        if (!inputFile.is_open()) {
            cerr << "Error opening file for reading." << endl;
            return;
        }

        inputFile.read(reinterpret_cast<char*>(this), sizeof(*this));

        inputFile.close();
        cout << "Data loaded successfully." << endl;
    }

};