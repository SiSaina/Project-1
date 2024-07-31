#pragma once
#include <iostream>
#include <memory>
#include "BookManager.cpp"
#include "BookAccount.cpp"
#include "InputValidation.cpp"
#include "PremiumBookAccount.cpp"
#include "BasicBookAccount.cpp"
#include "LibrarianManager.cpp"
#include "LoginAndRegister.cpp"

using namespace std;

enum {
    ADD = 1,
    OUTPUT,
    UPDATE,
    DELETE,
    SEARCH,
    SORT,
    SAVE,
    LOGOUT,
    EXIT = 0
};

class Application{
private:
    BookManager BM;
    BookAccount* BAAcc{};
    LibrarianManager LM;
    LibrarianAccount* LAAcc{};
    InputValidation val;
    
    void bookMenu(){
        cout<<"==================Book Manager Menu=================="<<endl;
        cout<<"1. Create book information"<<endl;
        cout<<"2. View all book information"<<endl;
        cout<<"3. Update book information"<<endl;
        cout<<"4. Delete book information"<<endl;
        cout<<"5. Search book information"<<endl;
        cout<<"6. Sort book information"<<endl;
        cout<<"7. Save data"<<endl;
        cout<<"8. Back"<<endl;
        cout<<"0. Exit"<<endl;
    }
    void librarianMenu(){
        cout<<"==================Librarian Manager Menu=================="<<endl;
        cout<<"1. Create new account"<<endl;
        cout<<"2. View all account"<<endl;
        cout<<"3. Update account"<<endl;
        cout<<"4. Delete account"<<endl;
        cout<<"5. Search account"<<endl;
        cout<<"6. Sort account information"<<endl;
        cout<<"7. Save data"<<endl;
        cout<<"8. Back"<<endl;
        cout<<"0. Exit"<<endl;
    }
    void menu(){
        cout<<"==================Main Menu=================="<<endl;
        cout<<"1. Book manager"<<endl;
        cout<<"2. Librarian account manager"<<endl;
        cout<<"3. Log out"<<endl;
    }
    void userMenu(){
        cout<<"==================Log in and Register=================="<<endl;
        cout<<"1. Log in"<<endl;
        cout<<"2. Register"<<endl;
        cout<<"0. Exit"<<endl;
    }
public:

    void bookManagement(){
        int choice=0;
        int option=0;

        do{
            bookMenu();
            choice=val.enterChoice();

            switch (choice) {
            case ADD:
                BM.addBookMenu();
                cout<<"Added successfully"<<endl;
                break;
            case OUTPUT:
                BM.viewAllBook();
                break;
            case UPDATE: {
                char choice;
                    do{
                        BM.updateBook(BAAcc);
                        cout<<"Do you want to update again??"<<endl;
                        choice=val.enterYN();
                    }while(choice=='y'||choice=='Y');
                }
                break;
            case DELETE:{
                char choice;
                    do{
                        BM.deleteBook(BAAcc);
                        cout<<"Do you want to delete again??"<<endl;
                        choice=val.enterYN();
                    }while(choice=='y'||choice=='Y');
                }
                break;
            case SEARCH:{
                char choice;
                    do{
                        BM.searchBook(BAAcc);
                        cout<<"Do you want to search again??"<<endl;
                        choice=val.enterYN();
                    }while(choice=='y'||choice=='Y');
                }
                break;
            case SORT:
                BM.sortBook();
                cout<<"Sorted successfully"<<endl;
                break;
            case SAVE:
                cout<<"Save successfully"<<endl;
                // BM.saveBook();
                break;
            case LOGOUT:
                break;
            case EXIT:
                exit(0);
            default:
                cout<<"Error: INVALID INPUT"<<endl;
                break;
            }
        } while(choice!=10&&choice!=8);
    }

    void librarianManagement(){
        int choice=0;
        int option=0;

        do {
            librarianMenu();
            choice=val.enterChoice();

            switch (choice) {
            case ADD:
                LM.addAccount();
                break;
            case OUTPUT:
                LM.viewAllAccount();
                break;
            case UPDATE:{
                char choice;
                do{
                    LM.updateAccount(LAAcc);
                    cout<<"Do you want to update again??"<<endl;
                    choice=val.enterYN();
                }while(choice=='y'||choice=='Y');
                }
                break;
            case DELETE:{
                char choice;
                do{
                    LM.deleteAccount(LAAcc);
                    cout<<"Do you want to delete again??"<<endl;
                    choice=val.enterYN();
                }while(choice=='y'||choice=='Y');
                }
                break;
            case SEARCH:{
                char choice;
                do{
                    LM.searchAccount(LAAcc);
                    cout<<"Do you want to search again??"<<endl;
                    choice=val.enterYN();
                }while(choice=='y'||choice=='Y');
                }
                break;
            case SORT:
                LM.sortAccount(LAAcc);
                break;
            case SAVE:
                cout<<"Save successfully"<<endl;
                //LM.saveAccount();
                break;
            case LOGOUT:
                return;
            case EXIT:
                exit(0);
            default:
                cout<<"Error: INVALID INPUT"<<endl;
                break;
            }
        } while(choice!=10);

    }
    void run(){
        int choice=0;
        int option=0;
        LoginAndRegister log;

        do{
            userMenu();
            choice=val.enterChoice();
            switch (choice) {
            case 1:
                if(log.userLogin()==true){
                    do{
                        menu();
                        option=val.enterChoice();
                        switch (option) {
                        case 1:{
                            //BM.loadBook();
                            bookManagement();   
                            break;
                        }
                        case 2:{
                            //LM.loadAccount();
                            librarianManagement();
                            break;
                        }
                        case 3:
                            break;
                        default:
                            cout<<"Error: INVALID INPUT"<<endl;
                            break;
                        }
                    }while(option!=3);
                }
                break;
            case 2:
                log.userRegister();
                break;
            case 0:
                exit(1);
            default:
                cout<<"Error: INVALID INPUT"<<endl;
                break;
            }
        }while(choice!=0);
    }
    void test(){
        //LM.loadAccount();
        //BM.loadBook();
        //bookManagement();
        //librarianManagement();
    }
};