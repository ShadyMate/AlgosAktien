#include "Hash.h"
#include "Stock.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#define CAPACITY 1000;


Hash::Hash(int size, int count){
    this->size = size;
    this->count = count;
    this->item = new Stock*[size];
    for (int i = 0; i < size; i++)
    {
        this->item[i] = nullptr;
    }
}

int Hash::getSize(){
    return size;
}

int Hash::getCount(){
    return count;
}

void Hash::setSize(int size){
    this->size = size;
}

void Hash::setCount(int count){
    this->count = count;
}

Stock* Hash::getStock(string key){
    int index = hashFunction(key);
    return item[index];
}

int Hash::hashFunction(string key){
    int hash = 0;
    int index;

    for (int i = 0; i < key.length(); i++)
    {
        hash = hash + (int)key[i];
    }

    index = hash % size;

    return index;
}

int Hash::acroHashFunction(string acro) {
    int hash = 0;
    for (int i = 0; i < acro.length(); i++) {
        hash = (hash * 31 + acro[i]) % size;
    }
    return hash;
}

void Hash::deleteTable(Hash* table) {
    for (int i = 0; i < table->size; i++)
    {
        delete table->item[i];
        table->item[i] = nullptr;
    }
    delete[] table->item;
    delete table;

    cout << "Hash table was deleted!" << endl;
}

void Hash::createHashItem(string name, string WKN, string acro, Hash* acroHashTable) {
    
    int index = checkForCollision(name, hashFunction(name));

    if (index == -1) {
        cout << "Hash table is full. Cannot add new stock." << endl;
        return;
    }
    if (this->item[index] != nullptr)
    {
        cout << "Stock item " << name << " already exists" << endl;
        return;
    }

    Stock* newStock = new Stock(name, WKN, acro);
    item[index] = newStock;
    int acroIndex = acroHashTable->checkForCollision(acro, acroHashTable->acroHashFunction(acro));
    acroHashTable->item[acroIndex] = newStock; // Add to the acronym hash table
    setCount(getCount()+1);

    cout << "Stock item " << name << " was successfully created" << endl;
}

void Hash::deleteHashItem(string name, Hash* acroHashTable) {
    // Calculate the hash value for the given name
    int index = hashFunction(name);

    // Search for the item in the hash table
    while (item[index] != nullptr)
    {
        // Check if the item's name matches the given name
        if (item[index]->getName() == name)
        {
            // Get the acronym before deleting the item
            string acro = item[index]->getAcro();

            // Delete the item
            delete item[index];
            item[index] = nullptr;

            // Remove the item from the acronym hash table and the name hashtable
            int acroIndex = acroHashTable->acroHashFunction(acro);
            acroHashTable->item[acroIndex] = nullptr;
            setCount(getCount()-1);

            cout << "The item \""<< name << "\" has been deleted." << endl;
            return;
        }

        // Move to the next index
        index = (index + 1) % size;
    }

    cout << "The item was not found." << endl;
}


void Hash::populateHashItem(string name){
    int index = hashFunction(name);
    Stock* stock = item[index];
    if (stock == nullptr)
    {
        cout << "Stock item " << name << " not found" << endl;
        return;
    }

    string userPath;
    cout << "Please enter the path\\to\\your\\file.csv: ";
    cin >> userPath;
    stock->importCSVData(userPath, stock->getStockVal());
}

Stock* Hash::getStockByName(string name) {
    int index = hashFunction(name);
    Stock* stock = item[index];
    if (stock == nullptr){
        cout << "Stock item " << name << " was not found" << endl;
        return nullptr;
    }
    return stock;
}

Stock* Hash::getStockByAcro(string acro) {
    int index = acroHashFunction(acro);
    Stock* stock = item[index];
    if (stock == nullptr){
        cout << "Stock item " << acro << " was not found" << endl;
        return nullptr;
    }
    return stock;
}

int Hash::checkForCollision(string key, int index){
    for(int i = 0;i < this->size;i++){
        int newIndex = (index + i*i) % this->size;
        if (item[newIndex] == nullptr || item[newIndex]->getName() == key)
        {
            return newIndex;
        }
    }

    cout << "The hash table is full!" << endl;
    return -1;
}

void Hash::getCloseValues(string name){
    int index = hashFunction(name);
    Stock* stock = item[index];
    if (stock == nullptr)
    {
        cout << "Stock item " << name << " not found" << endl;
        return;
    }

    // Check if there are enough entries
    if (stock->getStockVal().size() < 30)
    {
        cout << "Not enough data to plot." << endl;
        return;
    }

    vector<double> closePrices;
    // Change the integer to whatever value you need
    int start = stock->getStockVal().size() > 30 ? stock->getStockVal().size() - 30 : 0;
    for (int i = stock->getStockVal().size() - 1; i >= start; i--) {
        closePrices.push_back(stock->getStockVal()[i].close);
    }
    drawPlot(closePrices);
}

void Hash::drawPlot(vector<double> closePrices){
    double minValue = *min_element(closePrices.begin(), closePrices.end());

    for (double price : closePrices)
    {
        // Calculate the height relative to the min value
        int height = static_cast<int>(price - minValue);
        cout << price << "\t|";

        for (int i = 0; i < height; i++)
        {
            cout << " ";
        }
        cout << "X" << endl;
    }
}
void Hash::saveToFile(const string& filename, Hash* acroHashTable){
    ofstream file;
    file.open(filename);

    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return;
    }

    for (int i = 0; i < this->size; i++)
    {
        Stock* stock = this->item[i];
        if (stock != nullptr) // Check if the slot in the hash table is not empty
        {
            int acroIndex = acroHashTable->acroHashFunction(stock->getAcro());
            file << i << "," << acroIndex << "," << stock->serialize() << endl;
        }
    }

    file.close();
}

void Hash::deleteAllEntries(){
    for (int i = 0; i < size; i++) {
        if (item[i] != nullptr) {
            delete item[i];
            item[i] = nullptr;
        }
    }
}

void Hash::loadFromFile(const string& filename, Hash* acroHashTable){
    //to clear hash table before loading new data
    deleteAllEntries();

    ifstream file;
    file.open(filename);

    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        string indexStr;
        string acroIndexStr;
        string serializedStock;

        // Create an istringstream object to read from the line
        istringstream ss(line);

        // Get the index and serialized stock from the line
        getline(ss, indexStr, ',');
        getline(ss, acroIndexStr, ',');
        getline(ss, serializedStock); // Read the rest of the line

        // Convert the indices to integers
        int index = stoi(indexStr);
        int acroIndex = stoi(acroIndexStr);

        // Create a new Stock object from the serialized data
        Stock* stock = new Stock("", "", "");
        *stock = stock->deserialize(serializedStock);

        // Add the stock to the hash tables at the correct indices
        item[index] = stock;
        acroHashTable->item[acroIndex] = stock;
    }

    file.close();
}
