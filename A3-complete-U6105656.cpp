#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;
// tables stores the price of models, all funitures all models
int table[10][10];
// models is used to store the types of model
int models[10];
// slection is an empty array
int selection[10];
// result is used to store the combination of best selection
int result[10];

// the function 'find_maximum' returns the maximum spend money
// Reference: 
int find_maximum(int total_types, int total_money) {
    int maximum = 0;
    while (true) {
        // sum is used to store the current combination's sum value
        int sum = 0;
        // calculate the sum of current combination
        for (int i = 0; i < total_types; i++) {
            if (sum + table[i][selection[i]] < total_money) {
                sum = sum + table[i][selection[i]];
            } else if (sum + table[i][selection[i]] == total_money and i == total_types - 1) {
                sum = sum + table[i][selection[i]];
            } else {
                // if the sum is already over than total_money, set value to -1 and break.
                // When pick the maximum value, it always cannot be picked.
                sum = -1;
                break;
            }
            maximum = std::max(maximum,sum);
        }
        // If the current combination is the optimal one, update the result array
        if (maximum == sum) {
            for (int j = 0; j < total_types; j++) {
                result[j] = selection[j];
            }
        }
        // update the value for next combination
        int next = total_types - 1;
        while (next >= 0 and (selection[next] +1 >= models[next])) {
            next = next - 1;
        }
        // if all complete search is done, finish the while loop.
        if (next < 0) {
            break;
        }
        selection[next] = selection[next] + 1;
        for (int i = next + 1; i < total_types; i++) {
            selection[i] = 0;
        }
    }
    return maximum;
}

int main(int argc, char* argv[]) {
    ifstream file;
    file.open(argv[1]);
    int total_money, total_types;
    file >> total_money >> total_types;
    clock_t start,end;
    start = clock();
    for (int i = 0; i < total_types; i++) {
        int model = 0;
        file >> model;
        models[i] = model;
        for (int j = 0; j < model; j++) {
            int value = 0;
            file >> value;
            table[i][j] = value;
        }
    }
    int answer = find_maximum (total_types, total_money);
    cout << answer << " ";
    for (int j = 0; j < total_types; j++) {
        cout << result[j] << " ";
    }
    cout << endl;
    end = clock();
    /* following code is for printing the time. */
    /* cout << start << " " << end << " ";
    cout << CLOCKS_PER_SEC << "\n";
    long double cpu_timeused = (end - start)/(long double)CLOCKS_PER_SEC;
    cout << 1000*cpu_timeused << "\n";
    return 0; */
}


