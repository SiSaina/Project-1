#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>
#include "BookAccount.cpp"
#include "InputValidation.cpp"
#include "PremiumBookAccount.cpp"
#include "BasicBookAccount.cpp"
#include "BookDAO.cpp"

using namespace std;

class BookManager : public BookDAO {
private:
	vector<BookAccount*> BA;
	InputValidation val;

	void findMenu(){
		cout << "==============FIND MENU=============="<<endl;
		cout << "1. Find by ID"<<endl;
		cout << "2. Find by name"<<endl;
	}
	void bookTypeMenu(){
		cout << "==============CHOOSE BOOK TYPE=============="<<endl;
		cout << "1. Premium book"<<endl;
		cout << "2. Basic book"<<endl;
		cout << "3. Back"<<endl;
	}
public:
	~BookManager(){
		for(auto& acc : BA){
			delete acc;
		}
	}

	void addBook(BookAccount* BA){
		this->BA.push_back(BA);
	}
	void addBookMenu() {
		bookTypeMenu();
        int choice = val.enterChoice();

        switch (choice) {
            case 1: {
				cout<<"How many time you want to add??"<<endl;
				int time=val.enterChoice();
				for(int i=0; i<time;i++){
					auto premiumBookAccount = make_unique<PremiumBookAccount>();
					premiumBookAccount->input();
					addBook(premiumBookAccount.release());
					cout<<"\tAdded successfully"<<endl;
				}
                break;
            }
            case 2: {
				cout<<"How many time you want to add"<<endl;
				int time=val.enterChoice();
				for(int i=0; i<time;i++){
					auto basicBookAccount = make_unique<BasicBookAccount>();
					basicBookAccount->input();
					addBook(basicBookAccount.release());
					cout<<"\tAdded successfully"<<endl;
				}
                break;
            }
			case 3:
				break;
            default:
                cout << "Error: INVALID INPUT" << endl;
                break;
        }
    }
	
	void viewAllBook() {
		bookTypeMenu();
		int choice = val.enterChoice();
		switch (choice) {
			case 1:
				viewAllBooksFunction<PremiumBookAccount>(BA);
				break;
			case 2:
				viewAllBooksFunction<BasicBookAccount>(BA);
				break;
			case 3:
				break;
			default:
				cout << "Error: INVALID INPUT" << endl;
				break;
		}
	}
	template <typename BookType>
	void viewAllBooksFunction(const vector<BookAccount*>& acc) {
    bool print = false; 
    for (const auto& it : acc) {
        if (typeid(*it) == typeid(BookType)) {
            if (!print) {
                it->outputHeader();
                print = true;
            }
            it->output();
            cout << endl;
        }
    }
	}

