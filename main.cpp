#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include "yahoo_finance.h"

using namespace std;

struct StockData {
    string date;
    double open;
    double high;
    double low;
    double close;
    double volume;
    double adjClose;
};

class StockManager {
private:
    unordered_map<string, vector<StockData>> stockTable;

public:
    void addStock(const string& name, const string& wkn, const string& symbol) {
        // Assume stock is not already present
        stockTable[symbol] = vector<StockData>();
    }

    void deleteStock(const string& symbol) {
        stockTable.erase(symbol);
    }

    void importData(const string& symbol, const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }

        string line;
        // Skipping header line
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string date;
            double open, high, low, close, volume, adjClose;
            getline(ss, date, ',');
            ss >> open >> high >> low >> close >> volume >> adjClose;

            stockTable[symbol].push_back({date, open, high, low, close, volume, adjClose});
        }

        file.close();
    }

    void searchStock(const string& query) {
        auto it = stockTable.find(query);
        if (it != stockTable.end()) {
            const auto& data = it->second.back();
            cout << "Latest data for stock " << query << ":" << endl;
            cout << "Date: " << data.date << endl;
            cout << "Open: " << data.open << endl;
            cout << "High: " << data.high << endl;
            cout << "Low: " << data.low << endl;
            cout << "Close: " << data.close << endl;
            cout << "Volume: " << data.volume << endl;
            cout << "Adj Close: " << data.adjClose << endl;
        } else {
            cout << "Stock " << query << " not found." << endl;
        }
    }

    void plotStock(const string& symbol) {
        cout << "Plotting stock data for " << symbol << ":" << endl;
        for (const auto& data : stockTable[symbol]) {
            cout << data.date << " | ";
            // Here you can implement your own ASCII plot logic
            cout << "Close: " << data.close << endl;
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (const auto& pair : stockTable) {
            file << pair.first << ",";
            for (const auto& data : pair.second) {
                file << data.date << "," << data.open << "," << data.high << "," << data.low << ","
                     << data.close << "," << data.volume << "," << data.adjClose << endl;
            }
        }
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }

        stockTable.clear();
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string symbol;
            getline(ss, symbol, ',');
            string date;
            double open, high, low, close, volume, adjClose;
            while (getline(ss, date, ',')) {
                ss >> open >> high >> low >> close >> volume >> adjClose;
                stockTable[symbol].push_back({date, open, high, low, close, volume, adjClose});
            }
        }

        file.close();
    }
};

int main() {
    StockManager stockManager;
    int choice;
    string symbol, filename;

    do {
        cout << "\nMenu:\n1. ADD\n2. DEL\n3. IMPORT\n4. SEARCH\n5. PLOT\n6. SAVE <filename>\n7. LOAD <filename>\n8. FETCH DATA FROM YAHOO FINANCE\n9. QUIT\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter stock name, WKN, and symbol: ";
                string name, wkn;
                cin >> name >> wkn >> symbol;
                stockManager.addStock(name, wkn, symbol);
                break;
            }
            case 2: {
                cout << "Enter stock symbol to delete: ";
                cin >> symbol;
                stockManager.deleteStock(symbol);
                break;
            }
            case 3: {
                cout << "Enter stock symbol and filename to import data: ";
                cin >> symbol >> filename;
                stockManager.importData(symbol, filename);
                break;
            }
            case 4: {
                cout << "Enter stock symbol to search: ";
                cin >> symbol;
                stockManager.searchStock(symbol);
                break;
            }
            case 5: {
                cout << "Enter stock symbol to plot: ";
                cin >> symbol;
                stockManager.plotStock(symbol);
                break;
            }
            case 6: {
                cout << "Enter filename to save: ";
                cin >> filename;
                stockManager.saveToFile(filename);
                break;
            }
            case 7: {
                cout << "Enter filename to load: ";
                cin >> filename;
                stockManager.loadFromFile(filename);
                break;
            }
            case 8: {
                cout << "Enter stock symbol to fetch data: ";
                cin >> symbol;
                fetchDataFromYahooFinance(symbol);
                break;
            }
            case 9:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
