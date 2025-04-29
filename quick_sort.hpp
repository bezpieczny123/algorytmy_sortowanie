#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <algorithm>
#include <utility>

template <typename T>
void quickSort(T* arr, int size) {
    if (size <= 1) {
        return;
    }

    int pivot_index = size - 1;

    if (size >= 3) {
        int first_index = 0;
        int mid_index = (size - 1) / 2;
        int last_index = size - 1;

        if (arr[first_index] > arr[mid_index]) {
            std::swap(arr[first_index], arr[mid_index]);
        }
        if (arr[mid_index] > arr[last_index]) {
            std::swap(arr[mid_index], arr[last_index]);
        }
        if (arr[first_index] > arr[mid_index]) {
            std::swap(arr[first_index], arr[mid_index]);
        }

        std::swap(arr[mid_index], arr[last_index]);
    }

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

#endif // QUICK_SORT_HPP
