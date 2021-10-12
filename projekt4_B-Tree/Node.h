#pragma once
#include <cstdlib>
struct Node
{
	bool isLeaf;
	int keyNumber; //liczba kluczy w wêŸle
	int* keys;
	Node** sons; //tablica wskaŸników na synów
	bool contains(int key) const
	{
		for (int i = 0; i < keyNumber; i++)
		{
			if (keys[i] == key)
				return true;
		}

		return false;
	}
	Node(int order) : isLeaf(true), keyNumber(0)
	{
		keys = new int[2 * order - 1];
		sons = new Node* [2 * order];
	}
	~Node()
	{
		delete[] keys;
		delete[] sons;
	}
};
