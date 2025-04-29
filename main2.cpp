#include <chrono>
#include <random>
#include <fstream>
#include "quick_sort.hpp"
#include "merge_sort.hpp"
#include "intro_sort.hpp"

const int NUM_REPETITIONS = 100;
const std::vector<int> SIZES = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
const std::vector<double> SORTED_PERCENTAGES = {0.25, 0.50, 0.75, 0.95, 0.99, 0.997};
const std::string OUTPUT_FILENAME = "sorting_results_avg.csv";

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void generateRandom(int arr[], int size) {
    std::uniform_int_distribution<int> dist(1, size * 10);
    for (int i = 0; i < size; i++) {
        arr[i] = dist(rng);
    }
}

void generatePartiallySorted(int arr[], int size, double sorted_percentage) {
    int sorted_count = static_cast<int>(sorted_percentage * size);
    std::iota(arr, arr + sorted_count, 0);
    if (sorted_count < size) {
        std::shuffle(arr + sorted_count, arr + size, rng);
    }
}

void generateReversed(int arr[], int size) {
    std::iota(arr, arr + size, 0);
    std::reverse(arr, arr + size);
}

int main() {
    std::ofstream resultsFile(OUTPUT_FILENAME);
    if (!resultsFile.is_open()) {
        std::cerr << "Blad: Nie mozna otworzyc pliku do zapisu: " << OUTPUT_FILENAME << std::endl;
        return 1;
    }

    using SortFunction = void (*)(int[], int);
    std::vector<std::pair<std::string, SortFunction>> algorithms = {
        {"IntroSort", introsort<int>},
        {"QuickSort", quickSort<int>},
        {"MergeSort", mergeSort<int>}
    };

    for (const auto &algorithm : algorithms) {
        const auto& algName = algorithm.first;
        SortFunction sortFunc = algorithm.second;

        // Test random arrays
        for (int size : SIZES) {
            long long total_time = 0;
            for (int rep = 0; rep < NUM_REPETITIONS; rep++) {
                int* data = new int[size];
                generateRandom(data, size);
                auto start = std::chrono::high_resolution_clock::now();
                sortFunc(data, size);
                auto end = std::chrono::high_resolution_clock::now();
                total_time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                delete[] data;
            }
            int avg_time = static_cast<int>(total_time) / NUM_REPETITIONS;
            std::cout << algName << " " << size << std::endl;
            resultsFile << algName << "," << size << "," << "Random," << avg_time << std::endl;
        }

        // Test reversed arrays
        for (int size : SIZES) {
            long long total_time = 0;
            for (int rep = 0; rep < NUM_REPETITIONS; rep++) {
                int* data = new int[size];
                generateReversed(data, size);
                auto start = std::chrono::high_resolution_clock::now();
                sortFunc(data, size);
                auto end = std::chrono::high_resolution_clock::now();
                total_time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                delete[] data;
            }
            int avg_time = static_cast<int>(total_time) / NUM_REPETITIONS;
            std::cout << algName << " " << size << std::endl;
            resultsFile << algName << "," << size << "," << "Reversed," << avg_time << std::endl;
        }

        // Test partially sorted arrays for each percentage
        for (double perc : SORTED_PERCENTAGES) {
            for (int size : SIZES) {
                long long total_time = 0;
                for (int rep = 0; rep < NUM_REPETITIONS; rep++) {
                    int* data = new int[size];
                    generatePartiallySorted(data, size, perc);
                    auto start = std::chrono::high_resolution_clock::now();
                    sortFunc(data, size);
                    auto end = std::chrono::high_resolution_clock::now();
                    total_time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                    delete[] data;
                }
                int avg_time = static_cast<int>(total_time) / NUM_REPETITIONS;
                std::cout << algName << " " << size << std::endl;
                resultsFile << algName << "," << size << "," << perc << "," << avg_time << std::endl;
            }
        }
    }

    resultsFile.close();
    return 0;
}