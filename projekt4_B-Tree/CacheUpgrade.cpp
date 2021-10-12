#include "CacheUpgrade.h"

CacheUpgrade::CacheUpgrade(int size) : size(size), elementsNumber(0)
{
	elements = new Element[size];
}

CacheUpgrade::~CacheUpgrade()
{
	delete[] elements;
}

void CacheUpgrade::addNumber(int number)
{
	if (elementsNumber < size)
	{
		elements[size - elementsNumber - 1].number = number;
		elementsNumber++;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (elements[i].heat == 0)
			{
				elements[i].number = number;
				break;
			}
		}
	}
}

int CacheUpgrade::findNumber(int number) const
{
	for (int i = 0; i < elementsNumber; i++)
	{
		if (elements[i].number == number)
			return i;
	}

	return -1;
}

void CacheUpgrade::decrementHeat()
{
	for (int i = 0; i < elementsNumber; i++)
	{
		if (elements[i].heat > 0)
			elements[i].heat--;
	}
}

void CacheUpgrade::upgradeHeat(int index)
{
	elements[index].heat += 2;
}
