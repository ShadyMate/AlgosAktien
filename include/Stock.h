#ifndef STOCK_H
#define STOCK_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct StockVal {
    string date;
    double open;
    double high;
    double low;
    double close;
    int volume;
    double adj_close;
};

class Stock {
    public:
        Stock(string name, string wkn, string acro);
        string getName();
        string getWkn();
        string getAcro();
        vector<StockVal>& getStockVal();
        void importCSVData(const string& filename, vector<StockVal>& stockVectorData);
        void setStockArguments(string name, string wkn, string acro);
        void displayLatestStockVal(Stock* stock);
        Stock createStock();
        StockVal parseCSVLine(const string& line);
        string serialize();
        Stock deserialize(const string& data);
        ~Stock();

    private:
        string name;
        string wkn; // Wertpapierkennnummer (WKN)
        string acro; // acronym for the stock
        vector<StockVal> stockValVector; // Kursdaten der letzten 30 Tage
};

#endif // STOCK_H
