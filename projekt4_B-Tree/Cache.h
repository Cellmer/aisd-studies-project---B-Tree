#pragma once
class Cache
{
public:

	Cache(int size);
	~Cache();
	void addNumber(int number); //dodaje liczbê do kolejki
	bool findNumber(int number) const; //sprawdza czy w cache'u jest dana liczba

private:
	int* numbers;
	int size;
	int elementsNumber;
};

