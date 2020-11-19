#pragma once
#include "Sort/MergeSort.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>

namespace msod {

// the directory that contains the temp files
const char* OUTPUT_DIRECTORY = "output/";
// the max size of the read buffer
const int READ_BUFFER_CAP = 500;
// number of numbers in each file chunk
const int CHUNK_SIZE = 50000;
// the max number of filenames the sort queue may hold
const int SORT_QUEUE_CAP = 100;

// chunk the input into n numbers per file
// returns the number of files created
int split_to_chunks(std::string filename, int chunk_size) {
    std::ifstream fin;

    // limit the read buffer to make sure we arent loading in the entire file
    char buffer[READ_BUFFER_CAP];
    fin.rdbuf()->pubsetbuf(buffer, READ_BUFFER_CAP);

    int num = 0;
    fin.open(filename);
    if (fin.fail()) {
        return -1;
    }
    int counter = 0;
    while (!fin.eof()) {
        std::string _filename = std::to_string(counter);
        std::ofstream fout;
        fout.open(OUTPUT_DIRECTORY + _filename);
        for (int i = 0; i < chunk_size && !fin.eof(); i++) {
            if (fin >> num)
                fout << num << std::endl;
        }
        fout.close();
        counter++;
    }
    fin.close();
    return counter;
}

// sorts a file, this should be used for the small files
void small_sort(std::string filename, int chunk_size) {
    int* array = new int[chunk_size + 1];
    int array_size = 0;

    std::ifstream fin;
    fin.open(OUTPUT_DIRECTORY + filename);
    // no reason this should ever fail really
    assert(!fin.fail());
    for (array_size = 0; !fin.eof(); array_size++) {
        // file somehow had more numbers than the chunk allowed
        assert(array_size <= chunk_size);
        int num;
        fin >> num;
        array[array_size] = num;
    }
    fin.close();
    array_size--;

    Sort::merge_sort(array, array_size);
    std::ofstream fout;
    fout.open(OUTPUT_DIRECTORY + filename);
    assert(!fout.fail());
    for (int i = 0; i < array_size; i++) {
        fout << array[i] << std::endl;
    }
    fout.close();

    delete[] array;
}

// merges 2 sorted files and output into file3
void merge_files(std::string file1, std::string file2, std::string file3) {
    std::ifstream fin1;
    std::ifstream fin2;
    std::ofstream fout;

    // limit the buffer sizes
    char buffer1[READ_BUFFER_CAP];
    char buffer2[READ_BUFFER_CAP];
    fin1.rdbuf()->pubsetbuf(buffer1, READ_BUFFER_CAP);
    fin2.rdbuf()->pubsetbuf(buffer2, READ_BUFFER_CAP);

    fin1.open(OUTPUT_DIRECTORY + file1);
    fin2.open(OUTPUT_DIRECTORY + file2);
    fout.open(OUTPUT_DIRECTORY + file3);

    assert(!fin1.fail() && !fin2.fail());

    int num1;
    int num2;
    bool file1_empty = !(fin1 >> num1);
    bool file2_empty = !(fin2 >> num2);
    while (!file1_empty && !file2_empty) {
        if (num1 < num2) {
            fout << num1 << std::endl;
            file1_empty = !(fin1 >> num1);
        }

        if (num1 > num2) {
            fout << num2 << std::endl;
            file2_empty = !(fin2 >> num2);
        }

        if (num1 == num2) {
            fout << num1 << std::endl;
            fout << num2 << std::endl;
            file1_empty = !(fin1 >> num1);
            file2_empty = !(fin2 >> num2);
        }
    }
    // deal with numbers left in num1 and num2
    if (!file1_empty) {
        fout << num1 << std::endl;
    }
    if (!file2_empty) {
        fout << num2 << std::endl;
    }

    // empty out the rest of the files
    // int num;
    while (fin1 >> num1) {
        fout << num1 << std::endl;
    }
    while (fin2 >> num2) {
        fout << num2 << std::endl;
    }
    fin1.close();
    fin2.close();
    fout.close();
}

// mergesorts every file in the queue until 1 sorted array remains
void sort_queue(std::queue<std::string>& filenames) {
    while (filenames.size() >= 2) {
        std::string file1 = filenames.front();
        filenames.pop();
        std::string file2 = filenames.front();
        filenames.pop();
        std::string outfile = '_' + file1;
        merge_files(file1, file2, outfile);
        // delete the 2 files we just merged
        remove(std::string(OUTPUT_DIRECTORY + file1).c_str());
        remove(std::string(OUTPUT_DIRECTORY + file2).c_str());
        // rename outfile to the old file1
        rename((OUTPUT_DIRECTORY + outfile).c_str(),
               (OUTPUT_DIRECTORY + file1).c_str());
        filenames.push(file1);
    }
}

void sort_file(std::string infile, std::string outfile, bool verbose = false) {
    // use a queue to store filenames in the order we want to sort
    std::queue<std::string> queue;

    if (verbose)
        std::cout << "Splitting file into chunks" << std::endl;
    // split file into chunks
    int num_chunks = split_to_chunks(infile, CHUNK_SIZE);
    if (verbose) {
        std::cout << "Created " << num_chunks << " chunks of " << CHUNK_SIZE << " numbers";
        std::cout << std::endl;
        std::cout << "Sorting chunks" << std::endl;
    }

    // sort chunks
    for (int i = 0; i < num_chunks; i++) {
        std::string filename(std::to_string(i));
        small_sort(filename, CHUNK_SIZE);
        queue.push(filename);
        // merge files once we hit the cap
        if (queue.size() >= SORT_QUEUE_CAP) {
            sort_queue(queue);
        }
    }

    // mergesort the rest of files in the queue, if anything remains
    sort_queue(queue);

    // rename the file in the queue to sorted
    std::string old = (OUTPUT_DIRECTORY + queue.front());
    queue.pop();
    rename(old.c_str(), outfile.c_str());
}

} // namespace msod