#include "Cache.h"

Cache::Cache(int size) : size(size), elementsNumber(0)
{
	numbers = new int[size];
}

Cache::~Cache()
{
	delete[] numbers;
}

void Cache::addNumber(int number)
{
	if (elementsNumber < size)
	{
		numbers[size - elementsNumber - 1] = number;
		elementsNumber++;
	}
	else
	{
		for (int i = size - 1; i > 0; i--)
		{
			numbers[i] = numbers[i - 1];
		}
		numbers[0] = number;
	}
}

bool Cache::findNumber(int number) const
{
	for (int i = 0; i < elementsNumber; i++)
	{
		if (numbers[i] == number)
			return true;
	}

	return false;
}