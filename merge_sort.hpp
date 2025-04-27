#ifndef MERGE_HPP
#define MERGE_HPP
#include <iostream>

template <typename T>
void merge(T* in, T* out, int b, int m, int n) {
    auto less = [](T a, T b) { return a < b; };
    int i = b;
    int j = b + m;
    int const e1 = std::min(b + m, n);
    int const e2 = std::min(b + 2*m, n);
    int k = b;
    while (i < e1 && j < e2) {
        if (!less(in[j], in[i]))
            out[k++] = in[i++];
        else
            out[k++] = in[j++];
    }
    while (i < e1)
        out[k++] = in[i++];
    while (j < e2)
        out[k++] = in[j++];
}

template <typename T>
void mergeSort(T* S, int n) {
    T* a1 = new T[n];
    T* a2 = new T[n];
    for (int i = 0; i < n; i++) {
        a1[i] = S[i];
    }
    T* in = a1;
    T* out = a2;
    for (int m = 1; m < n; m *= 2) {
        for (int b = 0; b < n; b += 2*m) {
            merge(in, out, b, m, n);
        }
        std::swap(in, out);
    }
    for (int i = 0; i < n; i++) {
        S[i] = in[i];
    }
    delete[] a1;
    delete[] a2;
}

#endif //MERGE_HPP
