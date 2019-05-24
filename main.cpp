/*
 * Author: Jason Wong
 * Project: 
 * Purpose: 
 * Notes:
 */
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const* argv[]) {
    // reads in a csv of values
    const int READ_SIZE = 500;
    const int SORT_SIZE = 500;
    char read_buffer[READ_SIZE] = "";
    char sort_buffer[SORT_SIZE] = "";

    std::ifstream fin;
    int num = 0;
    char a;
    cin >> a;
    fin.open("numbers.txt");
        fin>>num;
    // cout << fin.rd
    int counter = 0;
    
    while (!fin.eof()) {
        std::string filename = "output/" + std::to_string(counter) + ".txt";
        std::ofstream fout;
        fout.open(filename);
        fout << num;
        fout.close();
        counter++;
    }
    cout << num;
    // fin.close();
    // fin.read(read_buffer, READ_SIZE);
    // std::string num = "";
    
    // split into 1 number per file for a bottom up merge sort
    // for (int i = 0; i < fin.gcount(); i++) {
    //     if (read_buffer[i] != )
    // }

    cout << endl;
    system("pause");
    return 0;
}