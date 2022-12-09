#include "pch.h"
#include <string>
#include "..\MySort\MySort.h"

TEST(MySort, Check_InsertionSort_prim)
{
	const int N = 10;
	int arr[N];

	for (int i = 0; i < N; i++)
	{
		arr[i] = N - i;
	}

	InsertionSort(arr, arr + N - 1, [](int a, int b) { return a < b; });

	for (int i = 0; i < N - 1; i++)
	{
		ASSERT_GE(arr[i + 1], arr[i]);
	}
}


TEST(MySort, Check_InsertionSort_str)
{
	const int N = 10;
	std::string* str = new std::string[N];

	for (int i = 0; i < N; i++)
	{
		str[i] = std::to_string(N - i) + "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	}

	InsertionSort(str, str + N - 1, [](const std::string& a, const std::string& b) { return a < b; });

	for (int i = 0; i < N - 1; i++)
	{
		ASSERT_GE(str[i + 1], str[i]);
	}

	delete[] str;
}


TEST(MySort, Check_sort_prim)
{
	const int N = 40;
	int arr[N];

	for (int i = 0; i < N; i++)
	{
		arr[i] = N - i;
	}

	sort(arr, arr + N - 1, [](int a, int b) { return a < b; });

	for (int i = 0; i < N - 1; i++)
	{
		ASSERT_GE(arr[i + 1], arr[i]);
	}
}

TEST(MySort, Check_sort_str)
{
	const int N = 10;
	std::string* str = new std::string[N];

	for (int i = 0; i < N; i++)
	{
		str[i] = std::to_string(N - i) + "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	}

	InsertionSort(str, str + N - 1, [](const std::string& a, const std::string& b) { return a < b; });

	for (int i = 0; i < N - 1; i++)
	{
		ASSERT_GE(str[i + 1], str[i]);
	}

	delete[] str;
}

TEST(MySort, Quick_sort_prim)
{
	const int N = 10;
	int arr[N];

	for (int i = 0; i < N; i++)
	{
		arr[i] = N - i;
	}

	QuickSort(arr, arr + N - 1, [](int a, int b) { return a < b; });

	for (int i = 0; i < N - 1; i++)
	{
		ASSERT_GE(arr[i + 1], arr[i]);
	}
}

TEST(MySort, Quick_sort_str)
{
	const int N = 10;
	std::string* str = new std::string[N];

	for (int i = 0; i < N; i++)
	{
		str[i] = std::to_string(N - i) + "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	}

	QuickSort(str, str + N - 1, [](const std::string& a, const std::string& b) { return a < b; });

	for (int i = 0; i < N - 1; i++)
	{
		ASSERT_GE(str[i + 1], str[i]);
	}

	delete[] str;
}
