#pragma once
#include "Heap.h"
#include <algorithm>

template <typename T>
void bubble_sort(T* array, unsigned int size) {
    for (unsigned int i = 0; i < size - 1; i++) {
        for (unsigned int j = 0; j < size - i - 1; j++) {
            if (array[j] >= array[j + 1])
                std::swap(array[j], array[j + 1]);
        }
    }
}

template <typename T>
void quick_sort(T* array, int start, int end) {
    if (start >= end)
        return;
    
    // partition array
    T pivot_item = array[end];
    int new_pivot_index = start;
    int end_index = end;

    while (new_pivot_index <= end_index) {
        while (array[new_pivot_index] < pivot_item) {
            new_pivot_index++;
        }
        while (array[end_index] > pivot_item) {
            end_index--;
        }

        if (new_pivot_index <= end_index) {
            std::swap(array[new_pivot_index], array[end_index]);
            new_pivot_index++;
            end_index--;
        }
    }

    // do recursion
    if (start < end_index)
        quick_sort(array, start, end_index);
    if (new_pivot_index < end)
        quick_sort(array, new_pivot_index, end);
}
template <typename T>
void quick_sort(T* array, unsigned int size) {
    quick_sort(array, 0, size - 1);
}



template <typename T>
void insertion_sort(T* array, unsigned int size) {
    for (unsigned int i = 1; i < size; i++) {
        T insert = array[i];
        int insert_at = i;
        while (insert_at > 0 && array[insert_at - 1] > insert) {
            array[insert_at] = array[insert_at - 1];
            insert_at--;
        }
        array[insert_at] = insert;
    }
}

template <typename T>
void merge(T* array, int midpoint, int size) {
    int left = 0;
    int right = midpoint;

    T merged[size];
    int merged_index = 0;

    while(left < midpoint && right < size) {
        if (array[left] >= array[right]) {
            merged[merged_index++] = array[right++];
        }
        else if (array[left] < array[right]) {
            merged[merged_index++] = array[left++];
        }
    }
    while(right < size) {
        merged[merged_index++] = array[right++];
    }
    while(left < midpoint) {
        merged[merged_index++] = array[left++];
    }
    for (int i = 0; i < size; i++) {
        array[i] = merged[i];
    }
}

template <typename T>
void merge_sort(T* array, unsigned int size) {
    if (size > 1) {
        int middle = size / 2;
        merge_sort(array, size / 2);
        merge_sort(&array[size / 2], (size + 1) / 2);
        merge(array, middle, size);
    }
}

template <typename T>
void heap_sort(T* array, unsigned int size) {
    Heap<T> heap;
    for (unsigned int i = 0; i < size; i++)
        heap.insert(array[i]);
    for (unsigned int i = 0; i < size; i++)
        array[i] = heap.pop();
}