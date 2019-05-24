#pragma once
#include "Queue/Queue.h"
#include "Sort/MergeSort.h"
#include <cstring>
#include <fstream>
#include <iostream>

const size_t BUFFER_SIZE = 500;

void sort_file(const char* filename) {
    char buffer[BUFFER_SIZE] = {'\0'};
    char overflow[BUFFER_SIZE] = {'\0'};

    std::ifstream file(filename);
    file.read(buffer, BUFFER_SIZE - 1);
    buffer[file.gcount()] = '\0';

    // make sure we arent cutting off any numbers
    int last_whitespace = 0;
    for (int i = 0; i < file.gcount(); i++) {
        if (buffer[i] == ' ' || buffer[i] == '\r' || buffer[i] == '\n' ||
            buffer[i] == '\t') {
                last_whitespace = i;
        }
    }
    if (last_whitespace != file.gcount() - 1) {
        strncpy(overflow, buffer[last_whitespace + 1], file.gcount() - last_whitespace);
    }
}