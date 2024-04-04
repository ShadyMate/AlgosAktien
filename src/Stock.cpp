#include "Stock.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

Stock::Stock(string name, string wkn, string acro){
    this->name = name;
    this->wkn = wkn;
    this->acro = acro;
    stockValVector.clear();

}

string Stock::getName(){
    return name;
}
string Stock::getWkn(){
    return wkn;
}
string Stock::getAcro(){
    return acro;
}
vector<StockVal>& Stock::getStockVal(){
    return stockValVector;
}


void Stock::setStockArguments(string name, string wkn, string acro){
    this->name = name;
    this->wkn = wkn;
    this->acro = acro;
}

void Stock::displayLatestStockVal(Stock* stock){
    if (!stock->stockValVector.empty()) {
        const auto& data = stock->stockValVector.back();
        cout << "Date: " << data.date << endl;
        cout << "Open: " << data.open << endl;
        cout << "High: " << data.high << endl;
        cout << "Low: " << data.low << endl;
        cout << "Close: " << data.close << endl;
        cout << "Volume: " << data.volume << endl;
        cout << "Adjusted Close: " << data.adj_close << endl;
    } else {
        cout << "No stock data available." << endl;
    }
}

StockVal Stock::parseCSVLine(const string& line){
    StockVal data;

    stringstream ss(line);
    string token;

    try
    {
        // Read each token separated by commas
        getline(ss, token, ',');
        data.date = token;

        getline(ss, token, ',');
        data.open = stod(token);

        getline(ss, token, ',');
        data.high = stod(token);

        getline(ss, token, ',');
        data.low = stod(token);

        getline(ss, token, ',');
        data.close = stod(token);

        getline(ss, token, ',');
        data.volume = stoi(token);

        getline(ss, token, ',');
        data.adj_close = stod(token);
    }
    catch (const std::invalid_argument& ia)
    {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
    }
    catch (const std::out_of_range& oor)
    {
        std::cerr << "Out of range: " << oor.what() << '\n';
    }
    return data;
}

void Stock::importCSVData(const string& filename, vector<StockVal>& stockVectorData){
    ifstream file(filename);

    // Check if the file was successfully opened
    if (!file.is_open()) {
        cout << "Could not open file " << filename << ". Please check the file path and try again." << endl;
        return;
    }

    string line;
    int count = 0;
    getline(file, line);

    while (getline(file, line) && count < 30) {
        StockVal data = parseCSVLine(line);
        stockVectorData.push_back(data);
        count++;
    }

    file.close();
    //displayStockVal();
    cout << "File \"" << filename << "\" was successfully imported!" << endl;
}

Stock Stock::createStock(){
    importCSVData("file.csv", this->stockValVector);
    return *this;
}

string Stock::serialize(){
    stringstream ss;
    ss << name << "," << wkn << "," << acro;

    // Convert Vector to string
    for (const auto& data : stockValVector) {
        ss << "," << data.date << "," << data.open << "," << data.high << "," << data.low << "," << data.close << "," << data.volume << "," << data.adj_close;
    }

    return ss.str();
}


Stock Stock::deserialize(const string& line){
    Stock stock("", "", "");
    stringstream ss(line);
    string token;

    // Read each token separated by commas
    getline(ss, token, ',');
    stock.name = token;

    getline(ss, token, ',');
    stock.wkn = token;

    getline(ss, token, ',');
    stock.acro = token;

    // Read the stock values
    while (getline(ss, token, ',')) {
        StockVal data;

        data.date = token;

        getline(ss, token, ',');
        data.open = stod(token);

        getline(ss, token, ',');
        data.high = stod(token);

        getline(ss, token, ',');
        data.low = stod(token);

        getline(ss, token, ',');
        data.close = stod(token);

        getline(ss, token, ',');
        data.volume = stoi(token);

        if (!ss.eof()) {
            getline(ss, token, ',');
            data.adj_close = stod(token);
        }

        stock.stockValVector.push_back(data);
    }

    return stock;
}

Stock::~Stock(){

}
