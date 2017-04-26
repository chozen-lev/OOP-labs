#include <iostream>
#include "cArray.h"

int main()
{
	cArray Array;

	std::cout << "Array count: " << Array.GetCount() << std::endl;
	std::cout << "Array size: " << Array.GetSize() << std::endl;
	std::cout << "Array Upper Bound: " << Array.GetUpperBound() << std::endl;
	std::cout << "Is array empty?: " << std::boolalpha << Array.IsEmpty() << std::endl;
	Array.Add(5);
	Array.Add(8);
	std::cout << "adding new elements 5, 8: " << Array[0] << ", " << Array[1] << std::endl;
	std::cout << "Array count: " << Array.GetCount() << std::endl;
	Array.SetAt(16,0);
	std::cout << "setting element's value with index 0 to 16: " << Array[0] << std::endl;
	Array.Append(&Array);
	Array.Append(&Array);
	Array.Append(&Array);
	std::cout << "appending array with itself 3 times: ";
	for (int i = 0; i < Array.GetCount() - 1; i++)
		std::cout << Array[i] << ", ";
	std::cout << Array[Array.GetUpperBound()] << std::endl;
	std::cout << "Array count: " << Array.GetCount() << ". Array size: " << Array.GetSize() << std::endl;
	Array.FreeExtra();
	std::cout << "freeing extra elements. " << "Array count: " << Array.GetCount() << ". Array size: " << Array.GetSize() << std::endl;
	Array.InsertAt(3, 5);
	std::cout << "inserting element at 5 pos with value 3: ";
	for (int i = 0; i < Array.GetCount() - 1; i++)
		std::cout << Array[i] << ", ";
	std::cout << Array[Array.GetUpperBound()] << std::endl;
	std::cout << "Array count: " << Array.GetCount() << ". Array size: " << Array.GetSize() << std::endl;
	Array.RemoveAt(Array.GetUpperBound());
	std::cout << "removing element at last pos: ";
	for (int i = 0; i < Array.GetCount() - 1; i++)
		std::cout << Array[i] << ", ";
	std::cout << Array[Array.GetUpperBound()] << std::endl;
	std::cout << "Array count: " << Array.GetCount() << ". Array size: " << Array.GetSize() << std::endl;

	cArray Array2;
	Array2.Copy(&Array);
	std::cout << "copying Array to Array2: ";
	for (int i = 0; i < Array2.GetCount() - 1; i++)
		std::cout << Array2[i] << ", ";
	std::cout << Array2[Array2.GetUpperBound()] << std::endl;
	std::cout << "Array2 count: " << Array2.GetCount() << ". Array2 size: " << Array2.GetSize() << std::endl;

	return 0;
}