#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <cstdlib>    // for std::rand

template <typename T>
void quickSort(T* arr, int size) {
    if (size <= 1) return;
    int pivot_index = std::rand() % size;
    std::swap(arr[pivot_index], arr[size - 1]);
    T pivot = arr[size - 1];
    int i = 0;
    int j = 0;
    int k = size - 1;
    while (j <= k) {
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            i++;
            j++;
        } else if (arr[j] > pivot) {
            std::swap(arr[j], arr[k]);
            k--;
        } else {
            j++;
        }
    }
    quickSort(arr, i);
    quickSort(arr + k + 1, size - k - 1);
}

#endif //QUICK_SORT_HPP