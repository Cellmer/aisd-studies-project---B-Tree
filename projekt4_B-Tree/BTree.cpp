#include <iostream>
#include <string>
#include "BTree.h"
#include "Node.h"

BTree::BTree(int order) : treeOrder(order), depth(0)
{
	root = new Node(order);
}

void BTree::insert(int key)
{
	if (root->keyNumber == 2 * treeOrder - 1) //root jest pe³ny
	{
		Node* newRoot = new Node(treeOrder);
		newRoot->isLeaf = false;
		newRoot->sons[0] = root;
		root = newRoot;
		splitChild(newRoot, 0);
	}
	insertNonFull(root, key);
}

Node* BTree::search(Node* node, int key) const
{
	depth++;
	int i = 0;
	while (i < node->keyNumber && key > node->keys[i])
		i++;

	if (i < node->keyNumber && key == node->keys[i])
		return node;

	else if (node->isLeaf)
		return nullptr;

	else
		return search(node->sons[i], key);



}

void BTree::setRoot(Node* node)
{
	root = node;
}

void BTree::print(Node* node) const
{
	if (node->isLeaf)
	{
		for (int i = 0; i < node->keyNumber; i++)
		{
			std::cout << node->keys[i] << " ";
		}
	}
	else
	{
		for (int i = 0; i < node->keyNumber; i++)
		{
			print(node->sons[i]);
			std::cout << node->keys[i] << " ";
		}
		print(node->sons[node->keyNumber]);
	}
}

void BTree::load()
{
	int sonNo = 0;
	std::string c; //wczytywana liczba lub nawias
	std::cin >> c; //wczytaj pierwszy otwieraj¹cy nawias
	std::cin >> c;

	while (c != ")")
	{
		if (c == "(")
		{
			addChild(root, sonNo);
			sonNo++;
		}
		else //c jest kluczem
		{
			root->keys[root->keyNumber] = std::stoi(c);
			root->keyNumber++;
		}
		std::cin >> c;
	}
}

void BTree::save(Node* node) const
{
	if (node->isLeaf)
	{
		std::cout << "( ";
		for (int i = 0; i < node->keyNumber; i++)
		{
			std::cout << node->keys[i] << " ";
		}
		std::cout << ") ";
	}
	else
	{
		std::cout << "( ";
		for (int i = 0; i < node->keyNumber; i++)
		{
			save(node->sons[i]);
			std::cout << node->keys[i] << " ";
		}
		save(node->sons[node->keyNumber]);
		std::cout << ") ";
	}

}

void BTree::remove(Node* node, int key)
{
	if (node->contains(key)) //w node jest key
	{
		//ustal którym kluczem w node jest key
		int i = 0;
		while (node->keys[i] != key)
			i++;

		if (node->isLeaf) //usuñ key z node
		{
			while (i < node->keyNumber - 1)
			{
				node->keys[i] = node->keys[i + 1];
				i++;
			}
			node->keyNumber--;
		}
		else if (node->sons[i]->keyNumber >= treeOrder) //syn poprzedzaj¹cy key nie jest minimalny wiêc szukaj poprzednika key i go usuñ i zamieñ
		{
			int predecessor = findPredecessor(node->sons[i]);
			remove(node->sons[i], predecessor);
			node->keys[i] = predecessor;

		}
		else if (node->sons[i + 1]->keyNumber >= treeOrder) //syn po key nie jest minimalny wiêc szukaj nastêpnika key i go usuñ i zamieñ
		{
			int successor = findSuccessor(node->sons[i + 1]);
			remove(node->sons[i + 1], successor);
			node->keys[i] = successor;
		}
		else //obaj synowie s¹ minmalni wiêc scal ich i usuñ key
		{
			merge(node, i); //scal synów node
			remove(node->sons[i], key);
		}
	}
	else //klucza nie ma w wêŸle
	{
		//znajdŸ syna w którym musi byæ key
		int i = 0;
		while (i < node->keyNumber && node->keys[i] < key)
		{
			i++;
		}
		Node* son = node->sons[i];

		if (son->keyNumber == treeOrder - 1) //syn jest minimalny
		{
			bool changed = false; //flaga mówi¹ca czy syn nadal jest minimalny
			if (i > 0)
			{
				Node* left = node->sons[i - 1];
				if (left->keyNumber >= treeOrder)
				{
					//zrób miejsce w minimalnym synu
					for (int j = son->keyNumber - 1; j >= 0; j--)
					{
						son->keys[j + 1] = son->keys[j];
						son->sons[j + 2] = son->sons[j + 1];
					}
					son->sons[1] = son->sons[0];
					son->keyNumber++;

					//przestaw odpowiednie klucze i wskaŸnik na synów
					son->keys[0] = node->keys[i - 1];
					node->keys[i - 1] = left->keys[left->keyNumber - 1];
					son->sons[0] = left->sons[left->keyNumber];
					left->keyNumber--;

					changed = true;
				}
			}
			else if (i < node->keyNumber)
			{
				Node* right = node->sons[i + 1];
				if (right->keyNumber >= treeOrder)
				{
					//przestaw odpowiednie klucze i wskaŸnik na synów
					son->keys[son->keyNumber] = node->keys[i];
					node->keys[i] = right->keys[0];
					son->sons[son->keyNumber + 1] = right->sons[0];
					son->keyNumber++;

					//zmniejsz prawego syna
					for (int j = 0; j < right->keyNumber - 1; j++)
					{
						right->keys[j] = right->keys[j + 1];
						right->sons[j] = right->sons[j + 1];
					}
					right->sons[right->keyNumber - 1] = right->sons[right->keyNumber];
					right->keyNumber--;

					changed = true;
				}
			}
			
			if (changed == false)
			{
				if (i > 0) //po³¹cz minimalnego syna z lewym bratem
				{
					merge(node, i - 1);
					son = node->sons[i - 1];
				}
				else //po³¹cz minimalnego syna z prawym bratem
					merge(node, i);
			}
		}

		remove(son, key);
	}
}

