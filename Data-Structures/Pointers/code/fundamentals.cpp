#include "fundamentals.hpp"

void insertStockInfo(stockInfo stocks[], string company_name, double stock_prices_arr[], int index) {
    stockInfo newStock;
    double average = 0;
    for (int i = 0; i < 5; ++i) {
        newStock.stock_prices_arr[i] = stock_prices_arr[i];
        average += stock_prices_arr[i];
    }
    newStock.average = average / 5.0;
    newStock.company_name = company_name;
    stocks[index] = newStock;
    return;
}
void sort(double arr[]) {
    double arr_A[5];
    int iter = 0, index = 0;
    for (int i = 0; i < 5; ++i) {
        arr_A[i] = arr[i];
    }
    while (iter < 5) {
        double least = __DBL_MAX__;
        for (int i = 0; i < 5; ++i) {
            if (arr_A[i] < least) {
                least = arr_A[i];
                index = i;
            }
        }
        arr[iter] = least;
        arr_A[index] = __DBL_MAX__;
        ++iter;
        least = __DBL_MAX__;
        index = 0;
    }
}
void displaySortedStocks(stockInfo stock, ofstream& file){
    cout << stock.company_name << "," << stock.average << ",";
    sort(stock.stock_prices_arr);
    if (file.is_open()) {
        file << stock.company_name << "," << stock.average << ",";
        for (int i = 0; i < 5; ++i) {
            if (i == 4) {
                file << stock.stock_prices_arr[i] << "\n";
                cout << stock.stock_prices_arr[i] << "\n";
            } else {
                file << stock.stock_prices_arr[i] << ",";
                cout << stock.stock_prices_arr[i] << ",";
            }
        }
    }
    return;   
}
