#ifndef INTRO_SORT_HPP
#define INTRO_SORT_HPP

#include <algorithm>
#include <cmath>

template <typename T>
void insertion_sort(T arr[], int begin, int end) {
    for (int i = begin + 1; i < end; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= begin && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
void heapify(T arr[], int begin, int end, int i) {
    int largest = i;
    int left = 2 * (i - begin) + 1 + begin;
    int right = 2 * (i - begin) + 2 + begin;

    if (left < end && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < end && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, begin, end, largest);
    }
}

template <typename T>
void heapsort(T arr[], int begin, int end) {
    for (int i = begin + (end - begin) / 2 - 1; i >= begin; --i) {
        heapify(arr, begin, end, i);
    }
    for (int i = end - 1; i > begin; --i) {
        std::swap(arr[begin], arr[i]);
        heapify(arr, begin, i, begin);
    }
}

template <typename T>
int partition(T arr[], int begin, int end) {
    int mid = begin + (end - begin) / 2;
    if (arr[mid] < arr[begin]) std::swap(arr[mid], arr[begin]);
    if (arr[end - 1] < arr[mid]) std::swap(arr[end - 1], arr[mid]);
    if (arr[mid] < arr[begin]) std::swap(arr[mid], arr[begin]);
    std::swap(arr[mid], arr[end - 1]);
    T pivot = arr[end - 1];

    int i = begin - 1;
    for (int j = begin; j < end - 1; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[end - 1]);
    return i + 1;
}

template <typename T>
void quicksort(T arr[], int begin, int end, int depth_limit, int current_depth) {
    while (end - begin > 1) {
        int size = end - begin;
        if (size < 16) {
            insertion_sort(arr, begin, end);
            break;
        }
        if (current_depth >= depth_limit) {
            heapsort(arr, begin, end);
            break;
        }

        int pivot = partition(arr, begin, end);
        ++current_depth;

        // recurse on smaller side
        if (pivot - begin < end - pivot - 1) {
            quicksort(arr, begin, pivot, depth_limit, current_depth);
            begin = pivot + 1;   // tail-call on larger side
        } else {
            quicksort(arr, pivot + 1, end, depth_limit, current_depth);
            end = pivot;         // tail-call on larger side
        }
    }
}


template <typename T>
void introsort(T arr[], int size) {
    if (size <= 1) return;
    int depth_limit = 2 * static_cast<int>(std::log2(size));
    quicksort(arr, 0, size, depth_limit, 0);
}

#endif // INTRO_SORT_HPP
