#include "yahoo_finance.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <curl/curl.h>

using namespace std;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* buffer) {
    buffer->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void fetchDataFromYahooFinance(const string& symbol) {
    string url = "http://de.finance.yahoo.com/q/hp?s=" + symbol;

    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            cerr << "Failed to fetch data: " << curl_easy_strerror(res) << endl;
            return;
        }

        // Parse CSV data from readBuffer
        stringstream ss(readBuffer);
        string line;
        while (getline(ss, line)) {
            // Skip headers or process CSV data line by line
            cout << line << endl;
        }
    }
}
