#pragma once

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