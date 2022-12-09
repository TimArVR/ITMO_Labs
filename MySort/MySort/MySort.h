#pragma once

#include <iostream>
#include <string>

constexpr int kThreshold = 32;

//������� ������� ��� QuickSort, ������� �������, �������� � ���������� �������� ������������ ���������
template<typename T, typename Compare>
T PivotCalc(T* first, T* last, Compare comp)
{
	T* middle = first + (last - first) / 2;

	if ((comp(*first, *last) && comp(*middle, *first)) || (comp(*first, *middle) && comp(*last, *first)))
	{
		return *first;
	}
	else if ((comp(*last, *first) && comp(*middle, *last)) || (comp(*last, *middle) && comp(*first, *last)))
	{
		return *last;
	}
	else
	{
		return *middle;
	}
}

// ���������� ���������
template<typename T, typename Compare>
void InsertionSort(T* first, T* last, Compare comp)
{
	for (T* i = first + 1; i <= last; i++)
	{
		T* j = i - 1;
		T key = std::move(*i);

		while (j >= first && comp(key, *j))
		{
			*(j + 1) = std::move(*j);
			j--;
		}

		*(j + 1) = std::move(key);
	}
}

// ��������� ����� �� ��� ����� ������������ pivot
template<typename T, typename Compare>
T* HoarePartition(T* first, T* last, Compare comp) {

	T pivot = std::move(PivotCalc(first, last, comp));

	T* i = first-1;
	T* j = last+1;

	while (true)
	{
		do 
		{
			++i;
		} 
		while (comp(*i, pivot));

		do
		{
			--j;
		}
		while (comp(pivot, *j));

			if (i >= j)
			{
				return j;
			}

		std::swap(*i, *j);

	}
}

// ������� ���������� �� ������ ���������� �����
template<typename T, typename Compare>
void QuickSort(T* first, T* last, Compare comp)
{
	while (first < last)
	{
		T* pivot = HoarePartition(first, last, comp);

		if (pivot - first < last - pivot + 1)
		{
			QuickSort(first, pivot, comp);
			first = pivot + 1;
		}
		else
		{
			QuickSort(pivot + 1, last, comp);
			last = pivot;
		}
	}
}

// ���������������� ����������, ���� ������ ������, �� ������� ����������, ���� ������ ������ - ���������.
template<typename T, typename Compare>
void sort(T* first, T* last, Compare comp)
{
	while (last - first > kThreshold) // ������� ����� ��������� ����������, � ������� ����� ��������� ����������
	{
		T* pivot = HoarePartition(first, last, comp);

		if (pivot - first < last - pivot + 1)
		{
			sort(first, pivot, comp);
			first = pivot + 1;
		}
		else
		{
			sort(pivot + 1, last, comp);
			last = pivot;
		}
	}

	InsertionSort(first, last, comp); //���� ������ ������, �.�. ������� �������� ������� �� ���� �������� �� ��������������� ��������� ��������� ������� ������
}

template<typename T>
void PrintArray(T* first, T* last)
{
	for (auto i = first; i <= last; ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}