#pragma once
#include <cstdlib>
#include <ctime>
#include <fstream>

namespace msod_util {

// checks if a file is sorted
bool is_sorted(std::string filename) {
    std::ifstream fin;
    fin.open(filename);
    int num1;
    int num2;
    while (fin >> num1 && fin >> num2) {
        if (num1 > num2) {
            fin.close();
            return false;
        }
    }
    fin.close();
    return true;
}

// generates a file with random numbers
void generate_random(std::string filename, int size) {
    srand(time(0));
    std::ofstream fout;
    fout.open(filename);
    for (int i = 0; i < size; i++) {
        fout << rand() % 1000000 << std::endl;
    }
    fout.close();
}

}