#include <iostream>
#include "./MyDynamicArray.h"

int main()
{
	setlocale(LC_ALL, "rus");
	
	Array<int>a(10);

	for (int i = 0; i < 10; i++)
	{
		a.Insert(i);
	}

	for (auto it = a.iterator(); it.HasNext(); it.Next())
	{
		std::cout<<it.Get()<<std::endl;
	}
	std::cout << std::endl;

	for (auto it = a.ReverseIterator(); it.HasNext(); it.Next()) //HasNext is not executed on the last element, so it is actually HasCurrent
	{
		std::cout << it.Get() << std::endl;
	}

	return EXIT_SUCCESS;
}