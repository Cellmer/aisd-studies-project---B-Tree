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
	void addNumber(int number); //dodaje liczb� do kolejki
	int findNumber(int number) const; //sprawdza czy w cache'u jest dana liczba
	void decrementHeat(); //zmniejsza temperatur� element�w o 1 (je�li jest wi�ksza od 0)
	void upgradeHeat(int index); //zwi�ksza temperatur� elementu o danym indeksie o 2

private:
	Element* elements;
	int size;
	int elementsNumber;
};

