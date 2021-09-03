#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;
/* the 'table' is used to store the current maximum spent money during the dynamic programming */
int table[100000][100];
/* the 'table_model' is used to store the selected model during the dynamic programming */
int table_model[100000][100];
/* the 'table_price' is used to store the price of selected model during the dynamic programming */
int table_price[100000][100];

int main(int argc, char* argv[]) {
    ifstream file;
    file.open(argv[1]);
    int total_money, total_types;
    file >> total_money >> total_types;
    clock_t start,end;
    start = clock();
    for (int i = 0; i < total_types; i++) {
        int total_model;
        file >> total_model;
        int models[total_model]; // array of K
        for (int x = 0; x < total_model; x++) {
            int value;
            file >> value;
            models[x] = value; // create price array
        }
        for (int j = 0; j <= total_money; j++) {
            int max_value = 0;
            int model = 0;
            int price = 0;
            for (int m = 0; m < total_model; m++) { // going through price array
                int previous = max_value;
                if (j > models[m] and i > 0) { // if you can afford furniture
                    int remaining = j - models[m];
                    max_value = max(max_value, models[m] + table[remaining][i-1]);
                } else if (j > models[m] and i == 0){
                    max_value = max(models[m],max_value);
                } else if (j == models[m]) {
                    max_value = models[m];
                }
                if (max_value != previous) {
                    model = m;
                    price = models[m];
                }
            }
            table[j][i] = max_value;
            table_model[j][i] = model + 1;
            table_price[j][i] = price;
        }
    }
    cout << table[total_money][total_types-1] << " ";
    //start to find the solution
    int previous = 0;
    int selection[total_types];
    for (int i = total_types-1; i >= 0; i--) {
        if (i == total_types - 1) {
            previous = table[total_money][total_types-1] - table_price[total_money][total_types-1];
            selection[i] = table_model[total_money][total_types-1];
        } else {
            selection[i] = table_model[previous][i];
            previous = previous - table_price[previous][i];
        }
    }
    // print out the solution
    for (int i = 0; i < total_types; i++) {
        cout << selection[i] << " ";
    }
    cout << endl;
    /*end = clock();
    cout << start << " " << end << " ";
    cout << CLOCKS_PER_SEC << "\n";
    long double cpu_timeused = (end - start)/(long double)CLOCKS_PER_SEC;
    cout << 1000*cpu_timeused << "\n";
    return 0; */
}
