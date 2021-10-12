#pragma once
class Cache
{
public:

	Cache(int size);
	~Cache();
	void addNumber(int number); //dodaje liczb� do kolejki
	bool findNumber(int number) const; //sprawdza czy w cache'u jest dana liczba

private:
	int* numbers;
	int size;
	int elementsNumber;
};