void BTree::resetDepth()
{
	depth = 0;
}

void BTree::splitChild(Node* parent, int sonNo)
{
	Node* newNode = new Node(treeOrder);
	Node* splitted = parent->sons[sonNo];
	newNode->isLeaf = splitted->isLeaf;
	newNode->keyNumber = treeOrder-1;
	for (int i = 0; i < treeOrder-1; i++) //przepisz do nowego wêz³a klucze z prawej po³owy dzielonego wêz³a
	{
		newNode->keys[i] = splitted->keys[i + treeOrder];
	}

	if (!splitted->isLeaf) //jeœli dzielony wêze³ nie by³ liœciem przeka¿ praw¹ czêœæ synów nowemu
	{
		for (int i = 0; i < treeOrder; i++)
		{
			newNode->sons[i] = splitted->sons[i + treeOrder];
		}
	}

	splitted->keyNumber = treeOrder - 1;

	//robi miejsce dla nowego klucza w rodzicu
	for (int i = parent->keyNumber; i > sonNo; i--)
	{
		parent->sons[i + 1] = parent->sons[i];
	}

	parent->sons[sonNo + 1] = newNode;

	for (int i = parent->keyNumber - 1; i >= sonNo; i--)
	{
		parent->keys[i + 1] = parent->keys[i];
	}

	parent->keys[sonNo] = splitted->keys[treeOrder - 1];
	parent->keyNumber++;
}

void BTree::insertNonFull(Node* node, int key)
{
	int i = node->keyNumber-1;
	if (node->isLeaf) //jeœli node jest liœciem to wstaw do niego
	{
		while (i >= 0 && key < node->keys[i])
		{
			node->keys[i + 1] = node->keys[i];
			i--;
		}
		node->keys[i + 1] = key;
		node->keyNumber++;
	}
	else //node nie jest liœciem wiêc znajdŸ odpowiedniego syna i wywo³aj funckjê dla niego
	{
		while (i >= 0 && key < node->keys[i])
		{
			i--;
		}
		i++;
		
		if (node->sons[i]->keyNumber == 2 * treeOrder - 1) //wyszukany syn jest pe³ny
		{
			splitChild(node, i);
			if (key > node->keys[i])
				i++;
		}

		insertNonFull(node->sons[i], key);
	}
}

void BTree::addChild(Node* node, int i)
{
	Node* newNode = new Node(treeOrder);
	int sonNo = 0;
	std::string c; //wczytywana liczba lub nawias
	std::cin >> c;
	while (c != ")")
	{
		if (c == "(")
		{
			addChild(newNode, sonNo);
			sonNo++;
		}
		else //c jest kluczem
		{
			newNode->keys[newNode->keyNumber] = std::stoi(c);
			newNode->keyNumber++;
		}
		std::cin >> c;
	}
	if (node->isLeaf)
		node->isLeaf = false;
	node->sons[i] = newNode;
}

int BTree::findPredecessor(Node* node)
{
	while (!node->isLeaf)
	{
		node = node->sons[node->keyNumber];
	}
	return node->keys[node->keyNumber-1];
}

int BTree::findSuccessor(Node* node)
{
	while (!node->isLeaf)
	{
		node = node->sons[0];
	}
	return node->keys[0];
}

void BTree::merge(Node* node, int index)
{
	int key = node->keys[index]; //usuwany klucz
	Node* predecessor = node->sons[index]; //lewy syn
	Node* successor = node->sons[index + 1]; //prawy syn

	//usuñ klucz z bie¿acego wêz³a
	int i = index + 1;
	while (i < node->keyNumber)
	{
		node->sons[i] = node->sons[i + 1];
		i++;
	}
	i = index;
	while (i < node->keyNumber - 1)
	{
		node->keys[i] = node->keys[i + 1];
		i++;
	}
	node->keyNumber--;

	//dodaj klucz k do syna poprzedzaj¹cego
	predecessor->keys[predecessor->keyNumber] = key;
	predecessor->keyNumber++;

	//dodaj wszystko z syna nastêpnego do syna poprzedniego
	for (int j = 0; j < successor->keyNumber; j++)
	{
		predecessor->keys[predecessor->keyNumber] = successor->keys[j];
		predecessor->sons[predecessor->keyNumber] = successor->sons[j];
		predecessor->keyNumber++;
	}
	predecessor->sons[predecessor->keyNumber] = successor->sons[successor->keyNumber];

	if (node->keyNumber == 0)
		setRoot(node->sons[0]);
	delete successor;
}