	void updateSingleDetail(BookAccount* acc){
		cout<<"==============UPDATE MENU=============="<<endl;
		cout<<"1. Update ID"<<endl;
		cout<<"2. Update name"<<endl;
		cout<<"3. Update price"<<endl;
    	if (PremiumBookAccount* premiumAccount = dynamic_cast<PremiumBookAccount*>(acc)) {
        cout << "4. Update discount percentage" << endl;
    	} else if (BasicBookAccount* basicAccount = dynamic_cast<BasicBookAccount*>(acc)) {
        cout << "4. Update fee" << endl;
    	}

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
				double price=val.enterPrice();
				acc->setPrice(price);
				break;
			}
			case 4:{
				if (PremiumBookAccount* premiumAccount = dynamic_cast<PremiumBookAccount*>(acc)) {
					double DC = val.enterDC();
					premiumAccount->setDC(DC);
				} else if (BasicBookAccount* basicAccount = dynamic_cast<BasicBookAccount*>(acc)) {
					double fee = val.enterFee();
					basicAccount->setFee(fee);
				}
				break;
			}
			default:
				cout<<"Error: INVALID INPUT"<<endl;
				break;
			}
	}
	void updateAllDetail(BookAccount* acc){
		cout<<"==============UPDATE MENU=============="<<endl;
		acc->input();
	}
	void updateHandleMenu(BookAccount* acc) {
    cout << "==============UPDATE MENU==============\n";
    cout << "1. Update a single detail\n";
    cout << "2. Update all detail\n";
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
	template <typename BookType>
	void updateBookByType(BookAccount* acc) {
		findMenu();
    	int choice = val.enterChoice();

    switch (choice) {
        case 1: {
            int key = val.enterID();

            auto it = find_if(BA.begin(), BA.end(), [key](const BookAccount* acc) {
                const BookType* derivedAcc = dynamic_cast<const BookType*>(acc);
                return derivedAcc ? derivedAcc->getID() == key : false;
            });
			if (it != BA.end()) {
				updateHandleMenu(*it);
			} else {
				cout << "Not found" << endl;
			}

            break;
        }
        case 2: {
            string key = val.enterName();

            auto it = find_if(BA.begin(), BA.end(), [key](const BookAccount* acc) {
                const BookType* derivedAcc = dynamic_cast<const BookType*>(acc);
                return derivedAcc ? derivedAcc->getName() == key : false;
            });
			if (it != BA.end()) {
				updateHandleMenu(*it);
			} else {
				cout << "Not found" << endl;
			}

            break;
        }
        default:
            cout << "Error: INVALID INPUT" << endl;
            break;
    }
	}
	void updateBook(BookAccount* acc) {
		bookTypeMenu();
		int choice = val.enterChoice();

		switch (choice) {
		case 1: {
			updateBookByType<PremiumBookAccount>(acc);
			cout<<"Updated successfully"<<endl;
			break;
		}
		case 2: {
			updateBookByType<BasicBookAccount>(acc);
			cout<<"Updated successfully"<<endl;
			break;
		}
		case 3:
			break;
		default:
			cout << "Error: INVALID INPUT" << endl;
			break;
		}
	}

	template <typename BookType>
	void deleteBookByType(BookAccount* acc) {
		findMenu();
		int choice = val.enterChoice();

		switch (choice) {
		case 1:{
			int key=val.enterID();

            auto it = find_if(BA.begin(), BA.end(), [key](const BookAccount* acc) {
                return dynamic_cast<const BookType*>(acc) != nullptr && acc->getID() == key;
            });
			if(it!=BA.end()){
				cout<<"Book information will be deleted"<<endl;
				(*it)->display();
				cout<<"Are you sure you want to delete it?? "<<endl;
				char choice=val.enterYN();
				
				if(choice=='y'||choice=='Y'){

					BA.erase(it);
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

            auto it = find_if(BA.begin(), BA.end(), [key](const BookAccount* acc) {
                return dynamic_cast<const BookType*>(acc) != nullptr && acc->getName() == key;
            });
			if(it!=BA.end()){
				cout<<"Book information will be deleted"<<endl;
				(*it)->display();
				cout<<"Are you sure you want to delete it?? ";
				char choice=val.enterYN();
				
				if(choice=='y'||choice=='Y'){
					BA.erase(it);
					cout<<"Deleted successfully"<<endl;
				}else{
					cout<<"Deletion canceled"<<endl;
				}
			}else{
				cout<<"Not found"<<endl;
			}
			break;
		}
		default:
			cout<<"Error: INVALID INPUT"<<endl;
			break;
		}
	}
	void deleteBook(BookAccount* acc){
		bookTypeMenu();
		int choice = val.enterChoice();

		switch (choice) {
			case 1: {
				deleteBookByType<PremiumBookAccount>(acc);
				break;
			}
			case 2: {
				deleteBookByType<BasicBookAccount>(acc);
				break;
			}
			case 3:
				break;
			default:
				cout << "Error: INVALID INPUT" << endl;
				break;
		}
	}

	template <typename BookType>
	void searchBookByType(BookAccount* acc){
		findMenu();
		int choice=val.enterChoice();

		switch (choice) {
		case 1:{
			int key=val.enterID();

            auto it = find_if(BA.begin(), BA.end(), [key](const BookAccount* acc) {
                return dynamic_cast<const BookType*>(acc) != nullptr && acc->getID() == key;
            });
			if(it!=BA.end()){
				cout << "==============BOOK INFORMATION=============="<<endl;
				(*it)->display();
			}else{
				cout<<"Not found"<<endl;
			}
			break;
		}
		case 2:{
			string key=val.enterName();

            auto it = find_if(BA.begin(), BA.end(), [key](const BookAccount* acc) {
                return dynamic_cast<const BookType*>(acc) != nullptr && acc->getName() == key;
            });
			if(it!=BA.end()){
				cout << "==============BOOK INFORMATION=============="<<endl;
				(*it)->display();
			}else{
				cout<<"Not found"<<endl;
			}
			break;
		}
		default:
			cout<<"Error: INVALID INPUT"<<endl;
			break;
		}
	}
	void searchBook(BookAccount* acc){
		bookTypeMenu();
		int choice = val.enterChoice();

		switch (choice) {
			case 1: {
				searchBookByType<PremiumBookAccount>(acc);
				cout<<"Searched successfully"<<endl;
				break;
			}
			case 2: {
				searchBookByType<BasicBookAccount>(acc);
				cout<<"Searched successfully"<<endl;
				break;
			}
			case 3:
				break;
			default:
				cout << "Error: INVALID INPUT" << endl;
				break;
		}
	}
	
	void sortBook(){
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
				sort(BA.begin(), BA.end(), [](const BookAccount* a, const BookAccount* b) { return a->getID() < b->getID();});
				break;
			case 2:
				sort(BA.begin(), BA.end(), [](const BookAccount* a, const BookAccount* b) { return a->getID() > b->getID();});
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
				sort(BA.begin(), BA.end(), [](const BookAccount* a, const BookAccount* b) { return a->getName() < b->getName();});
				break;
			case 2:
				sort(BA.begin(), BA.end(), [](const BookAccount* a, const BookAccount* b) { return a->getName() > b->getName();});
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

// void saveBook() {
//     ofstream premiumFile("PremiumBook.dat", ios::out);
//     ofstream basicFile("BasicBook.dat", ios::out);
//     if (!premiumFile.is_open() || !basicFile.is_open()) {
//         cout << "Error in creating files...\n";
//         exit(1);
//     } else {
//         for (const auto& accountPtr : BA) {
//             if (typeid(*accountPtr) == typeid(PremiumBookAccount)) {
//                 premiumFile << 'P';
//                 premiumFile << *dynamic_cast<PremiumBookAccount*>(accountPtr);
//             } else if (typeid(*accountPtr) == typeid(BasicBookAccount)) {
//                 basicFile << 'B';
//                 basicFile << *dynamic_cast<BasicBookAccount*>(accountPtr);
//             }
//         }
//         cout << "Files saved successfully" << endl;
//     }
//     premiumFile.close();
//     basicFile.close();
// }

// void loadBook() {
//     ifstream premiumFile("PremiumBook.dat", ios::in);
//     ifstream basicFile("BasicBook.dat", ios::in);
//     if (!premiumFile.is_open() || !basicFile.is_open()) {
//         cout << "Error in opening files...\n";
//         exit(1);
//     }
//     try {
//         loadFromFile(premiumFile, 'P'); // Load PremiumBookAccount data
//         loadFromFile(basicFile, 'B');   // Load BasicBookAccount data
//     } catch (const std::exception& e) {
//         cerr << "Exception: " << e.what() << endl;
//     }
//     premiumFile.close();
//     basicFile.close();
// }
// void loadFromFile(ifstream& file, char accountType) {
//     while (file.peek() != EOF) {
//         char storedType;
//         file >> storedType;
//         if (storedType == accountType) {
//             BookAccount* acc;
//             if (accountType == 'P') {
//                 acc = new PremiumBookAccount();
//             } else if (accountType == 'B') {
//                 acc = new BasicBookAccount();
//             }
//             if (file >> *acc) {
//                 // Assuming addBook() function handles polymorphism correctly
//                 addBook(acc);
//                 cout << "Record loaded successfully" << endl;
//             } else {
//                 cerr << "Error reading account data. Skipping record." << endl;
//                 delete acc;  // Clean up memory
//             }
//         } else {
//             cerr << "Unexpected account type in file. Skipping record." << endl;
//             // Skip the rest of the record
//             file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//         }
//     }
// }

	
};