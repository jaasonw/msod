/*
 * Author: Jason Wong
 * Project: merge sort on disk
 * Purpose: implement a mergesort that can sort large files of numbers that
 *          do not fit in ram
 * Notes:
 */
#include "merge_sort_on_disk.h"
#include "sort_util.h"
#include <chrono>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const* argv[]) {
    
    int numbers = 90000;

    string in = "test.txt";
    string out = "output.txt";

    auto t0 = std::chrono::high_resolution_clock::now();
    cout << "Generating file with " << numbers << " numbers" << endl;
    msod_util::generate_random(in, numbers);
    msod::sort_file(in, out, true);
    cout << ((msod_util::is_sorted(out)) ? "SORTED" : "NOT SORTED") << endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count();
    cout << "Operation took: " << duration << " seconds" << endl;

    cout << endl;
    system("pause");
    return 0;
}