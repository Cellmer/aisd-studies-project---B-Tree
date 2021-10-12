#pragma once

struct Element
{
	int number;
	int heat=0;
};
class CacheUpgrade
{
public:

	CacheUpgrade(int size);
	~CacheUpgrade();
	void addNumber(int number); //dodaje liczbê do kolejki
	int findNumber(int number) const; //sprawdza czy w cache'u jest dana liczba
	void decrementHeat(); //zmniejsza temperaturê elementów o 1 (jeœli jest wiêksza od 0)
	void upgradeHeat(int index); //zwiêksza temperaturê elementu o danym indeksie o 2

private:
	Element* elements;
	int size;
	int elementsNumber;
};

