#ifndef HASH_H
#define HASH_H

#include<Stock.h>
#include <string>

using namespace std;

class Hash
{
    public:
        Hash(int size, int count);


        int getSize();
        int getCount();
        void setSize(int size);
        void setCount(int count);
        int hashFunction(string key);
        void deleteTable(Hash* table);
        Stock* getStock(string key);
        void createHashItem(string name, string WKN, string acro, Hash* acroHashTable);
        void populateHashItem(string name);
        void deleteHashItem(string name, Hash* acroHashTable);
        void displayLatestHashData(string name);
        void getCloseValues(string name);
        void drawPlot(vector<double> closePrices);
        int checkForCollision(string key, int index);
        void saveToFile(const string& filename, Hash* acroHashTable);
        void loadFromFile(const string& filename, Hash* acroHashTable);
        void deleteAllEntries();
        Stock* getStockByName(string name);
        Stock* getStockByAcro(string acro);
        int acroHashFunction(string acro);
        ~Hash();




    private:
        int size;
        int count;
        Stock** item;

};



#endif // HASH_H
