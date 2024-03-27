#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <tuple>

const int TABLE_SIZE = 1000;

using namespace std;

struct Stock {
    string name;
    string wkn;
    string symbol;
    vector<tuple<string, double, double, double, double, int, double>> data;
};

struct HashNode {
    string key;
    Stock value;
};

class HashTable {
private:
    vector<list<HashNode>> table;
    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return hash;
    }
public:
    HashTable() : table(TABLE_SIZE) {}
    void insert(const string& key, const Stock& value) {
        int hash = hashFunction(key);
        for (auto& node : table[hash]) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }
        table[hash].push_back({key, value});
    }
    void remove(const string& key) {
        int hash = hashFunction(key);
        for (auto it = table[hash].begin(); it != table[hash].end(); ++it) {
            if (it->key == key) {
                table[hash].erase(it);
                return;
            }
        }
    }
    Stock* search(const string& key) {
        int hash = hashFunction(key);
        for (auto& node : table[hash]) {
            if (node.key == key) {
                return &node.value;
            }
        }
        return nullptr;
    }
    void plot(const string& key) {
        Stock* stock = search(key);
        if (stock) {
            cout << "Plotting data for " << stock->name << " (" << stock->symbol << "):\n";
            for (auto& data : stock->data) {
                cout << get<0>(data) << ": " << get<4>(data) << "\n";
            }
        } else {
            cout << "Stock not found.\n";
        }
    }
    void save(const string& filename) {
        ofstream file(filename);
        for (auto& list : table) {
            for (auto& node : list) {
                file << node.key << "\n";
                file << node.value.name << "\n";
                file << node.value.wkn << "\n";
                file << node.value.symbol << "\n";
                for (auto& data : node.value.data) {
                    file << get<0>(data) << " " << get<1>(data) << " " << get<2>(data) << " "
                         << get<3>(data) << " " << get<4>(data) << " " << get<5>(data) << " "
                         << get<6>(data) << "\n";
                }
                file << "\n";
            }
        }
    }
    void load(const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            string key = line;
            getline(file, line);
            string name = line;
            getline(file, line);
            string wkn = line;
            getline(file, line);
            string symbol = line;
            Stock stock = {name, wkn, symbol, {}};
            while (getline(file, line) && !line.empty()) {
                istringstream ss(line);
                string date;
                double open, high, low, close, adjClose;
                int volume;
                ss >> date >> open >> high >> low >> close >> volume >> adjClose;
                stock.data.push_back(make_tuple(date, open, high, low, close, volume, adjClose));
            }
            insert(key, stock);
        }
    }
    void quit() {
        exit(0);
    }
};

int main() {
    HashTable table;
    int choice;
    while (true) {
        cout << "1. ADD\n2. DEL\n3. IMPORT\n4. SEARCH\n5. PLOT\n6. SAVE\n7. LOAD\n8. QUIT\n";
        cin >> choice;
        switch (choice) {
            case 1: {
                string name, wkn, symbol;
                cout << "Enter name, WKN and symbol:\n";
                cin >> name >> wkn >> symbol;
                table.insert(symbol, {name, wkn, symbol, {}});
                break;
            }
            case 2: {
                string symbol;
                cout << "Enter symbol:\n";
                cin >> symbol;
                table.remove(symbol);
                break;
            }
            case 3: {
                // Implementieren Sie die Funktion zum Importieren von Daten aus einer CSV-Datei.
                break;
            }
            case 4: {
                string symbol;
                cout << "Enter symbol:\n";
                cin >> symbol;
                table.search(symbol);
                break;
            }
            case 5: {
                string symbol;
                cout << "Enter symbol:\n";
                cin >> symbol;
                table.plot(symbol);
                break;
            }
            case 6: {
                string filename;
                cout << "Enter filename:\n";
                cin >> filename;
                table.save(filename);
                break;
            }
            case 7: {
                string filename;
                cout << "Enter filename:\n";
                cin >> filename;
                table.load(filename);
                break;
            }
            case 8: {
                table.quit();
                break;
            }
            default: {
                cout << "Ungültige Auswahl.\n";
                break;
            }
        }
    }
    return 0;
}
