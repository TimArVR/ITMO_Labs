#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"
#include "./MySort.h"

constexpr int kNumberTests = 1000;
constexpr int kMaxSize = 64;


int main()
{ 
    int a[kMaxSize];
    LARGE_INTEGER Start, End;
    LARGE_INTEGER Freq;
    
    QueryPerformanceFrequency(&Freq);
    double Frequency = double(Freq.QuadPart) / 1000;

    // Быстрая сортировка

    std::ofstream fout("QuickSort.txt", std::ios_base::out | std::ios_base::trunc);
    fout << "size, QS" << std::endl;

    for (int size = 3; size < kMaxSize; size++)
    {

        QueryPerformanceCounter(&Start);
        for (int cycle = 0; cycle < kNumberTests; cycle++)
        {

            for (int i = 0; i < size; i++) 
            {
                a[i] = size - i;
            }

            QuickSort(a, a + size, [](int a, int b) { return a < b; });
        }
        QueryPerformanceCounter(&End);
        fout << size << "," << (End.QuadPart - Start.QuadPart) / Frequency << std::endl;

    }
    fout.close();

    // Сортировка вставками

    fout.open("InsertionSort.txt", std::ios_base::out | std::ios_base::trunc);
    fout << "size, IS" << std::endl;

    for (int size = 3; size < kMaxSize; size++)
    {
        QueryPerformanceCounter(&Start);
        for (int cycle = 0; cycle < kNumberTests; cycle++) 
        {
            for (int i = 0; i < size; i++) 
            {
                a[i] = size - i;
            }

            InsertionSort(a, a + size, [](int a, int b) { return a < b; });
        }
        QueryPerformanceCounter(&End);
        fout << size << "," << (End.QuadPart - Start.QuadPart) / Frequency << std::endl;        
    }

    fout.close();
}