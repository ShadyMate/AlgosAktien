#include <iostream>
#include <Stock.h>
#include <Hash.h>
#include <string>
#include <limits>

using namespace std;


string getUserString(int number){
    string input = "0";
    switch(number)
    {
    case 1:
        cout << "Enter the name: ";
        cin >> input;
        return input;
    case 2:
        cout << "Enter the WKN: ";
        cin >> input;
        return input;
    case 3:
        cout << "Enter the acronym: ";
        cin >> input;
        return input;
    }
    return input;
}

int actionInput() {
    string input;
    cin >> input;

    try {
        // Convert string to integer
        int userNumber = stoi(input);
        return userNumber;
    } catch (invalid_argument& ia) { // Catch invalid argument exception
        cout << "Number is invalid, try again." << endl;
        cin.clear(); // Clear the error state of the stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
    }

    return 0; // Return a default value
}

string getStockName(){
    cout << "Enter the stock name: ";
    string input;
    cin >> input;
    return input;
}

string getStockAcro(){
    cout << "Enter the stock acronym: ";
    string input;
    cin >> input;
    return input;
}

void actionMenu(){
    cout << "------------------------------------------"<< endl;
    cout << "|          1: Add a stock item           |"<< endl;
    cout << "|        2: Delete a stock item          |"<< endl;
    cout << "|    3: Import csv data for stock item   |"<< endl;
    cout << "|       4: Search for a stock item       |"<< endl;
    cout << "|       5: Plot the last stock item      |"<< endl;
    cout << "|      6: Save hash table into a file    |"<< endl;
    cout << "|       7: Load hash table from file     |"<< endl;
    cout << "|           8: Quit application          |"<< endl;
    cout << "------------------------------------------"<< endl;
    cout << "Enter your number: ";
}

void userAction(int input, Hash* hashTable, Hash* acroHashTable) {
    string name;
    string WKN;
    string acro;
    string filename;

    switch(input) {
    case 1: // add stock item
        name = getUserString(1);
        WKN = getUserString(2);
        acro = getUserString(3);
        hashTable->createHashItem(name, WKN, acro, acroHashTable);
        break;
    case 2: // delete stock item
        hashTable->deleteHashItem(getStockName(),acroHashTable);
        break;
    case 3: // import csv data
        hashTable->populateHashItem(getStockName());
        break;
    case 4: // search stock item
            cout << "Search by (1) Name or (2) Acronym? ";
            int choice;
            try{
                cin >> choice;
            }catch (invalid_argument& ia){ // Catch invalid argument exception
                cout << "Not a valid Input, try again." << endl;
                break;
            }
            if (choice == 1) {
                name = getStockName();
                Stock* stock = hashTable->getStockByName(name);
                if (stock != nullptr) {
                    cout << "\nName: " << stock->getName() << "\nAcronym: " << stock->getAcro() << "\nWKN: " << stock->getWkn() << "\n\n";
                    stock->displayLatestStockVal(stock);
                }
            } else if (choice == 2) {
                acro = getStockAcro();
                Stock* stock = acroHashTable->getStockByAcro(acro);
                if (stock != nullptr) {
                    cout << "\nName: " << stock->getName() << "\nAcronym: " << stock->getAcro() << "\nWKN: " << stock->getWkn() << "\n\n";
                    stock->displayLatestStockVal(stock);
                }
            }
            break;
    case 5: // plot stock item
        hashTable->getCloseValues(getStockName());
        break;
    case 6: // save hashtable
        cout << "Enter Filename to save Hashtable in: ";
        cin >> filename;
        hashTable->saveToFile(filename, acroHashTable);
        break;
    case 7: // load hashtable
        cout << "Enter Filename to load Hashtable from: ";
        cin >> filename;
        hashTable->loadFromFile(filename, acroHashTable);
        break;
    case 8: // quit
        hashTable->deleteTable(hashTable);
        cout << "Was I not good enough? :(" << endl;
        break;
    default:
        cout << "For the love of God, 1-8.. nothing else pls!" << endl;
        break;
    }

}



int main(){
    int input = 0;
    Hash* hashTable = new Hash(1000, 0);
    Hash* acroHashTable = new Hash(1000, 0);

    while(input != 8 && input >= 0 && input <= 7) {
        actionMenu();
        input = actionInput();
        system("CLS");
        userAction(input, hashTable, acroHashTable);
    }
    delete hashTable;
    delete acroHashTable;
    return 0;
}

Hash::~Hash(){

}
